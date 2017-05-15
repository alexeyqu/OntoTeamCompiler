#include "AST/TreeVisitors/CPrintVisitor.h"

void CPrintVisitor::Start( IVisitorTarget *vertex, std::string graphname ) {
    outputStream << "digraph " << graphname << " {\n";

    vertex->Accept(this);

    outputStream << "\n}";
}

void CPrintVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CPrintVisitor::Visit( CGoal *goal )
{
    long goalId = generateId(goal);

    outputStream << goalId << ";\n";
    outputStream << goalId << "[label = \"Goal\"];\n";

    outputStream << goalId << "->";
    goal->tmp1->Accept(this);

	if (goal->tmp2) {
		outputStream << goalId << "->";
		goal->tmp2->Accept(this);
	}
}

void CPrintVisitor::Visit( CBuiltInType *type ) {
    long typeId = generateId(type);

    outputStream << typeId << ";\n";
    
    outputStream << typeId << "[label = \"" << type->ToString() << "\" ];\n";
}

void CPrintVisitor::Visit( CUserType *type ) {
    long typeId = generateId(type);

    outputStream << typeId << ";\n";
    outputStream << typeId << "[label = \"" << type->name << "\" ];\n";
}

void CPrintVisitor::Visit( CVariable *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"VarDeclNtt\"];\n";

    outputStream << entityId << "->";
    entity->type->Accept(this);

    outputStream << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundVariable *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundVariableNtt\"];\n";

    if( entity->var1 ) {
        if( entity->var1->var1 ) {
            outputStream << entityId << "->";
            entity->var1->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->var1->var2->Accept(this);
        }
    }

    outputStream << entityId << "->";
    entity->var2->Accept(this);
}

void CPrintVisitor::Visit( CArgument *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"ArgumentNtt\"];\n";

    outputStream << entityId << "->";
    entity->type->Accept(this);

    outputStream << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundArgument *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundArgumentNtt\"];\n";

	outputStream << entityId << ";\n";
   	entity->arg1->Accept(this);
	
	if( entity->arg2 ) {
		outputStream << entityId << "->";
		entity->arg2->Accept( this );
	}
}

void CPrintVisitor::Visit( CMethod *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"MethodNtt\"];\n";

    outputStream << entityId << "->";
    entity->returnType->Accept(this);

    outputStream << entityId << "->";
    entity->id->Accept(this);

    if( entity->arguments ) {
    	if( entity->arguments->arg1 ) {
			outputStream << entityId << "->";
			entity->arguments->Accept(this);
		} else {
			outputStream << entityId << "->";
			entity->arguments->arg2->Accept(this);
		}
	}

    if( entity->variables ) {
        if( entity->variables->var1 ) {
            outputStream << entityId << "->";
            entity->variables->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->variables->var2->Accept(this);
        }
    }

    if( entity->statements ) {
        if( entity->statements->leftStatement ) {
            outputStream << entityId << "->";
            entity->statements->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->statements->rightStatement->Accept(this);
        }
    }

    outputStream << entityId << "->";
    entity->returnExpression->Accept(this);
}

void CPrintVisitor::Visit( CCompoundMethod *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundMethodNtt\"];\n";

    if( entity->method1 ) {
        if( entity->method1->method1 ) {
            outputStream << entityId << "->";
            entity->method1->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->method1->method2->Accept(this);
        }
    }

    outputStream << entityId << "->";
    entity->method2->Accept(this);
}

void CPrintVisitor::Visit( CMainClass *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"MainClassNtt\"];\n";

    outputStream << entityId << "->";
    entity->name->Accept(this);

    outputStream << entityId << "->";
    entity->cmdArgs->Accept(this);

    outputStream << entityId << "->";
    entity->statement->Accept(this);
}

void CPrintVisitor::Visit( CClass *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"ClassNtt\"];\n";

    outputStream << entityId << "->";
    entity->name->Accept(this);

    if( entity->parentName ) {
        outputStream << entityId << "->";
        entity->parentName->Accept(this);
    }

    if( entity->fields ) {
        if( entity->fields->var1 ) {
            outputStream << entityId << "->";
            entity->fields->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->fields->var2->Accept(this);
        }
    }

    if( entity->methods ) {
        if( entity->methods->method1 ) {
            outputStream << entityId << "->";
            entity->methods->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->methods->method2->Accept(this);
        }
    }
}

void CPrintVisitor::Visit( CCompoundClass *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundClassNtt\"];\n";

    if( entity->class1 ) {
        if( entity->class1->class1 ) {
            outputStream << entityId << "->";
            entity->class1->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->class1->class2->Accept(this);
        }
    }

    outputStream << entityId << "->";
    entity->class2->Accept(this);
}


void CPrintVisitor::Visit( CCompoundStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"CompoundStm\"];\n";

    if(statement->leftStatement) {
        outputStream << stmId << "->";
        statement->leftStatement->Accept(this);
    }

    if(statement->rightStatement) {
        outputStream << stmId << "->";
        statement->rightStatement->Accept(this);
    }
}

void CPrintVisitor::Visit( CAssignStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"AssignStm\"];\n";

    outputStream << stmId << "->";
    statement->leftOperand->Accept(this);

    outputStream << stmId << "->";
    statement->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CPrintStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"PrintStm\"];\n";

    outputStream << stmId << "->";
    statement->operand->Accept(this);
}

void CPrintVisitor::Visit( CIfStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"IfStm\"];\n";

    outputStream << stmId << "->";
    statement->expression->Accept(this);

    outputStream << stmId << "->";
    statement->thenStatement->Accept(this);

    outputStream << stmId << "->";
    statement->elseStatement->Accept(this);
}

void CPrintVisitor::Visit( CWhileStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"WhileStm\"];\n";

    outputStream << stmId << "->";
    statement->expression->Accept(this);

    outputStream << stmId << "->";
    statement->loopStatement->Accept(this);
}

void CPrintVisitor::Visit( CIdExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"IdExp\"];\n";

    long nameId = generateId(&expression->name);
    outputStream << exprId << "->" << nameId << ";\n";
    outputStream << nameId << "[label = \"" << expression->name << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"BinExp\"];\n";

    outputStream << exprId << "->";
    expression->leftOperand->Accept(this);

    outputStream << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TArithmeticOperation::ADD:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"+\" ];\n";
            break;

        case enums::TArithmeticOperation::SUB:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"-\" ];\n";
            break;

        case enums::TArithmeticOperation::MUL:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"*\" ];\n";
            break;

        case enums::TArithmeticOperation::DIV:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"/\" ];\n";
            break;        
    }

    outputStream << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CNumberExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"NumExp\"];\n";

    long numberId = generateId(&expression->number);
    outputStream << exprId << "->" << numberId << ";\n";
    outputStream << numberId << "[label = \"" << expression->number << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryBooleanExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"BinBoolExp\"];\n";

    outputStream << exprId << "->";
    expression->leftOperand->Accept(this);

    outputStream << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TBooleanOperation::AND:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"AND\" ];\n";
            break;

        case enums::TBooleanOperation::OR:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"OR\" ];\n";
            break;
        case enums::TBooleanOperation::LESS:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"<\" ];\n";
            break;

        case enums::TBooleanOperation::GREATER:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \">\" ];\n";
            break;
    }

    outputStream << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CBooleanExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"BoolExp\"];\n";

    long valueId = generateId(&expression->value);
    outputStream << exprId << "->" << valueId << ";\n";
    outputStream << valueId << "[label = \"" << expression->value << "\"];\n";
}

void CPrintVisitor::Visit( CThisExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ThisExp\"];\n";

    long addressId = generateId(&expression->address);
    outputStream << exprId << "->" << addressId << ";\n";
    outputStream << addressId << "[label = \"" << expression->address << "\"];\n";
}

void CPrintVisitor::Visit( CNewObjectExpression *expression ) {
    long newObjId = generateId(expression);

    outputStream << newObjId << "\n";
    outputStream << newObjId << "[label = \"NewObjExp\"];\n";

    outputStream << newObjId << "->";
    expression->objTypeId->Accept(this);
}

void CPrintVisitor::Visit( CNewIntArrayExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"NewIntArrayExp\"];\n";

    outputStream << exprId << "->";
    expression->arrSize->Accept(this);
}

void CPrintVisitor::Visit( CMethodCallExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"MethodCallExp\"];\n";

    outputStream << exprId << "->";
    expression->base->Accept(this);

    outputStream << exprId << "->";
    expression->methodId->Accept(this);

    if(expression->arg) {
        outputStream << exprId << "->";
        expression->arg->Accept(this);        
    }
}

void CPrintVisitor::Visit( CArrayLengthExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ArrayLengthExp\"];\n";

    outputStream << exprId << "->";
    expression->exp->Accept(this);
}

void CPrintVisitor::Visit( CArrayIndexExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ArrayIndexExp\"];\n";

    outputStream << exprId << "->";
    expression->id->Accept(this);

    outputStream << exprId << "->";
    expression->index->Accept(this);
}

void CPrintVisitor::Visit( CCompoundExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"CompoundExp\"];\n";

    if(expression->leftExpression) {
        outputStream << exprId << "->";
        expression->leftExpression->Accept(this);
    }

    if(expression->rightExpression) {
        outputStream << exprId << "->";
        expression->rightExpression->Accept(this);
    }
}

std::size_t  CPrintVisitor::generateId( void *entity )
{
    if( entity == nullptr )
    {
        assert(!"Error in CPrintVisitor::generateId : nullptr");
    }

    return reinterpret_cast<long>( entity ); // TODO move to std::hash
}