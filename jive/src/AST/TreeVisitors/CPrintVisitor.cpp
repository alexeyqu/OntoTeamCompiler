#include "CPrintVisitor.h"

// TODO: fix .dot labels

void CPrintVisitor::Start( IVisitorTarget *vertex, std::string graphname ) {
    std::string filename = graphname + ".dot";
    file.open(filename.c_str());

    file << "digraph " << graphname << " {\n";

    vertex->Accept(this);

    file << "\n}";

    file.close();
}

void CPrintVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CPrintVisitor::Visit( CGoal *goal )
{
    long goalId = generateId(goal);

    file << goalId << ";\n";
    file << goalId << "[label = \"Goal\"];\n";

    file << goalId << "->";
    goal->tmp1->Accept(this);

    file << goalId << "->";
    goal->tmp2->Accept(this);
}

void CPrintVisitor::Visit( CType *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    switch(entity->type) {
    case enums::TType::INTEGER:
        file << entityId << "[label = \"int\" ];\n";
        break;

    case enums::TType::BOOLEAN:
        file << entityId << "[label = \"bool\" ];\n";
        break;
    case enums::TType::STRING:
        file << entityId << "[label = \"String\" ];\n";
        break;
    }
}

void CPrintVisitor::Visit( CArray *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"Array[" << entity->size << "]\" ];\n";
    
    file << entityId << "->";
    entity->type->Accept(this);
}

void CPrintVisitor::Visit( CVariable *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"VarDeclNtt\"];\n";

    file << entityId << "->";
    entity->type->Accept(this);

    file << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundVariable *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"CompoundVariableNtt\"];\n";

    if( entity->var1 ) {
        if( entity->var1->var1 ) {
            file << entityId << "->";
            entity->var1->Accept(this);
        } else {
            file << entityId << "->";
            entity->var1->var2->Accept(this);
        }
    }

    file << entityId << "->";
    entity->var2->Accept(this);
}

void CPrintVisitor::Visit( CArgument *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"ArgumentNtt\"];\n";

    file << entityId << "->";
    entity->type->Accept(this);

    file << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundArgument *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"CompoundArgumentNtt\"];\n";

    if( entity->arg1 ) {
    	if( entity->arg1->arg1 ) {
			file << entityId << "->";
			entity->arg1->Accept(this);
		} else {
			file << entityId << "->";
			entity->arg1->arg2->Accept(this);
		}
	}

    file << entityId << "->";
    entity->arg2->Accept(this);
}

void CPrintVisitor::Visit( CMethod *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"MethodNtt\"];\n";

    file << entityId << "->";
    entity->returnType->Accept(this);

    file << entityId << "->";
    entity->id->Accept(this);

    if( entity->arguments ) {
    	if( entity->arguments->arg1 ) {
			file << entityId << "->";
			entity->arguments->Accept(this);
		} else {
			file << entityId << "->";
			entity->arguments->arg2->Accept(this);
		}
	}

    if( entity->variables ) {
        if( entity->variables->var1 ) {
            file << entityId << "->";
            entity->variables->Accept(this);
        } else {
            file << entityId << "->";
            entity->variables->var2->Accept(this);
        }
    }

    if( entity->statements ) {
        if( entity->statements->leftStatement ) {
            file << entityId << "->";
            entity->statements->Accept(this);
        } else {
            file << entityId << "->";
            entity->statements->rightStatement->Accept(this);
        }
    }

    file << entityId << "->";
    entity->returnExpression->Accept(this);
}

void CPrintVisitor::Visit( CCompoundMethod *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"CompoundMethodNtt\"];\n";

    if( entity->method1 ) {
        if( entity->method1->method1 ) {
            file << entityId << "->";
            entity->method1->Accept(this);
        } else {
            file << entityId << "->";
            entity->method1->method2->Accept(this);
        }
    }

    file << entityId << "->";
    entity->method2->Accept(this);
}

void CPrintVisitor::Visit( CMainClass *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"MainClassNtt\"];\n";

    file << entityId << "->";
    entity->name->Accept(this);

    file << entityId << "->";
    entity->cmdArgs->Accept(this);

    file << entityId << "->";
    entity->statement->Accept(this);
}

void CPrintVisitor::Visit( CClass *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"ClassNtt\"];\n";

    file << entityId << "->";
    entity->name->Accept(this);

    if( entity->parentName ) {
        file << entityId << "->";
        entity->parentName->Accept(this);
    }

    if( entity->fields ) {
        if( entity->fields->var1 ) {
            file << entityId << "->";
            entity->fields->Accept(this);
        } else {
            file << entityId << "->";
            entity->fields->var2->Accept(this);
        }
    }

    if( entity->methods ) {
        if( entity->methods->method1 ) {
            file << entityId << "->";
            entity->methods->Accept(this);
        } else {
            file << entityId << "->";
            entity->methods->method2->Accept(this);
        }
    }
}

void CPrintVisitor::Visit( CCompoundClass *entity ) {
    long entityId = generateId(entity);

    file << entityId << ";\n";
    file << entityId << "[label = \"CompoundClassNtt\"];\n";

    if( entity->class1 ) {
        if( entity->class1->class1 ) {
            file << entityId << "->";
            entity->class1->Accept(this);
        } else {
            file << entityId << "->";
            entity->class1->class2->Accept(this);
        }
    }

    file << entityId << "->";
    entity->class2->Accept(this);
}


void CPrintVisitor::Visit( CCompoundStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"CompoundStm\"];\n";

    file << stmId << "->";
    statement->leftStatement->Accept(this);

    file << stmId << "->";
    statement->rightStatement->Accept(this);
}

void CPrintVisitor::Visit( CAssignStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"AssignStm\"];\n";

    file << stmId << "->";
    statement->leftOperand->Accept(this);

    file << stmId << "->";
    statement->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CPrintStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"PrintStm\"];\n";

    file << stmId << "->";
    statement->operand->Accept(this);
}

void CPrintVisitor::Visit( CIfStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"IfStm\"];\n";

    file << stmId << "->";
    statement->expression->Accept(this);

    file << stmId << "->";
    statement->thenStatement->Accept(this);

    file << stmId << "->";
    statement->elseStatement->Accept(this);
}

void CPrintVisitor::Visit( CWhileStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"WhileStm\"];\n";

    file << stmId << "->";
    statement->expression->Accept(this);

    file << stmId << "->";
    statement->loopStatement->Accept(this);
}

void CPrintVisitor::Visit( CIdExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"IdExp\"];\n";

    long nameId = generateId(&expression->name);
    file << exprId << "->" << nameId << ";\n";
    file << nameId << "[label = \"" << expression->name << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << ";\n";
    file << exprId << "[label = \"BinExp\"];\n";

    file << exprId << "->";
    expression->leftOperand->Accept(this);

    file << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TArithmeticOperation::ADD:
            file << operationId << ";\n";
            file << operationId << "[label = \"+\" ];\n";
            break;

        case enums::TArithmeticOperation::SUB:
            file << operationId << ";\n";
            file << operationId << "[label = \"-\" ];\n";
            break;

        case enums::TArithmeticOperation::MUL:
            file << operationId << ";\n";
            file << operationId << "[label = \"*\" ];\n";
            break;

        case enums::TArithmeticOperation::DIV:
            file << operationId << ";\n";
            file << operationId << "[label = \"/\" ];\n";
            break;
    }

    file << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CNumberExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"NumExp\"];\n";

    long numberId = generateId(&expression->number);
    file << exprId << "->" << numberId << ";\n";
    file << numberId << "[label = \"" << expression->number << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryBooleanExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << ";\n";
    file << exprId << "[label = \"BinBoolExp\"];\n";

    file << exprId << "->";
    expression->leftOperand->Accept(this);

    file << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TBooleanOperation::AND:
            file << operationId << ";\n";
            file << operationId << "[label = \"AND\" ];\n";
            break;

        case enums::TBooleanOperation::OR:
            file << operationId << ";\n";
            file << operationId << "[label = \"OR\" ];\n";
            break;

        case enums::TBooleanOperation::LESS:
            file << operationId << ";\n";
            file << operationId << "[label = \"<\" ];\n";
            break;

        case enums::TBooleanOperation::GREATER:
            file << operationId << ";\n";
            file << operationId << "[label = \">\" ];\n";
            break;
    }

    file << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CBooleanExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"BoolExp\"];\n";

    long valueId = generateId(&expression->value);
    file << exprId << "->" << valueId << ";\n";
    file << valueId << "[label = \"" << expression->value << "\"];\n";
}

void CPrintVisitor::Visit( CThisExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"ThisExp\"];\n";

    long addressId = generateId(&expression->address);
    file << exprId << "->" << addressId << ";\n";
    file << addressId << "[label = \"" << expression->address << "\"];\n";
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

std::size_t  CPrintVisitor::generateId( void *entity )
{
    if( entity == nullptr )
    {
        assert(!"Error in CPrintVisitor::generateId : nullptr");
    }

    return reinterpret_cast<long>( entity ); // TODO move to std::hash
}