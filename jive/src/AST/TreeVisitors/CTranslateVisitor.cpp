#include "AST/TreeVisitors/CTranslateVisitor.h"
#include <iostream>
#include <cassert>

void CTranslateVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept( this );
}

void CTranslateVisitor::Visit( CProgram *program ) {
	program->rootVertex->Accept( this );
}

void CTranslateVisitor::Visit( CGoal *goal ) {
    goal->tmp1->Accept( this );
	if ( goal->tmp2 ) {
		goal->tmp2->Accept( this );
	}
}

void CTranslateVisitor::Visit( CBuiltInType *type ) {	
}

void CTranslateVisitor::Visit( CUserType *type ) {	
}

void CTranslateVisitor::Visit( CVariable *entity ) {
	if( curFrame ) {
		curFrame->AddLocal( CSymbol::GetSymbol( entity->id->name ) );
	}
}

void CTranslateVisitor::Visit( CCompoundVariable *entity ) {
	if( entity->var1 ) {
        entity->var1->Accept( this );
    }
    entity->var2->Accept( this );
}

void CTranslateVisitor::Visit( CArgument *entity ) {
	curFrame->AddFormal( CSymbol::GetSymbol( entity->id->name ) );
}

void CTranslateVisitor::Visit( CCompoundArgument *entity ) {
	entity->arg1->Accept( this );
	if( entity->arg2 ) {
    	entity->arg2->Accept( this );
	}
}

void CTranslateVisitor::Visit( CMethod *entity ) {
	curFrame = new CFrame( CSymbol::GetSymbol( 
		curClass->GetName() + "$" + entity->id->name ) );
	curMethod = curClass->methods.GetObject( 
		CSymbol::GetSymbol( entity->id->name ) );

	std::vector<CClassSymbol*> hierarhy;
	hierarhy.push_back( curClass );
	CSymbol* parentName = curClass->parentName;
	while( parentName ) {
		CClassSymbol* parentlass = table->GetClassByName( parentName );
		hierarhy.push_back( parentlass );
		parentName = parentlass->parentName;
	}

	for( int i = hierarhy.size() - 1; i >= 0; --i ) {
		for( auto it = hierarhy[i]->fields.GetBegin(); 
			it != hierarhy[i]->fields.GetEnd(); ++it ) {
			curFrame->AddField( it->second->name );
		}
	}

	if( entity->arguments ) {
    	entity->arguments->Accept( this );
	}

	if( entity->variables ) {
        entity->variables->Accept( this );
    }

	if( entity->statements ) {
        entity->statements->Accept( this );
    }

	IStm* methodStms = nullptr;
	if ( wrapper ) {
		methodStms = wrapper->ToStm();
	} 

	entity->returnExpression->Accept( this );
	IStm* returnStm = wrapper->ToStm();
	IStm* fragmentStm = nullptr;
	if ( methodStms ) {
		fragmentStm = new SEQ( methodStms, returnStm );
	}
	else {
		fragmentStm = returnStm;
	}

	Fragments.push_back( CFragment( curFrame, fragmentStm,
		curClass->GetName() + "$" + curMethod->GetName() ) );
	wrapper = nullptr;

	curMethod = nullptr;
	curFrame = nullptr;
}

void CTranslateVisitor::Visit( CCompoundMethod *entity ) {
	if( entity->method1 ) {
            entity->method1->Accept( this );
    }
    entity->method2->Accept( this );
}

void CTranslateVisitor::Visit( CMainClass *entity ) {
	curClass = table->GetClassByName( entity->name->name );
	curFrame = new CFrame( 
		CSymbol::GetSymbol( curClass->GetName() + "$main" ) );
	IStatement* statement = entity->statement;
	if ( statement ) {
		statement->Accept( this );
	}
	Fragments.push_back( CFragment( curFrame, 
		wrapper->ToStm(), curClass->GetName() + "$main" ) );
	curClass = nullptr;
	curFrame = nullptr;
	wrapper = nullptr;
}

void CTranslateVisitor::Visit( CClass *entity ) {
	curClass = table->GetClassByName( entity->name->name );
	if( entity->fields ) {
            entity->fields->Accept( this );
    }

	if( entity->methods ) {
            entity->methods->Accept( this );
    }

	curClass = nullptr;
	wrapper = nullptr;
}

void CTranslateVisitor::Visit( CCompoundClass *entity ) {
	if( entity->class1 ) {
        entity->class1->Accept( this );
    }
    entity->class2->Accept( this );
}

void CTranslateVisitor::Visit( CCompoundStatement *statement ) {
	statement->rightStatement->Accept( this );
	IStm* head = wrapper->ToStm();
	wrapper = nullptr;

	if ( statement->leftStatement ) {
		statement->leftStatement->Accept( this );
		IStm* tail = wrapper->ToStm();
		wrapper = new CStmConverter( new SEQ( head, tail ) );
	} else {
		wrapper = new CStmConverter( head );
	}
}

void CTranslateVisitor::Visit( CIfStatement *statement ) {

	statement->thenStatement->Accept( this );
	IStm* trueStm = nullptr;
	if ( wrapper ) {
		trueStm = wrapper->ToStm();
	}
	wrapper = nullptr;

	statement->elseStatement->Accept( this );
	IStm* falseStm = nullptr;
	if ( wrapper ) {
		falseStm = wrapper->ToStm();
	}
	wrapper = nullptr;

	statement->expression->Accept( this );
	CLabel* trueLabel = new CLabel();
	CLabel* falseLabel = new CLabel();
	CLabel* endLabel = new CLabel();

	wrapper = new CStmConverter( new SEQ
		( new SEQ
			( new SEQ
				( new SEQ
					( wrapper->ToConditional( trueLabel, falseLabel ),
					new SEQ( new LABEL( trueLabel ), trueStm ) ),
					new JUMP( endLabel ) ),
					new SEQ( new LABEL( falseLabel ), falseStm ) ),
					new LABEL( endLabel ) ) );
}

void CTranslateVisitor::Visit( CWhileStatement *statement ) {

	statement->loopStatement->Accept( this );
	IStm* body = wrapper->ToStm();
	wrapper = nullptr;

	CLabel* condLabel = new CLabel();
	CLabel* bodyLabel = new CLabel();
	CLabel* endLabel = new CLabel();

	statement->expression->Accept( this );

	wrapper = new CStmConverter( new SEQ
		( new SEQ
			( new SEQ
				( new LABEL( condLabel ), 
					wrapper->ToConditional( bodyLabel, endLabel ) ),
				( new SEQ( new LABEL( bodyLabel ), 
					new SEQ( body, new JUMP( condLabel ) ) ) ) ),
				new LABEL( endLabel ) ) );
}

void CTranslateVisitor::Visit( CAssignStatement *statement ) {

	statement->leftOperand->Accept( this );
	IExp* leftExp = wrapper->ToExp();
	wrapper = nullptr;
	/*CSymbol* varName = CSymbol::GetSymbol( statement->leftOperand );
	IExp* leftExp = curFrame->FindLocalOrFormal( varName )->GetExp( curFrame->FramePointer() );*/
	statement->rightOperand->Accept( this );
	IExp* rightExp = wrapper->ToExp();
	wrapper = nullptr;

	/*if( dynamic_cast<CNewObjectExpression*>( statement->rightOperand ) ||
		dynamic_cast<CNewIntArrayExpression*>( statement->rightOperand ) ) {
		wrapper = new CStmConverter( new MOVE( new MEM( leftExp ), rightExp ) );
	} else {*/
		wrapper = new CStmConverter( new MOVE( leftExp, rightExp ) );
	//}
}

void CTranslateVisitor::Visit( CPrintStatement *statement ) {
	statement->operand->Accept( this );
	IExp* printExp = wrapper->ToExp();
	wrapper = nullptr;

	NAME* printName =  new NAME( 
		new CLabel( CSymbol::GetSymbol( "System.out.println" ) ) );
	CExpList* args = new CExpList( printExp, nullptr );
	IExp* printCall = new CALL( printName, args );
	wrapper = new CExpConverter( printCall );
}

void CTranslateVisitor::Visit( CIdExpression *expression ) {
	CSymbol* name = CSymbol::GetSymbol( expression->name );
	wrapper = new CExpConverter( 
		curFrame->FindVariable( name )->GetExp() );
}

void CTranslateVisitor::Visit( CBinaryExpression *expression ) {

	expression->leftOperand->Accept( this );
	IExp* leftExp = wrapper->ToExp();
	
	expression->rightOperand->Accept( this );
	IExp* rightExp = wrapper->ToExp();

	switch (expression->operation) {
		case enums::ADD:
			wrapper = new CExpConverter(
				new BINOP( enums::BO_ADD, leftExp, rightExp ) );
			break;
		case enums::SUB:
			wrapper = new CExpConverter(
				new BINOP( enums::BO_SUB, leftExp, rightExp ) );
			break;
		case enums::MUL:
			wrapper = new CExpConverter(
				new BINOP( enums::BO_MUL, leftExp, rightExp ) );
			break;
		default:
			assert( false );
	}
}

void CTranslateVisitor::Visit( CNumberExpression *expression ) {
	wrapper = new CExpConverter( new CONST( expression->number ) );
}

void CTranslateVisitor::Visit( CBinaryBooleanExpression *expression ) {

	expression->leftOperand->Accept( this );
	IExp* leftExp = wrapper->ToExp();
	
	expression->rightOperand->Accept( this );
	IExp* rightExp = wrapper->ToExp();

	switch (expression->operation) {
		case enums::LESS:
			wrapper = new CRelConverter( enums::LT, leftExp, rightExp );
			break;
		case enums::GREATER:
			wrapper = new CRelConverter( enums::GT, leftExp, rightExp );
			break;
		case enums::AND:
			wrapper = new CAndConverter( leftExp, rightExp );
			break;
		case enums::OR:
			wrapper = new COrConverter( leftExp, rightExp );
			break;
		default:
			assert( false );
	}
}

void CTranslateVisitor::Visit( CBooleanExpression *expression ) {
	if( expression->value ) {
		wrapper = new CExpConverter( new CONST( 1 ) );
	} else {
		wrapper = new CExpConverter( new CONST( 0 ) );
	}
}

void CTranslateVisitor::Visit( CThisExpression *expression ) {
	wrapper = new CExpConverter( new TEMP( curFrame->ThisPointer() ) );
}

void CTranslateVisitor::Visit( CNewObjectExpression *expression ) {

	CClassSymbol* objClass = table->GetClassByName( expression->objTypeId->name );
	NAME* newName = new NAME( new CLabel( CSymbol::GetSymbol( "new" ) ) );
	CALL* newCall = new CALL( newName, 
		new CExpList( new BINOP(enums::BO_MUL,
			new CONST( objClass->fields.Size() ), 
			new CONST( CFrame::GetWordSize() ) ), nullptr ) );
	TEMP* objTemp = new TEMP( curFrame->ThisPointer() );

	MOVE* alloc = new MOVE( objTemp, newCall );
	wrapper = new CExpConverter( new ESEQ( alloc, objTemp ) );
}

void CTranslateVisitor::Visit( CNewIntArrayExpression *expression ) {

	expression->arrSize->Accept( this );
	IExp* sizeExp = wrapper->ToExp();
	wrapper = nullptr;

	IExp* memSizeExp = new BINOP(enums::BO_MUL,
		new BINOP( enums::BO_ADD, sizeExp, new CONST( 1 ) ), 
		new CONST( CFrame::GetWordSize() ) );

	IExp* newName = new NAME( new CLabel( CSymbol::GetSymbol( "new" ) ) );
	IExp* newCall = new CALL( newName, new CExpList( memSizeExp, nullptr ) );
	TEMP* arrTemp = new TEMP( new CTemp() );

	SEQ* memset = new SEQ( new MOVE( arrTemp, newCall ), 
		new MOVE( arrTemp, sizeExp ) );
	wrapper = new CExpConverter( new ESEQ( memset, arrTemp ) );
}

void CTranslateVisitor::Visit( CMethodCallExpression *expression ) {

	expression->base->Accept( this );
	IExp* objExp = wrapper->ToExp();
	wrapper = nullptr;

	std::string name = curClass->GetName() + "$" + expression->methodId->name;
	NAME* methodName = new NAME( new CLabel( CSymbol::GetSymbol( name ) ) );

	expList = nullptr;
	if ( expression->arg ) {
		expression->arg->Accept( this );
	}
	CExpList* args = new CExpList( objExp, expList );

	TEMP* returnTemp = new TEMP( new CTemp() );
	wrapper = new CExpConverter( new ESEQ( 
		new MOVE( returnTemp, new CALL( methodName, args ) ), returnTemp ) );
}

void CTranslateVisitor::Visit( CArrayLengthExpression *expression ) {

	expression->exp->Accept( this );
	IExp* lengthExp = wrapper->ToExp();
	wrapper = nullptr;

	TEMP* resultTemp = new TEMP( new CTemp() );
	wrapper = new CExpConverter( new ESEQ( 
		new MOVE( resultTemp, lengthExp ), resultTemp ) );
}

void CTranslateVisitor::Visit( CArrayIndexExpression *expression ) {

	expression->id->Accept( this );
	IExp* arrExp = wrapper->ToExp();
	wrapper = nullptr;
	
	expression->index->Accept( this );

	IExp* offset = new BINOP( enums::BO_MUL,
		new BINOP( enums::BO_ADD, wrapper->ToExp(), new CONST( 1 ) ),
		new CONST( CFrame::GetWordSize() ) );
	wrapper = nullptr;

	wrapper = new CExpConverter( new MEM( 
		new BINOP( enums::BO_ADD, arrExp, offset ) ) );
}

void CTranslateVisitor::Visit( CCompoundExpression *expression )
{
	expression->leftExpression->Accept( this );
	IExp* exp = wrapper->ToExp();

	if ( expression->rightExpression ) {
		expression->rightExpression->Accept( this );
	}
	
	expList = new CExpList( exp, expList );
}