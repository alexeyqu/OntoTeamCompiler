#include "CTypeCheckerVisitor.h"
#include "CJiveEnvironment.h"

namespace AST 
{

using jive::TType;
using jive::CJiveEnvironment;

#define OUT_COORDINATES( entity ) \
	"[" << entity->coordinates.first_line << ", " << entity->coordinates.first_column << "] " 

void CTypeCheckerVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept( this );
}

void CTypeCheckerVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept( this );
}

void CTypeCheckerVisitor::Visit( CGoal *goal )
{
    goal->left->Accept(this);

    goal->right->Accept(this);
}

void CTypeCheckerVisitor::Visit( CType *type ) {
}

void CTypeCheckerVisitor::Visit( CVariable *entity ) {
    CType *varType = entity->type;
    if( jiveEnv->typeTable->lookup( varType ) == nullptr ) 
    {
        outputStream << OUT_COORDINATES( entity )
        << "Error: Unknown type of variable \"" << entity->id->name->get() << "\": " << varType->getSymbol()->get() << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->var1 ) {
        entity->var1->Accept(this);
    }
    entity->var2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CArgument *entity ) {
    CType *argType = entity->type;
    if( jiveEnv->typeTable->lookup( argType ) == nullptr ) 
    {
        outputStream << OUT_COORDINATES( entity )
        << "Error: Unknown type of variable \"" << entity->id->name->get() << "\": " << argType->getSymbol()->get() << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->arg1 ) {
    	entity->arg1->Accept(this);
	}
    entity->arg2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CMethod *entity ) {
 //   curMethodSymbol = curClassSymbol->lookupMethod( entity );
	// assert( curMethodSymbol );

    if( entity->arguments ) {
    	entity->arguments->Accept(this);
	}

    if( entity->variables ) {
        entity->variables->Accept(this);
    }

    if( entity->statements ) {
        entity->statements->Accept(this);
    }

    entity->returnExpression->Accept(this);

	CType *retExpType = entity->returnExpression->type;

	if( jiveEnv->typeTable->lookup( retExpType ) ) {
		std::cerr << OUT_COORDINATES( entity )
			<< "Error: Return type of method \"" << "FIXIT" /*curMethodName */
			<< "\" is of unknown type \"" << entity->returnType->getSymbol()->get()  << "\".\n";
		// curMethodName = "";
		return;
	}
	if( retExpType != entity->returnType ) {
		std::cerr << OUT_COORDINATES( entity ) 
			<< "Error: Type of return expression doesn't match "
			<< "method \"" <<  "FIXIT" /*curMethodName */ << "\" return type.\n"
			<< "Expected: \"" << entity->returnType->getSymbol()->get()  << "\". Found: \"" << retExpType->getSymbol()->get()  << "\".\n";
	}
	// curMethodName = "";
}

void CTypeCheckerVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->method1 ) {
		entity->method1->Accept(this);
    }
    entity->method2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CMainClass *entity ) {
    entity->name->Accept(this);
    entity->methods->method2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CClass *entity ) {
    entity->name->Accept(this);

    if( entity->parentName ) {
        entity->parentName->Accept(this);
    }

    if( entity->fields ) {
		entity->fields->Accept(this);
    }

    if( entity->methods ) {
		entity->methods->Accept(this);
    }
}

void CTypeCheckerVisitor::Visit( CCompoundClass *entity ) {
    if( entity->class1 ) {
        entity->class1->Accept(this);
    }
    entity->class2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CCompoundStatement *statement ) {
    if(statement->leftStatement) {
        statement->leftStatement->Accept(this);
    }

    if(statement->rightStatement) {
        statement->rightStatement->Accept(this);
    }
}

void CTypeCheckerVisitor::Visit( CAssignStatement *statement ) {
    statement->leftOperand->Accept(this);
    statement->rightOperand->Accept(this);
}

void CTypeCheckerVisitor::Visit( CPrintStatement *statement ) {
    statement->operand->Accept(this);
}

void CTypeCheckerVisitor::Visit( CIfStatement *statement ) {
    statement->expression->Accept(this);
    statement->thenStatement->Accept(this);
    statement->elseStatement->Accept(this);
}

void CTypeCheckerVisitor::Visit( CWhileStatement *statement ) {
    statement->expression->Accept(this);
    statement->loopStatement->Accept(this);
}

void CTypeCheckerVisitor::Visit( CIdExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CBinaryExpression *expression ) {
    expression->leftOperand->Accept(this);
    expression->rightOperand->Accept(this);
}

void CTypeCheckerVisitor::Visit( CNumberExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CBinaryBooleanExpression *expression ) {
    expression->leftOperand->Accept(this);
    expression->rightOperand->Accept(this);
}

void CTypeCheckerVisitor::Visit( CBooleanExpression *expression ) {
 
 }

void CTypeCheckerVisitor::Visit( CThisExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CNewObjectExpression *expression ) {
    expression->objTypeId->Accept(this);
}

void CTypeCheckerVisitor::Visit( CNewIntArrayExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CMethodCallExpression *expression ) {
    expression->base->Accept(this);
    expression->methodId->Accept(this);

    if(expression->arg) {
        expression->arg->Accept(this);        
    }
}

void CTypeCheckerVisitor::Visit( CArrayLengthExpression *expression ) {
    expression->exp->Accept(this);
}

void CTypeCheckerVisitor::Visit( CArrayIndexExpression *expression ) {
    expression->id->Accept(this);
    expression->index->Accept(this);
}

void CTypeCheckerVisitor::Visit( CCompoundExpression *expression ) {
    if(expression->leftExpression) {
        expression->leftExpression->Accept(this);
    }

    if(expression->rightExpression) {
        expression->rightExpression->Accept(this);
    }
}

void CTypeCheckerVisitor::Visit( CVoidExpression *expression ) {
}

}