#include "IRTree/CCodeGenerator.h"
#include "IRTree/IInstruction.h"
#include "IRTree/Instructions.h"
#include <string>
#include <cassert>


void CCodeGenerator::emit( IInstruction* instruction ) {
	instructions.push_back( instruction );
}

std::list<IInstruction*> CCodeGenerator::generateCode( IStm* rootStm ) {
	munchStm( rootStm );
	return instructions;
}

void CCodeGenerator::Generate() {
	CStmList* list = stms;
	while ( list ) {
		IStm* stm = list->GetHead();
		munchStm( stm );
		list = list->GetTail();
	}
}

std::list<IInstruction*> CCodeGenerator::GetInstrucions() const {
	return instructions;
}

void CCodeGenerator::munchStm( IStm* statement ) {
	if ( !statement ) {
		return;
	}	
	MOVE* moveStm = helper.IsMOVE( statement );
	EXP* expStm = helper.IsEXP( statement );
	SEQ* seqStm = helper.IsSEQ( statement );
	JUMP* jumpStm = helper.IsJUMP( statement );
	CJUMP* cjumpStm = helper.IsCJUMP( statement );
	LABEL* labelStm = helper.IsLABEL( statement );
	if ( moveStm ) {
		munchStm( moveStm );
	} else if ( expStm ) {
		munchStm( expStm );
	} else if ( seqStm ) {
		munchStm( seqStm );
	} else if ( jumpStm ) {
		munchStm( jumpStm );
	} else if ( cjumpStm ) {
		munchStm( cjumpStm );
	} else if ( labelStm ) {
		munchStm( labelStm );
	}
}

void CCodeGenerator::munchStm( SEQ* seq ) {
	munchStm( seq->GetLeft() );
	munchStm( seq->GetRight() );
}

void CCodeGenerator::munchStm( MOVE* move ) {
	if ( munchFunctionCall( move ) ) {
		return;
	}

	MEM* destMem = helper.IsMEM(move->GetDest());
	MEM* srcMem = helper.IsMEM( move->GetSrc() );

	CTemp* d0 = munchExp( destMem ? destMem->GetExp() : move->GetDest() );
	CTemp* s0 = munchExp( srcMem ? srcMem->GetExp() : move->GetSrc() );

	if( destMem && srcMem ) {	
		CTemp* temp = new CTemp();
		emit(new MOVEI("\tMOV `d0, [`s0]", temp,  s0 ) );
		emit( new MOVEI( "\tMOV [`d0], `s0", d0, temp ) );
	} else if( destMem && !srcMem ) {
		emit( new MOVEI( "\tMOV [`d0], `s0", d0, s0 ) );
	} else if( srcMem && !destMem ) {
		emit( new MOVEI( "\tMOV `d0, [`s0]", d0, s0 ) );
	} else if( !srcMem && !destMem ) {
		emit( new MOVEI( "\tMOV `d0, `s0", d0, s0 ) );
	}
}

void CCodeGenerator::munchStm( EXP* exp ) {
	if ( munchProcedureCall( exp ) ) {
		return;
	}

	CTemp* d0 = new CTemp();
	CTemp* s0 = munchExp( exp->GetExp() );
	emit( new MOVEI( "\tMOV `d0, `s0", d0, s0 ) );
}

void CCodeGenerator::munchStm( LABEL* label ) {
	emit( new LABELI( label->GetLabel()->Name() + ": ", label->GetLabel() ) );
}

void CCodeGenerator::munchStm( JUMP* jump ) {
	CLabel* label = jump->GetTargets()->GetHead();
	emit( new OPER( "\tJUMP `j0", nullptr, nullptr, ToList( label ) ) );
}

void CCodeGenerator::munchStm( CJUMP* cjump ) {
	CLabel* trueLabel = cjump->GetIfTrue();
	CLabel* falseLabel = cjump->GetIfFalse();
	CTemp* leftArg = munchExp( cjump->GetLeft() );
	CTemp* rightArg = munchExp( cjump->GetRight() );
	emit( new OPER( "\tCMP `s0, `s1", nullptr, ToList( leftArg, rightArg ) ) );

	switch( cjump->GetOp() ) {
		case enums::EQ:
			emit( new OPER( "\tJE `j0", nullptr, nullptr, ToList( trueLabel ) ) );
			emit( new OPER( "\tJUMP `j0", nullptr, nullptr, ToList( falseLabel ) ) );
			break;
		case enums::NE:
			emit( new OPER( "\tJNE `j0", nullptr, nullptr, ToList( trueLabel ) ) );
			emit( new OPER( "\tJUMP `j0", nullptr, nullptr, ToList( falseLabel ) ) );
			break;
		case enums::GT:
			emit( new OPER( "\tJG `j0", nullptr, nullptr, ToList( trueLabel ) ) );
			emit( new OPER( "\tJUMP `j0", nullptr, nullptr, ToList( falseLabel ) ) );
			break;
		case enums::LT:
			emit( new OPER( "\tJL `j0", nullptr, nullptr, ToList( trueLabel ) ) );
			emit( new OPER( "\tJUMP `j0", nullptr, nullptr, ToList( falseLabel ) ) );
			break;
		case enums::GE:
			emit( new OPER( "\tJGE `j0", nullptr, nullptr, ToList( trueLabel ) ) );
			emit( new OPER( "\tJUMP `j0", nullptr, nullptr, ToList( falseLabel ) ) );
			break;
		case enums::LE:
			emit( new OPER( "\tJLE `j0", nullptr, nullptr, ToList( trueLabel ) ) );
			emit( new OPER( "\tJUMP `j0", nullptr, nullptr, ToList( falseLabel ) ) );
			break;
		default:
			break;
	}
}

CTemp* CCodeGenerator::munchExp( IExp* exp ) {
	MEM* memExp = helper.IsMEM( exp );
	BINOP* binopExp = helper.IsBINOP( exp );
	CONST* constExp = helper.IsCONST( exp );
	CALL* callExp = helper.IsCALL( exp );
	NAME* nameExp = helper.IsNAME( exp );
	TEMP* tempExp = helper.IsTEMP( exp );

	if( memExp ) {
		return munchExp( memExp );
	} else if( binopExp ) {
		return munchExp( binopExp );
	} else if( constExp ) {
		return munchExp( constExp );
	} else if( callExp ) {
		return munchExp( callExp );
	} else if( nameExp ) {
		return munchExp( nameExp );
	} else if( tempExp ) {
		return munchExp( tempExp );
	} else {
		return nullptr;
	}
}

CTemp* CCodeGenerator::munchExp( CONST* constExp ) {
	CTemp* temp = new CTemp();
	std::string command = "\tMOV `d0, " + std::to_string( constExp->GetValue() );
	emit( new MOVEI( command, temp, nullptr ) );
	return temp;
}

CTemp* CCodeGenerator::munchExp( NAME* name ) {
	return nullptr;
}

CTemp* CCodeGenerator::munchExp( TEMP* temp ) {
	return temp->GetTemp();
}

CTemp* CCodeGenerator::munchExp( BINOP* binop ) {
	CTemp* temp = new CTemp();
	CTemp* leftOperand = munchExp( binop->GetLeft() );
	CTemp* rightOperand = munchExp( binop->GetRight() );
	emit( new MOVEI("\tMOV `d0, `s0", temp, leftOperand) );
	switch( binop->GetOp() ) {
		case enums::BO_ADD:
			emit( new OPER( "\tADD `d0, `s0", ToList( temp ), ToList( rightOperand ) ) );
			break;
		case enums::BO_SUB:
			emit( new OPER( "\tSUB `d0, `s0", ToList( temp ), ToList( rightOperand ) ) );
			break;
		case enums::BO_MUL:
			emit( new OPER( "\tIMUL `d0, `s0", ToList( temp ), ToList( rightOperand ) ) );
			break;
		case enums::BO_DIV:
			// TIP: деление в x86 привязано к регистрам
			break;
		case enums::BO_AND:
			emit( new OPER( "\tAND `d0, `s0", ToList( temp ), ToList( rightOperand ) ) );
			break;
		case enums::BO_OR:
			emit( new OPER( "\tOR `d0, `s0", ToList( temp ), ToList( rightOperand ) ) );
			break;
		default:
			break;
	}
	return temp;
}

CTemp* CCodeGenerator::munchExp( MEM* mem ) {
	CTemp* temp = new CTemp();
	CTemp* src = munchExp( mem->GetExp() );
	emit( new MOVEI( "\tMOV `d0, [`s0]", temp, src ) );
	return temp;
}

CTemp* CCodeGenerator::munchExp( CALL* call ) {
	return nullptr;
}

CTempList* CCodeGenerator::munchArgs( CExpList* expList )
{
	CExpList* list = expList;

	std::list<CTemp*> temps;

	while ( list ) {
		IExp* currentExrpession = list->GetHead();
		temps.push_back( munchExp( currentExrpession ) );
		// Переходим к следующему аргументу
		list = list->GetTail();
	}

	// Оборачиваем полученные переменные в CTempList
	CTempList* tempsList = nullptr;
	for ( auto temp = temps.begin(); temp != temps.end(); temp++ ) {
		tempsList = new CTempList( *temp, tempsList );
	}

	// Возвращаем результат
	return tempsList;
}

bool CCodeGenerator::munchFunctionCall( MOVE* move ) {
	TEMP* tempExp = helper.IsTEMP( move->GetDest() );
	CALL* callExp = helper.IsCALL( move->GetSrc() );
	if ( !tempExp || !callExp ) {
		return false;
	}
	munchProcedureCall( new EXP( callExp ) );
	CTemp* resultTemp = munchExp( tempExp );
	emit( new MOVEI( "\tMOV `d0, EAX", resultTemp, nullptr ) );
	return true;
}

bool CCodeGenerator::munchProcedureCall( EXP* exp ) {
	CALL* callExp = helper.IsCALL( exp->GetExp() );
	if ( !callExp ) {
		return false;
	}
	CTemp* temp = munchExp( callExp->GetFunc() );
	NAME* functionName = dynamic_cast<NAME*>( callExp->GetFunc() );
	assert( functionName );
	CTempList* argList = munchArgs( callExp->GetArgs() );
	CTempList* list = argList;
	while ( list ) {
		CTemp* temp = list->GetHead();		
		emit( new OPER( "\tPUSH `s0", methodFrame->GetCallDefArgs(),
			ToList( temp ), nullptr ) );
		list = list->GetTail();
	}	
	emit( new OPER( "\tCALL " + functionName->GetLabel()->Name(), 
		nullptr, new CTempList( temp, argList ) ) );
	return true;
}