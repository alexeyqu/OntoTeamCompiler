#include "CPrintVisitor.h"

// TODO: fix .dot labels

void CPrintVisitor::Start( IVisitorTarget *vertex, std::string graphname ) {
    std::cout << "digraph " << graphname << " {\n";

    vertex->Accept(this);

    std::cout << "\n}";
}

void CPrintVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CPrintVisitor::Visit( CGoal *goal )
{
    long goalId = generateId(goal);

    std::cout << goalId << ";\n";
    std::cout << goalId << "[label = \"Goal\"];\n";

    std::cout << goalId << "->";
    goal->tmp1->Accept(this);

    std::cout << goalId << "->";
    goal->tmp2->Accept(this);
}

void CPrintVisitor::Visit( CBuiltInType *type ) {
    long typeId = generateId(type);

    std::cout << typeId << ";\n";
    switch(type->type) {
    case enums::TType::INTEGER:
        std::cout << typeId << "[label = \"int\" ];\n";
        break;
    case enums::TType::BOOLEAN:
        std::cout << typeId << "[label = \"bool\" ];\n";
        break;
    case enums::TType::STRING:
        std::cout << typeId << "[label = \"String\" ];\n";
        break;
    }
}

void CPrintVisitor::Visit( CUserType *type ) {
    long typeId = generateId(type);

    std::cout << typeId << ";\n";
    std::cout << typeId << "[label = \"" << type->typeClass->name->name << "\" ];\n";
}

void CPrintVisitor::Visit( CVariable *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"VarDeclNtt\"];\n";

    std::cout << entityId << "->";
    entity->type->Accept(this);

    std::cout << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundVariable *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"CompoundVariableNtt\"];\n";

    if( entity->var1 ) {
        if( entity->var1->var1 ) {
            std::cout << entityId << "->";
            entity->var1->Accept(this);
        } else {
            std::cout << entityId << "->";
            entity->var1->var2->Accept(this);
        }
    }

    std::cout << entityId << "->";
    entity->var2->Accept(this);
}

void CPrintVisitor::Visit( CArgument *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"ArgumentNtt\"];\n";

    std::cout << entityId << "->";
    entity->type->Accept(this);

    std::cout << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundArgument *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"CompoundArgumentNtt\"];\n";

    if( entity->arg1 ) {
    	if( entity->arg1->arg1 ) {
			std::cout << entityId << "->";
			entity->arg1->Accept(this);
		} else {
			std::cout << entityId << "->";
			entity->arg1->arg2->Accept(this);
		}
	}

    std::cout << entityId << "->";
    entity->arg2->Accept(this);
}

void CPrintVisitor::Visit( CMethod *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"MethodNtt\"];\n";

    std::cout << entityId << "->";
    entity->returnType->Accept(this);

    std::cout << entityId << "->";
    entity->id->Accept(this);

    if( entity->arguments ) {
    	if( entity->arguments->arg1 ) {
			std::cout << entityId << "->";
			entity->arguments->Accept(this);
		} else {
			std::cout << entityId << "->";
			entity->arguments->arg2->Accept(this);
		}
	}

    if( entity->variables ) {
        if( entity->variables->var1 ) {
            std::cout << entityId << "->";
            entity->variables->Accept(this);
        } else {
            std::cout << entityId << "->";
            entity->variables->var2->Accept(this);
        }
    }

    if( entity->statements ) {
        if( entity->statements->leftStatement ) {
            std::cout << entityId << "->";
            entity->statements->Accept(this);
        } else {
            std::cout << entityId << "->";
            entity->statements->rightStatement->Accept(this);
        }
    }

    std::cout << entityId << "->";
    entity->returnExpression->Accept(this);
}

void CPrintVisitor::Visit( CCompoundMethod *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"CompoundMethodNtt\"];\n";

    if( entity->method1 ) {
        if( entity->method1->method1 ) {
            std::cout << entityId << "->";
            entity->method1->Accept(this);
        } else {
            std::cout << entityId << "->";
            entity->method1->method2->Accept(this);
        }
    }

    std::cout << entityId << "->";
    entity->method2->Accept(this);
}

void CPrintVisitor::Visit( CMainClass *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"MainClassNtt\"];\n";

    std::cout << entityId << "->";
    entity->name->Accept(this);

    std::cout << entityId << "->";
    entity->cmdArgs->Accept(this);

    std::cout << entityId << "->";
    entity->statement->Accept(this);
}

void CPrintVisitor::Visit( CClass *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"ClassNtt\"];\n";

    std::cout << entityId << "->";
    entity->name->Accept(this);

    if( entity->parentName ) {
        std::cout << entityId << "->";
        entity->parentName->Accept(this);
    }

    if( entity->fields ) {
        if( entity->fields->var1 ) {
            std::cout << entityId << "->";
            entity->fields->Accept(this);
        } else {
            std::cout << entityId << "->";
            entity->fields->var2->Accept(this);
        }
    }

    if( entity->methods ) {
        if( entity->methods->method1 ) {
            std::cout << entityId << "->";
            entity->methods->Accept(this);
        } else {
            std::cout << entityId << "->";
            entity->methods->method2->Accept(this);
        }
    }
}

void CPrintVisitor::Visit( CCompoundClass *entity ) {
    long entityId = generateId(entity);

    std::cout << entityId << ";\n";
    std::cout << entityId << "[label = \"CompoundClassNtt\"];\n";

    if( entity->class1 ) {
        if( entity->class1->class1 ) {
            std::cout << entityId << "->";
            entity->class1->Accept(this);
        } else {
            std::cout << entityId << "->";
            entity->class1->class2->Accept(this);
        }
    }

    std::cout << entityId << "->";
    entity->class2->Accept(this);
}


void CPrintVisitor::Visit( CCompoundStatement *statement ) {
    long stmId = generateId(statement);

    std::cout << stmId << ";\n";
    std::cout << stmId << "[label = \"CompoundStm\"];\n";

    if(statement->leftStatement) {
        std::cout << stmId << "->";
        statement->leftStatement->Accept(this);
    }

    if(statement->rightStatement) {
        std::cout << stmId << "->";
        statement->rightStatement->Accept(this);
    }
}

void CPrintVisitor::Visit( CAssignStatement *statement ) {
    long stmId = generateId(statement);

    std::cout << stmId << ";\n";
    std::cout << stmId << "[label = \"AssignStm\"];\n";

    std::cout << stmId << "->";
    statement->leftOperand->Accept(this);

    std::cout << stmId << "->";
    statement->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CPrintStatement *statement ) {
    long stmId = generateId(statement);

    std::cout << stmId << ";\n";
    std::cout << stmId << "[label = \"PrintStm\"];\n";

    std::cout << stmId << "->";
    statement->operand->Accept(this);
}

void CPrintVisitor::Visit( CIfStatement *statement ) {
    long stmId = generateId(statement);

    std::cout << stmId << ";\n";
    std::cout << stmId << "[label = \"IfStm\"];\n";

    std::cout << stmId << "->";
    statement->expression->Accept(this);

    std::cout << stmId << "->";
    statement->thenStatement->Accept(this);

    std::cout << stmId << "->";
    statement->elseStatement->Accept(this);
}

void CPrintVisitor::Visit( CWhileStatement *statement ) {
    long stmId = generateId(statement);

    std::cout << stmId << ";\n";
    std::cout << stmId << "[label = \"WhileStm\"];\n";

    std::cout << stmId << "->";
    statement->expression->Accept(this);

    std::cout << stmId << "->";
    statement->loopStatement->Accept(this);
}

void CPrintVisitor::Visit( CIdExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"IdExp\"];\n";

    long nameId = generateId(&expression->name);
    std::cout << exprId << "->" << nameId << ";\n";
    std::cout << nameId << "[label = \"" << expression->name << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << ";\n";
    std::cout << exprId << "[label = \"BinExp\"];\n";

    std::cout << exprId << "->";
    expression->leftOperand->Accept(this);

    std::cout << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TArithmeticOperation::ADD:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \"+\" ];\n";
            break;

        case enums::TArithmeticOperation::SUB:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \"-\" ];\n";
            break;

        case enums::TArithmeticOperation::MUL:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \"*\" ];\n";
            break;

        case enums::TArithmeticOperation::DIV:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \"/\" ];\n";
            break;
    }

    std::cout << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CNumberExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"NumExp\"];\n";

    long numberId = generateId(&expression->number);
    std::cout << exprId << "->" << numberId << ";\n";
    std::cout << numberId << "[label = \"" << expression->number << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryBooleanExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << ";\n";
    std::cout << exprId << "[label = \"BinBoolExp\"];\n";

    std::cout << exprId << "->";
    expression->leftOperand->Accept(this);

    std::cout << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TBooleanOperation::AND:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \"AND\" ];\n";
            break;

        case enums::TBooleanOperation::OR:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \"OR\" ];\n";
            break;

        case enums::TBooleanOperation::LESS:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \"<\" ];\n";
            break;

        case enums::TBooleanOperation::GREATER:
            std::cout << operationId << ";\n";
            std::cout << operationId << "[label = \">\" ];\n";
            break;
    }

    std::cout << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CBooleanExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"BoolExp\"];\n";

    long valueId = generateId(&expression->value);
    std::cout << exprId << "->" << valueId << ";\n";
    std::cout << valueId << "[label = \"" << expression->value << "\"];\n";
}

void CPrintVisitor::Visit( CThisExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"ThisExp\"];\n";

    long addressId = generateId(&expression->address);
    std::cout << exprId << "->" << addressId << ";\n";
    std::cout << addressId << "[label = \"" << expression->address << "\"];\n";
}

void CPrintVisitor::Visit( CNewObjectExpression *expression ) {
    long newObjId = generateId(expression);

    std::cout << newObjId << "\n";
    std::cout << newObjId << "[label = \"NewObjExp\"];\n";

    std::cout << newObjId << "->";
    expression->objTypeId->Accept(this);
}

void CPrintVisitor::Visit( CNewIntArrayExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"NewIntArrayExp\"];\n";

    long sizeId = generateId(&expression->arrSize);
    std::cout << exprId << "->" << sizeId << ";\n";
    std::cout << sizeId << "[label = \"" << expression->arrSize << "\"];\n";
}

void CPrintVisitor::Visit( CMethodCallExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"MethodCallExp\"];\n";

    std::cout << exprId << "->";
    expression->base->Accept(this);

    std::cout << exprId << "->";
    expression->methodId->Accept(this);

    if(expression->arg) {
        std::cout << exprId << "->";
        expression->arg->Accept(this);        
    }
}

void CPrintVisitor::Visit( CArrayLengthExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"ArrayLengthExp\"];\n";

    std::cout << exprId << "->";
    expression->exp->Accept(this);
}

void CPrintVisitor::Visit( CArrayIndexExpression *expression ) {
    long exprId = generateId(expression);

    std::cout << exprId << "\n";
    std::cout << exprId << "[label = \"ArrayIndexExp\"];\n";

    std::cout << exprId << "->";
    expression->id->Accept(this);

    std::cout << exprId << "->";
    expression->index->Accept(this);
}

std::size_t  CPrintVisitor::generateId( void *entity )
{
    if( entity == nullptr )
    {
        assert(!"Error in CPrintVisitor::generateId : nullptr");
    }

    return reinterpret_cast<long>( entity ); // TODO move to std::hash
}