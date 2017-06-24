#include "CPrintVisitor.h"

namespace AST 
{

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
    outputStream << goalId << "[label = \"Goal\", shape = \"doublecircle\"];\n";

    outputStream << goalId << "->";
    goal->tmp1->Accept(this);

    outputStream << goalId << "->";
    goal->tmp2->Accept(this);
}

void CPrintVisitor::Visit( CBuiltInType *type ) {
    long typeId = generateId(type);

    outputStream << typeId << ";\n";
    
    outputStream << typeId << "[label = \"" << type->getSymbol().get() << "\", shape = \"diamond\" ];\n";
}

void CPrintVisitor::Visit( CUserType *type ) {
    long typeId = generateId(type);

    outputStream << typeId << ";\n";
    outputStream << typeId << "[label = \"" << type->getSymbol().get() << "\", shape = \"diamond\" ];\n";
}

void CPrintVisitor::Visit( CVariable *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"VarDeclNtt\", shape = \"box\"];\n";

    outputStream << entityId << "->";
    entity->type->Accept(this);

    outputStream << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundVariable *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundVariableNtt\", shape = \"hexagon\"];\n";

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
    outputStream << entityId << "[label = \"ArgumentNtt\", shape = \"box\"];\n";

    outputStream << entityId << "->";
    entity->type->Accept(this);

    outputStream << entityId << "->";
    entity->id->Accept(this);
}

void CPrintVisitor::Visit( CCompoundArgument *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundArgumentNtt\", shape = \"hexagon\"];\n";

    if( entity->arg1 ) {
    	if( entity->arg1->arg1 ) {
			outputStream << entityId << "->";
			entity->arg1->Accept(this);
		} else {
			outputStream << entityId << "->";
			entity->arg1->arg2->Accept(this);
		}
	}

    outputStream << entityId << "->";
    entity->arg2->Accept(this);
}

void CPrintVisitor::Visit( CMethod *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"MethodNtt\", shape = \"box\"];\n";

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
    outputStream << entityId << "[label = \"CompoundMethodNtt\", shape = \"hexagon\"];\n";

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
    outputStream << entityId << "[label = \"MainClassNtt\", shape = \"box\"];\n";

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
    outputStream << entityId << "[label = \"ClassNtt\", shape = \"box\"];\n";

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
    outputStream << entityId << "[label = \"CompoundClassNtt\", shape = \"hexagon\"];\n";

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
    outputStream << stmId << "[label = \"CompoundStm\", shape = \"polygon\"];\n";

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
    outputStream << stmId << "[label = \"AssignStm\", shape = \"ellipse\"];\n";

    outputStream << stmId << "->";
    statement->leftOperand->Accept(this);

    outputStream << stmId << "->";
    statement->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CPrintStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"PrintStm\", shape = \"ellipse\"];\n";

    outputStream << stmId << "->";
    statement->operand->Accept(this);
}

void CPrintVisitor::Visit( CIfStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"IfStm\", shape = \"ellipse\"];\n";

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
    outputStream << stmId << "[label = \"WhileStm\", shape = \"ellipse\"];\n";

    outputStream << stmId << "->";
    statement->expression->Accept(this);

    outputStream << stmId << "->";
    statement->loopStatement->Accept(this);
}

void CPrintVisitor::Visit( CIdExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"IdExp\", shape = \"circle\"];\n";

    long nameId = generateId(&expression->name);
    outputStream << exprId << "->" << nameId << ";\n";
    outputStream << nameId << "[label = \"" << expression->getName() << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"BinExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->leftOperand->Accept(this);

    outputStream << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case jive::TArithmeticOperation::ADD:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"+\" ];\n";
            break;

        case jive::TArithmeticOperation::SUB:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"-\" ];\n";
            break;

        case jive::TArithmeticOperation::MUL:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"*\" ];\n";
            break;

        case jive::TArithmeticOperation::DIV:
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
    outputStream << exprId << "[label = \"NumExp\", shape = \"circle\"];\n";

    long numberId = generateId(&expression->number);
    outputStream << exprId << "->" << numberId << ";\n";
    outputStream << numberId << "[label = \"" << expression->number << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryBooleanExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"BinBoolExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->leftOperand->Accept(this);

    outputStream << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case jive::TBooleanOperation::AND:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"AND\" ];\n";
            break;

        case jive::TBooleanOperation::OR:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"OR\" ];\n";
            break;
        case jive::TBooleanOperation::LESS:
            outputStream << operationId << ";\n";
            outputStream << operationId << "[label = \"<\" ];\n";
            break;

        case jive::TBooleanOperation::GREATER:
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
    outputStream << exprId << "[label = \"BoolExp\", shape = \"circle\"];\n";

    long valueId = generateId(&expression->value);
    outputStream << exprId << "->" << valueId << ";\n";
    outputStream << valueId << "[label = \"" << expression->value << "\"];\n";
}

void CPrintVisitor::Visit( CThisExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ThisExp\", shape = \"circle\"];\n";

    long addressId = generateId(&expression->address);
    outputStream << exprId << "->" << addressId << ";\n";
    outputStream << addressId << "[label = \"" << expression->address << "\"];\n";
}

void CPrintVisitor::Visit( CNewObjectExpression *expression ) {
    long newObjId = generateId(expression);

    outputStream << newObjId << "\n";
    outputStream << newObjId << "[label = \"NewObjExp\", shape = \"circle\"];\n";

    outputStream << newObjId << "->";
    expression->objTypeId->Accept(this);
}

void CPrintVisitor::Visit( CNewIntArrayExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"NewIntArrayExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->arrSize->Accept(this);
}

void CPrintVisitor::Visit( CMethodCallExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"MethodCallExp\", shape = \"circle\"];\n";

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
    outputStream << exprId << "[label = \"ArrayLengthExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->exp->Accept(this);
}

void CPrintVisitor::Visit( CArrayIndexExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ArrayIndexExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->id->Accept(this);

    outputStream << exprId << "->";
    expression->index->Accept(this);
}

void CPrintVisitor::Visit( CCompoundExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"CompoundExp\", shape = \"circle\"];\n";

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

    return reinterpret_cast<long>( entity ); // FIXIT move to std::hash
}

}