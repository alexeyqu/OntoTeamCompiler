#include "CTypeCheckerVisitor.h"


void CTypeCheckerVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept(this);
}

void CTypeCheckerVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CTypeCheckerVisitor::Visit( CGoal *goal ) {
    goal->tmp1->Accept(this);
    goal->tmp2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CBuiltInType *type ) {
}

void CTypeCheckerVisitor::Visit( CUserType *type ) {
}

void CTypeCheckerVisitor::Visit( CVariable *entity ) {
    entity->type->Accept(this);
    entity->id->Accept(this);
}

void CTypeCheckerVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->var1 ) {
        entity->var2->Accept(this);
    }
    entity->var2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CArgument *entity ) {
    entity->type->Accept(this);
    entity->id->Accept(this);
}

void CTypeCheckerVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->arg1 ) {
    	entity->arg1->Accept(this);
	}
    entity->arg2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CMethod *entity ) {
    entity->returnType->Accept(this);
    entity->id->Accept(this);
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
}

void CTypeCheckerVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->method1 ) {
            entity->method1->Accept(this);
    }
    entity->method2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CMainClass *entity ) {
    entity->name->Accept(this);
    entity->cmdArgs->Accept(this);
    entity->statement->Accept(this);
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