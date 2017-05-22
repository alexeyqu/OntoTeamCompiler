#include "IRTree/CCanonizer.h"
#include "IRTree/TreeVisitors/CIRTreePrinter.h"
#include <cassert>

CStmExpList* CCanonizer::nopNull = 
	new CStmExpList( new EXP( new CONST( 0 ) ), nullptr );

bool CCanonizer::IsNop( IStm* stm ) {
	EXP* exp = dynamic_cast<EXP*>( stm );
	return ( exp != nullptr
		&& dynamic_cast<CONST*>( exp->GetExp() ) != nullptr );
}

bool CCanonizer::Commute( IStm* stm, IExp* exp ) {
	return ( IsNop( stm )
		|| dynamic_cast<NAME*>( exp ) != nullptr
		|| dynamic_cast<CONST*>( exp ) != nullptr );
}

IStm* CCanonizer::Seq( IStm* stm1, IStm* stm2 ) {
	if( IsNop( stm1 ) ) {
		return stm2;
	} else if( IsNop( stm2 ) ) {
		return stm1;
	} else {
		return new SEQ( stm1, stm2 );
	}
}

IStm* CCanonizer::DoStm( SEQ* seq ) {
	return Seq( DoStm( seq->GetLeft() ), DoStm( seq->GetRight() ) );
}

IStm* CCanonizer::DoStm( MOVE* stm ) {
	TEMP* temp = dynamic_cast<TEMP*>( stm->GetDest() );
	CALL* call = dynamic_cast<CALL*>( stm->GetSrc() );
	ESEQ* eseq = dynamic_cast<ESEQ*>( stm->GetDest() );

	if( temp && call ) {
		return ReorderStm( new MoveCall( temp, call ) );
	} else if( eseq ) {
		return DoStm( new SEQ( eseq->GetStm(),
			new MOVE( eseq->GetExp(), stm->GetSrc() ) ) );
	} else {
		return ReorderStm( stm );
	}
}

IStm* CCanonizer::DoStm( EXP* stm ) {
	CALL* call = dynamic_cast<CALL*>( stm->GetExp() );
	if( call ) {
		return ReorderStm( new ExpCall( call ) );
	} else {
		return ReorderStm( stm );
	}
}

IStm* CCanonizer::DoStm( IStm* stm ) {
	SEQ* seq = dynamic_cast< SEQ* >( stm );
	MOVE* move = dynamic_cast< MOVE* >( stm );
	EXP* exp = dynamic_cast< EXP* >( stm );

	if( seq ) {
		return DoStm( seq );
	} else if( move ) {
		return DoStm( move );
	} else if( exp ) {
		if( IsNop( stm ) ) {
			return nullptr;
		} else {
			return DoStm( exp );
		}
	} else {
		return ReorderStm( stm );
	}
}

ESEQ* CCanonizer::DoExp( ESEQ* exp ) {
	IStm* stm = DoStm( exp->GetStm() );
	ESEQ* eseq = DoExp( exp->GetExp() );
	return new ESEQ( Seq( stm, eseq->GetStm() ), eseq->GetExp() );
}

ESEQ* CCanonizer::DoExp( IExp* exp ) {
	ESEQ* eseq = dynamic_cast< ESEQ* >( exp );
	if( eseq ) {
		return DoExp( eseq );
	} else {
		return ReorderExp( exp );
	}
}

CStmExpList* CCanonizer::Reorder( CExpList* exps ) {
	if( !exps )
		return nopNull;
	else {
		IExp* exp = exps->GetHead();
		if( dynamic_cast<CALL*>( exp ) ) {
			CTemp* temp = new CTemp();
			IExp* eseq = new ESEQ( 
				new MOVE( new TEMP( temp ), exp ), new TEMP( temp ) );
			return Reorder( new CExpList( eseq, exps->GetTail() ) );
		} else {
			ESEQ* eseq = DoExp( exp );
			CStmExpList* list = Reorder( exps->GetTail() );
			if( Commute( list->GetStm(), eseq->GetExp() ) ) {
				return new CStmExpList( Seq( eseq->GetStm(), list->GetStm() ),
					new CExpList( eseq->GetExp(), list->GetExps() ) );
			} else {
				CTemp* temp = new CTemp();
				return new CStmExpList(
					Seq( eseq->GetStm(), Seq( new MOVE( 
						new TEMP( temp ), eseq->GetExp() ), list->GetStm() ) ),
					new CExpList( new TEMP( temp ), list->GetExps() ) );
			}
		}
	}
}

IStm* CCanonizer::ReorderStm( IStm* stm ) {
	if( !stm ) {
		return nullptr;
	}
	CStmExpList* list = Reorder( stm->Kids() );
	return Seq( list->GetStm(), stm->Build( list->GetExps() ) );
}

ESEQ* CCanonizer::ReorderExp( IExp* exp ) {
	CStmExpList* list = Reorder( exp->Kids() );
	return new ESEQ( list->GetStm(), exp->Build( list->GetExps() ) );
}

CStmList* CCanonizer::Linear( SEQ* seq, CStmList* list ) {
	return Linear( seq->GetLeft(), Linear( seq->GetRight(), list ) );
}

CStmList* CCanonizer::Linear( IStm* stm, CStmList* list ) {
	SEQ* seq = dynamic_cast<SEQ*>( stm );
	if( seq ) {
		return Linear( seq, list );
	} else {
		if( stm ) {
			return new CStmList( stm, list );
		} else {
			return list;
		}
	}
}

CStmList* CCanonizer::Linearize( IStm* stm ) {
	if( stm ) {
		return Linear( DoStm( stm ), nullptr );
	} else {
		return nullptr;
	}
}

void CCanonizer::Canonize() {
	linearizeStm();
	makeBlocks( linearizedStms );
	generateTraces();
	optimizeCjumpBlocks();
	translateToStms();
}

void CCanonizer::linearizeStm() {
	linearizedStms = Linearize( stm );

	CStmList* list = linearizedStms;

	CIRTreePrinter* irTreePrinter = new CIRTreePrinter( "linearized_test.dot" );
	irTreePrinter->OpenFile();

	size_t methodsCounter = 1;
	while( list ) {
		irTreePrinter->ResetPrinter( 
			"fragment" + std::to_string( methodsCounter ) + "_", 
			"fragment" + std::to_string( methodsCounter ) );
		list->GetHead()->Accept( irTreePrinter );
		methodsCounter++;
		irTreePrinter->WriteGraphToFile();
		list = list->GetTail();
	}
	irTreePrinter->CloseFile();
}

void CCanonizer::split() {
	makeBlocks( linearizedStms );
}

void CCanonizer::makeBlocks( CStmList* list ) {
	if( !list ) {
		return;
	}
	if( !isLABEL( list->GetHead() ) ) {
		list = new CStmList( new LABEL( new CLabel() ), list );
	}
	LABEL* label = dynamic_cast<LABEL*>( list->GetHead() );
	curBlock.Label = label;
	doStms( list->GetTail() );
}

void CCanonizer::doStms( CStmList* list ) {
	if( !list ) {
		list = new CStmList( new JUMP( methodFrame->GetEpilogueLabel() ), nullptr );
	}
	if( isLABEL( list->GetHead() ) ) {
		LABEL* stm = dynamic_cast<LABEL*>( list->GetHead() );
		list = new CStmList( new JUMP( stm->GetLabel() ), list ) ;
	}
	if( isJUMP( list->GetHead() ) || isCJUMP( list->GetHead() ) ) {
		curBlock.Jump = list->GetHead();
		basicBlocks.push_back( curBlock );
		curBlock.Clear();
		makeBlocks( list->GetTail() );
	} else {
		curBlock.AddStm( list->GetHead() );
		doStms( list->GetTail() );
	}
}

void CCanonizer::connect() {
	if ( basicBlocks.empty() ) {
		return;
	}

	IStm* curBlockLabel = nullptr;
	auto& previousBlock = basicBlocks.begin();
	auto& nextBlock = previousBlock + 1;

	if ( !previousBlock->Label ) {
		previousBlock->Label = new LABEL( methodFrame->GetStartLabel() );
	}

	while ( nextBlock != basicBlocks.end() ) {

		if ( !previousBlock->Jump && nextBlock->Label ) {
			previousBlock->Jump = new JUMP( nextBlock->Label->GetLabel() );
		} else if ( previousBlock->Jump && !nextBlock->Label ) {
			throw( "Error in connecting basic blocks" );
		}
		previousBlock++;
		nextBlock++;
	}

	if ( !previousBlock->Jump ) {
		previousBlock->Jump = new JUMP( methodFrame->GetEpilogueLabel() );
	}
}

void CCanonizer::generateTraces() {
	std::vector<CBasicBlock> reorderedBlocks;
	std::map<CLabel*, CBasicBlock> blocksByLavel;
	std::map<CLabel*, bool> isBlockVisited;

	for ( auto& basicBlock : basicBlocks ) {
		isBlockVisited[basicBlock.Label->GetLabel()] = false;
		blocksByLavel[basicBlock.Label->GetLabel()] = basicBlock;
	}
	
	for( auto& basicBlock : basicBlocks ) {
		std::vector<CBasicBlock> currentTrace;

		CBasicBlock curBlock = basicBlock;
		CLabel* curBlockLabel = basicBlock.Label->GetLabel();

		while( !isBlockVisited[curBlockLabel] ) {
			isBlockVisited[curBlockLabel] = true;
			currentTrace.push_back( curBlock );

			if( curBlock.GetJump() ) {
				CLabel* jumpLabel = curBlock.GetJump()->GetTargets()->GetHead();
				if (jumpLabel == methodFrame->GetEpilogueLabel()) {
					break;
				}
				if( !isBlockVisited[jumpLabel] ) {
					curBlock = blocksByLavel[jumpLabel];
					curBlockLabel = jumpLabel;
				}
			} else if( curBlock.GetCjump() ) {
				CLabel* ifTrueLabel = curBlock.GetCjump()->GetIfTrue();
				if( !isBlockVisited[ifTrueLabel] ) {
					curBlock = blocksByLavel[ifTrueLabel];
					curBlockLabel = ifTrueLabel;
				} else {
					CLabel* ifFalseLabel = curBlock.GetCjump()->GetIfFalse();
					if( !isBlockVisited[ifFalseLabel] ) {
					curBlock = blocksByLavel[ifFalseLabel];
					curBlockLabel = ifFalseLabel;
					}
				}
			}
		}
		reorderedBlocks.insert( reorderedBlocks.end(), currentTrace.begin(), currentTrace.end() );
		currentTrace.clear();
	}

	basicBlocks.clear();
	basicBlocks = std::vector<CBasicBlock>( reorderedBlocks );
}

void CCanonizer::optimizeCjumpBlocks() {
	for ( auto basicBlock = basicBlocks.begin(), nextBasicBlock = basicBlocks.begin() + 1;
		nextBasicBlock != basicBlocks.end();
		basicBlock++, nextBasicBlock++
		) {
		CJUMP* jumpStm = basicBlock->GetCjump();
		if ( jumpStm ) {
			CLabel* falseLabel = jumpStm->GetIfFalse();
			CLabel* trueLabel = jumpStm->GetIfTrue();

			CLabel* nextBlockLabel = nextBasicBlock->Label->GetLabel();

			if( nextBlockLabel == falseLabel ) {
				continue;
			} else if( nextBlockLabel == trueLabel ) {
				IExp *leftExpression = jumpStm->GetLeft();
				IExp *rightExpression = jumpStm->GetRight();
				basicBlock->Jump = new CJUMP( jumpStm->GetNotOp(), leftExpression, rightExpression, falseLabel, trueLabel );
			} else {
				CBasicBlock newBlock;
				CLabel* newLabel = new CLabel();
				newBlock.Label = new LABEL( newLabel );
				newBlock.Jump = new JUMP( jumpStm->GetIfFalse() );

				basicBlock->Jump = new CJUMP(
					jumpStm->GetOp(), jumpStm->GetLeft(), jumpStm->GetRight(),
					jumpStm->GetIfTrue(), newLabel );

				auto insertedBlockIterator = basicBlocks.insert( nextBasicBlock, newBlock );
				basicBlock = insertedBlockIterator;
				nextBasicBlock = insertedBlockIterator + 1;
			}
		}
	}
}

void CCanonizer::translateToStms() {
	std::list<IStm*> stms;
		
	auto basicBlock = basicBlocks.begin();
	auto nextBasicBlock = basicBlock + 1;
	
	stms.push_back( basicBlock->Label );

	while ( nextBasicBlock != basicBlocks.end() ) {
		for ( auto block : basicBlock->FlowStms ) {
			stms.push_back( block );
		}

		JUMP* jumpStm = basicBlock->GetJump();
		CJUMP* cjumpStm = basicBlock->GetCjump();
		LABEL* nextBlockLabel = nextBasicBlock->Label;
		bool isOmmited = false;

		if( jumpStm && 
			jumpStm->GetTargets()->GetHead() == nextBlockLabel->GetLabel() ) {
			isOmmited = true;
		}

		if( !isOmmited ) {
			if( jumpStm ) {
				stms.push_back( jumpStm );
			} else if( cjumpStm ) {
				stms.push_back( cjumpStm );
			} else {
				assert( false, "Null Jump!!!" );
			}
		}
		stms.push_back( nextBlockLabel );
		basicBlock++;
		nextBasicBlock++;
	}
	for ( auto block : basicBlock->FlowStms ) {
		stms.push_back( block );
	}
	stms.push_back( basicBlock->Jump );

	CStmList* list = nullptr;
	for ( auto stm = stms.rbegin(); stm != stms.rend(); stm++ ) {
		list = new CStmList( *stm, list );
	}
	canonizedStmList = list;

	CIRTreePrinter* irTreePrinter = new CIRTreePrinter( "canonized_test.dot" );
	irTreePrinter->OpenFile();

	size_t methodsCounter = 1;
	while( list ) {
		irTreePrinter->ResetPrinter( 
			"fragment" + std::to_string( methodsCounter ) + "_", 
			"fragment" + std::to_string( methodsCounter ) );
		list->GetHead()->Accept( irTreePrinter );
		methodsCounter++;
		irTreePrinter->WriteGraphToFile();
		list = list->GetTail();
	}
	irTreePrinter->CloseFile();
}