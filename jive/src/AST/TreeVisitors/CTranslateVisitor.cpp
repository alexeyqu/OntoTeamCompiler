#include "CTranslateVisitor.h"
#include "CJiveEnvironment.h"

namespace AST
{

using namespace IRTTRANSLATOR;

using jive::CJiveEnvironment;

void CTranslateVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept( this );
}

void CTranslateVisitor::Visit( CProgram *program ) {
    program->getRoot()->Accept( this );
}

void CTranslateVisitor::Visit( CGoal *goal ) {
    goal->getLeft()->Accept( this );
    goal->getRight()->Accept( this );
}

void CTranslateVisitor::Visit( CType *type ) {
}

void CTranslateVisitor::Visit( CVariable *entity ) {
    if( curFrame ) {
        curFrame->addLocal( entity->getSymbol() );
    }
}

void CTranslateVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->getNextVariable() ) {
        entity->getNextVariable()->Accept( this );
    }
    entity->getVariable()->Accept( this );
}

void CTranslateVisitor::Visit( CArgument *entity ) {
    if( curFrame ) {
        curFrame->addParam( entity->getSymbol() );
    }
}

void CTranslateVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->getNextArgument() ) {
    	entity->getNextArgument()->Accept( this );
	}
    entity->getArgument()->Accept( this );
}

void CTranslateVisitor::Visit( CMethod *entity ) {    
    CSymbol *fragmentSymbol = CSymbol::makeSymbol( curClassSymbol->getSymbol()->getBasicString() + "::" + entity->getSymbol()->getBasicString() );
    curFrame = new CX86JiveFrame( fragmentSymbol );
    curMethodSymbol = curClassSymbol->lookupMethod( entity->getSymbol() );

    CClassSymbol *ancestorClass = curClassSymbol;
    while( ancestorClass != nullptr ) {
        for( auto field : ancestorClass->getFields() ) {
            curFrame->addField( field->getSymbol() );
        }

        ancestorClass = ancestorClass->getBaseClass();
    }

    if( entity->getArguments() ) {
    	entity->getArguments()->Accept( this );
	}

    if( entity->getVariables() ) {
        entity->getVariables()->Accept( this );
    }

    if( entity->getStatements() ) {
        entity->getStatements()->Accept( this );
    }

    IStm *methodStms = nullptr;
    if( translator ) {
        methodStms = translator->unNx();
    }

    entity->getReturnExpression()->Accept( this );

    IStm *returnStm = translator->unNx();
    IStm *fragmentStm = nullptr;

    if( methodStms ) {
        fragmentStm = new CSEQ( methodStms, returnStm );
    } else {
        fragmentStm = returnStm;
    }

    fragments.push_back( CFragment( curFrame, fragmentStm, fragmentSymbol ) );

    translator = nullptr;
    curMethodSymbol = nullptr;
    curFrame = nullptr;
}

void CTranslateVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->getNextMethod() ) {
		entity->getNextMethod()->Accept( this );
    }
    entity->getMethod()->Accept( this );
}

void CTranslateVisitor::Visit( CMainClass *entity ) {
    curClassSymbol = jiveEnv->classMap->lookup( entity ) ;
    curMethodSymbol = nullptr;
    CSymbol *fragmentSymbol = CSymbol::makeSymbol( curClassSymbol->getSymbol()->getBasicString() + "::main" );
    
    curFrame = new CX86JiveFrame( fragmentSymbol );

    if( entity->getMethods() ) {
		entity->getMethods()->Accept( this );
    }

    if( translator ) {
        fragments.push_back( CFragment( curFrame, translator->unNx(), fragmentSymbol ) );
    }
    
    curClassSymbol = nullptr;
    curMethodSymbol = nullptr;
    curFrame = nullptr;
    translator = nullptr;
}

void CTranslateVisitor::Visit( CClass *entity ) {
    curClassSymbol = jiveEnv->classMap->lookup( entity ) ;
    curMethodSymbol = nullptr;

    if( entity->getFields() ) {
		entity->getFields()->Accept( this );
    }

    if( entity->getMethods() ) {
		entity->getMethods()->Accept( this );
    }

    curClassSymbol = nullptr;
    curMethodSymbol = nullptr;
}

void CTranslateVisitor::Visit( CCompoundClass *entity ) {

    if( entity->getNextClass() ) {
        entity->getNextClass()->Accept( this );
    }
    entity->getClass()->Accept( this );
}


void CTranslateVisitor::Visit( CCompoundStatement *statement ) {
    statement->getRightStatement()->Accept( this );

    IStm *head = translator->unNx();
    translator = nullptr;

    if(statement->getLeftStatement()) {
        statement->getLeftStatement()->Accept( this );
        IStm *tail = translator->unNx();

        translator = new CStmTranslator( new CSEQ( head, tail ) );
    } else {
        translator = new CStmTranslator( head );
    }
}

void CTranslateVisitor::Visit( CAssignStatement *statement ) {
    statement->getLValue()->Accept( this );
	IExp *leftExp = translator->unEx();
	translator = nullptr;
	
    statement->getRValue()->Accept( this );
	IExp *rightExp = translator->unEx();
	translator = nullptr;

    translator = new CStmTranslator( new CMOVE( leftExp, rightExp ) );
}

void CTranslateVisitor::Visit( CPrintStatement *statement ) {
    statement->getExpression()->Accept( this );
	IExp *printExp = translator->unEx();
	translator = nullptr;

	CNAME *printName =  new CNAME( new CLabel( CSymbol::makeSymbol( "System.out.println" ) ) );

	CExpList *args = new CExpList( printExp, nullptr );
	IExp *printCall = new CCALL( printName, args );

	translator = new CExpTranslator( printCall );
}

void CTranslateVisitor::Visit( CIfStatement *statement ) {
    statement->getThenStatement()->Accept( this );
	IStm *trueStm = nullptr;
	if ( translator ) {
		trueStm = translator->unNx();
	}
	translator = nullptr;

	statement->getElseStatement()->Accept( this );
	IStm *falseStm = nullptr;
	if ( translator ) {
		falseStm = translator->unNx();
	}
	translator = nullptr;

	statement->getExpression()->Accept( this );
	CLabel *trueLabel = new CLabel();
	CLabel *falseLabel = new CLabel();
	CLabel *endLabel = new CLabel();

	translator = new CStmTranslator( 
        new CSEQ(
            new CSEQ(
                new CSEQ(
                    new CSEQ(
                        translator->unCx( trueLabel, falseLabel ),
					    new CSEQ( 
                            new CLABEL( trueLabel ), 
                            trueStm ) 
                        ),
					new CJUMP( endLabel ) 
                    ),
				new CSEQ(
                    new CLABEL( falseLabel ), 
                    falseStm )
                ),
			new CLABEL( endLabel ) 
        ) 
    );
}

void CTranslateVisitor::Visit( CWhileStatement *statement ) {
    statement->getStatement()->Accept( this );
	IStm* body = translator->unNx();
	translator = nullptr;

	CLabel* condLabel = new CLabel();
	CLabel* bodyLabel = new CLabel();
	CLabel* endLabel = new CLabel();

	statement->getExpression()->Accept( this );

	translator = new CStmTranslator(
        new CSEQ(
            new CSEQ(
                new CSEQ(
                    new CLABEL( condLabel ), 
					translator->unCx( bodyLabel, endLabel ) 
                ),
				new CSEQ(
                    new CLABEL( bodyLabel ), 
					new CSEQ(
                        body, 
                        new CJUMP( condLabel ) 
                    ) 
                ) 
            ),
            new CLABEL( endLabel ) 
        )
    );
}

void CTranslateVisitor::Visit( CIdExpression *expression ) {
	translator = new CExpTranslator( curFrame->getAccess( expression->getSymbol() )->getExp() );
}

void CTranslateVisitor::Visit( CBinaryExpression *expression ) {
    expression->getLeftOperand()->Accept( this );
	IExp* leftExp = translator->unEx();
	
	expression->getRightOperand()->Accept( this );
	IExp* rightExp = translator->unEx();

	switch (expression->getOperator()) {
		case jive::TArithmeticOperation::ADD:
			translator = new CExpTranslator( new CBINOP( TBINOP::ADD, leftExp, rightExp ) );
			break;
		case jive::TArithmeticOperation::SUB:
			translator = new CExpTranslator( new CBINOP( TBINOP::SUB, leftExp, rightExp ) );
			break;
		case jive::TArithmeticOperation::MUL:
			translator = new CExpTranslator( new CBINOP( TBINOP::MUL, leftExp, rightExp ) );
			break;
		default:
			assert( false );
	}
}

void CTranslateVisitor::Visit( CNumberExpression *expression ) {
    translator = new CExpTranslator( new CCONST( expression->getValue() ) );
}

void CTranslateVisitor::Visit( CBinaryBooleanExpression *expression ) {
    expression->getLeftOperand()->Accept( this );
	IExp* leftExp = translator->unEx();
	
	expression->getRightOperand()->Accept( this );
	IExp* rightExp = translator->unEx();

	switch (expression->getOperator()) {
		case jive::TBooleanOperation::LESS:
			translator = new CJumpTranslator( TCJUMP::LT, leftExp, rightExp );
			break;
		case jive::TBooleanOperation::GREATER:
			translator = new CJumpTranslator( TCJUMP::GT, leftExp, rightExp );
			break;
		case jive::TBooleanOperation::AND:
			translator = new CAndTranslator( leftExp, rightExp );
			break;
		case jive::TBooleanOperation::OR:
			translator = new COrTranslator( leftExp, rightExp );
			break;
		default:
			assert( false );
	}
}

void CTranslateVisitor::Visit( CBooleanExpression *expression ) {
    if( expression->getValue() ) {
		translator = new CExpTranslator( new CCONST( 1 ) );
	} else {
		translator = new CExpTranslator( new CCONST( 0 ) );
	}
}

void CTranslateVisitor::Visit( CThisExpression *expression ) {
    translator = new CExpTranslator( new CTEMP( curFrame->getThisPointer() ) );
}

void CTranslateVisitor::Visit( CNewObjectExpression *expression ) {
    CClassSymbol* objClass = jiveEnv->classMap->lookup( expression->getSymbol() );

	CNAME* newName = new CNAME( new CLabel( CSymbol::makeSymbol( "new" ) ) );

	CCALL* newCall = new CCALL( 
        newName, 
		new CExpList(  
            new CBINOP(
                TBINOP::MUL,
			    new CCONST( objClass->getFields().size() ), 
			    new CCONST( CX86JiveFrame::getWordSize() ) 
            ), 
            nullptr
        ) 
    );
	CTEMP* objTemp = new CTEMP( curFrame->getThisPointer() );

	CMOVE* alloc = new CMOVE( objTemp, newCall );

	translator = new CExpTranslator( new CESEQ( alloc, objTemp ) );
}

void CTranslateVisitor::Visit( CNewIntArrayExpression *expression ) {
    expression->getArrSize()->Accept( this );
	IExp* sizeExp = translator->unEx();
	translator = nullptr;

	IExp* memSizeExp = new CBINOP(
        TBINOP::MUL,
		new CBINOP( TBINOP::ADD, sizeExp, new CCONST( 1 ) ), 
		new CCONST( CX86JiveFrame::getWordSize() ) 
    );

	IExp* newName = new CNAME( new CLabel( CSymbol::makeSymbol( "new" ) ) );
	IExp* newCall = new CCALL( newName, new CExpList( memSizeExp, nullptr ) );
	CTEMP* arrTemp = new CTEMP( new CTemp() );

	CSEQ* memset = new CSEQ( 
        new CMOVE( arrTemp, newCall ), 
		new CMOVE( arrTemp, sizeExp ) 
    );

	translator = new CExpTranslator( new CESEQ( memset, arrTemp ) );
}

void CTranslateVisitor::Visit( CMethodCallExpression *expression ) {

	expression->getBaseExpression()->Accept( this );
	IExp* objExp = translator->unEx();
	translator = nullptr;

	CSymbol *methodSymbol = CSymbol::makeSymbol( curClassSymbol->getSymbol()->getBasicString() + "::" + expression->getMethodSymbol()->getBasicString() );
	CNAME* methodName = new CNAME( new CLabel( methodSymbol ) );

	expList = nullptr;
	if ( expression->getArguments() ) {
		expression->getArguments()->Accept( this );
	}
	CExpList* args = new CExpList( objExp, expList );

	CTEMP* returnTemp = new CTEMP( new CTemp() );

	translator = new CExpTranslator(
        new CESEQ( 
		    new CMOVE( 
                returnTemp, 
                new CCALL( methodName, args ) 
            ), 
            returnTemp
        ) 
    );
}

void CTranslateVisitor::Visit( CArrayLengthExpression *expression ) {

	expression->getValue()->Accept( this );
	IExp* lengthExp = translator->unEx();
	translator = nullptr;

	CTEMP* resultTemp = new CTEMP( new CTemp() );

	translator = new CExpTranslator( 
        new CESEQ( 
		    new CMOVE( resultTemp, lengthExp ), 
            resultTemp
        ) 
    );
}

void CTranslateVisitor::Visit( CArrayIndexExpression *expression ) {
    expression->getArrayId()->Accept( this );
	IExp* arrExp = translator->unEx();
	translator = nullptr;
	
	expression->getArrayIndex()->Accept( this );

	IExp* offset = new CBINOP( 
        TBINOP::MUL,
		new CBINOP( TBINOP::ADD, translator->unEx(), new CCONST( 1 ) ),
		new CCONST( CX86JiveFrame::getWordSize() ) 
    );
	translator = nullptr;

	translator = new CExpTranslator(
        new CMEM( 
            new CBINOP( TBINOP::ADD, arrExp, offset ) )
    );
}

void CTranslateVisitor::Visit( CCompoundExpression *expression ) {
	expression->getRightExpression()->Accept( this );
	IExp* exp = translator->unEx();

	if ( expression->getLeftExpression() ) {
		expression->getLeftExpression()->Accept( this );
	}
	
	expList = new CExpList( exp, expList );
}

void CTranslateVisitor::Visit( CVoidExpression *expression ) {
} 

}