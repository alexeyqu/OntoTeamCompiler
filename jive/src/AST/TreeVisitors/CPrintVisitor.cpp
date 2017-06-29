#include "CPrintVisitor.h"

namespace AST 
{

void CPrintVisitor::Start( IVisitorTarget *vertex, std::string graphname ) {
    outputStream << "digraph " << graphname << " {\n";

    vertex->Accept(this);

    outputStream << "\n}";
}

void CPrintVisitor::Visit( CProgram *program ) {
    program->getRoot()->Accept(this);
}

void CPrintVisitor::Visit( CGoal *goal )
{
    long goalId = generateId(goal);

    outputStream << goalId << ";\n";
    outputStream << goalId << "[label = \"Goal\", shape = \"doublecircle\"];\n";

    outputStream << goalId << "->";
    goal->getLeft()->Accept(this);

    outputStream << goalId << "->";
    goal->getRight()->Accept(this);
}

void CPrintVisitor::Visit( CType *type ) {
    long typeId = generateId(type);

    outputStream << typeId << ";\n";
    outputStream << typeId << "[label = \"" << type->getSymbol()->getString() << "\", shape = \"diamond\" ];\n";
}

void CPrintVisitor::Visit( CVariable *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"VarDeclNtt\", shape = \"box\"];\n";

    outputStream << entityId << "->";
    entity->getType()->Accept(this);

    outputStream << entityId << "->";
    entity->getId()->Accept(this);
}

void CPrintVisitor::Visit( CCompoundVariable *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundVariableNtt\", shape = \"hexagon\"];\n";

    if( entity->getNextVariable() ) {
        if( entity->getNextVariable()->getNextVariable() ) {
            outputStream << entityId << "->";
            entity->getNextVariable()->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->getNextVariable()->getVariable()->Accept(this);
        }
    }

    outputStream << entityId << "->";
    entity->getVariable()->Accept(this);
}

void CPrintVisitor::Visit( CArgument *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"ArgumentNtt\", shape = \"box\"];\n";

    outputStream << entityId << "->";
    entity->getType()->Accept(this);

    outputStream << entityId << "->";
    entity->getId()->Accept(this);
}

void CPrintVisitor::Visit( CCompoundArgument *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundArgumentNtt\", shape = \"hexagon\"];\n";

    if( entity->getNextArgument() ) {
    	if( entity->getNextArgument()->getNextArgument() ) {
			outputStream << entityId << "->";
			entity->getNextArgument()->Accept(this);
		} else {
			outputStream << entityId << "->";
			entity->getNextArgument()->getArgument()->Accept(this);
		}
	}

    outputStream << entityId << "->";
    entity->getArgument()->Accept(this);
}

void CPrintVisitor::Visit( CMethod *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"MethodNtt\", shape = \"box\"];\n";

    outputStream << entityId << "->";
    entity->getReturnType()->Accept(this);

    outputStream << entityId << "->";
    entity->getId()->Accept(this);

    if( entity->getArguments() ) {
    	if( entity->getArguments()->getNextArgument() ) {
			outputStream << entityId << "->";
			entity->getArguments()->Accept(this);
		} else {
			outputStream << entityId << "->";
			entity->getArguments()->getArgument()->Accept(this);
		}
	}

    if( entity->getVariables() ) {
        if( entity->getVariables()->getNextVariable() ) {
            outputStream << entityId << "->";
            entity->getVariables()->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->getVariables()->getVariable()->Accept(this);
        }
    }

    if( entity->getStatements() ) {
        if( entity->getStatements()->getLeftStatement() ) {
            outputStream << entityId << "->";
            entity->getStatements()->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->getStatements()->getRightStatement()->Accept(this);
        }
    }

    if( entity->getReturnExpression() ) {
		outputStream << entityId << "->";
    	entity->getReturnExpression()->Accept(this);
	}
}

void CPrintVisitor::Visit( CCompoundMethod *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundMethodNtt\", shape = \"hexagon\"];\n";

    if( entity->getNextMethod() ) {
        if( entity->getNextMethod()->getNextMethod() ) {
            outputStream << entityId << "->";
            entity->getNextMethod()->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->getNextMethod()->getMethod()->Accept(this);
        }
    }

    outputStream << entityId << "->";
    entity->getMethod()->Accept(this);
}

void CPrintVisitor::Visit( CMainClass *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"MainClassNtt\", shape = \"box\"];\n";

    outputStream << entityId << "->";
    entity->getId()->Accept(this);

	outputStream << entityId << "->";
	entity->getMethods()->getMethod()->Accept(this);
}

void CPrintVisitor::Visit( CClass *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"ClassNtt\", shape = \"box\"];\n";

    outputStream << entityId << "->";
    entity->getId()->Accept(this);

    if( entity->getParentId() ) {
        outputStream << entityId << "->";
        entity->getParentId()->Accept(this);
    }

    if( entity->getFields() ) {
        if( entity->getFields()->getNextVariable() ) {
            outputStream << entityId << "->";
            entity->getFields()->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->getFields()->getVariable()->Accept(this);
        }
    }

    if( entity->getMethods() ) {
        if( entity->getMethods()->getNextMethod() ) {
            outputStream << entityId << "->";
            entity->getMethods()->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->getMethods()->getMethod()->Accept(this);
        }
    }
}

void CPrintVisitor::Visit( CCompoundClass *entity ) {
    long entityId = generateId(entity);

    outputStream << entityId << ";\n";
    outputStream << entityId << "[label = \"CompoundClassNtt\", shape = \"hexagon\"];\n";

    if( entity->getNextClass() ) {
        if( entity->getNextClass()->getNextClass() ) {
            outputStream << entityId << "->";
            entity->getNextClass()->Accept(this);
        } else {
            outputStream << entityId << "->";
            entity->getNextClass()->getClass()->Accept(this);
        }
    }

    outputStream << entityId << "->";
    entity->getClass()->Accept(this);
}


void CPrintVisitor::Visit( CCompoundStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"CompoundStm\", shape = \"polygon\"];\n";

    if(statement->getLeftStatement()) {
        outputStream << stmId << "->";
        statement->getLeftStatement()->Accept(this);
    }

    if(statement->getRightStatement()) {
        outputStream << stmId << "->";
        statement->getRightStatement()->Accept(this);
    }
}

void CPrintVisitor::Visit( CAssignStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"AssignStm\", shape = \"ellipse\"];\n";

    outputStream << stmId << "->";
    statement->getLValue()->Accept(this);

    outputStream << stmId << "->";
    statement->getRValue()->Accept(this);
}

void CPrintVisitor::Visit( CPrintStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"PrintStm\", shape = \"ellipse\"];\n";

    outputStream << stmId << "->";
    statement->getExpression()->Accept(this);
}

void CPrintVisitor::Visit( CIfStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"IfStm\", shape = \"ellipse\"];\n";

    outputStream << stmId << "->";
    statement->getExpression()->Accept(this);

    outputStream << stmId << "->";
    statement->getThenStatement()->Accept(this);

    outputStream << stmId << "->";
    statement->getElseStatement()->Accept(this);
}

void CPrintVisitor::Visit( CWhileStatement *statement ) {
    long stmId = generateId(statement);

    outputStream << stmId << ";\n";
    outputStream << stmId << "[label = \"WhileStm\", shape = \"ellipse\"];\n";

    outputStream << stmId << "->";
    statement->getExpression()->Accept(this);

    outputStream << stmId << "->";
    statement->getStatement()->Accept(this);
}

void CPrintVisitor::Visit( CIdExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"IdExp\", shape = \"circle\"];\n";

    long nameId = generateId(expression->getSymbol());
    outputStream << exprId << "->" << nameId << ";\n";
    outputStream << nameId << "[label = \"" << expression->getString() << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"BinExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->getLeftOperand()->Accept(this);

    outputStream << exprId << "->";
    long operationId = generateId(expression) + 1;
    switch(expression->getOperator()) {
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
    expression->getRightOperand()->Accept(this);
}

void CPrintVisitor::Visit( CNumberExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"NumExp\", shape = \"circle\"];\n";

    long numberId = generateId(expression) + 1;
    outputStream << exprId << "->" << numberId << ";\n";
    outputStream << numberId << "[label = \"" << expression->getValue() << "\"];\n";
}

void CPrintVisitor::Visit( CBinaryBooleanExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"BinBoolExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->getLeftOperand()->Accept(this);

    outputStream << exprId << "->";
    long operationId = generateId(expression) + 1;
    switch(expression->getOperator()) {
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
    expression->getRightOperand()->Accept(this);
}

void CPrintVisitor::Visit( CBooleanExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"BoolExp\", shape = \"circle\"];\n";

    long valueId = generateId(expression) + 1;
    outputStream << exprId << "->" << valueId << ";\n";
    outputStream << valueId << "[label = \"" << expression->getValue() << "\"];\n";
}

void CPrintVisitor::Visit( CThisExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ThisExp\", shape = \"circle\"];\n";

    long addressId = generateId(expression) + 1;
    outputStream << exprId << "->" << addressId << ";\n";
    outputStream << addressId << "[label = \"" << expression->getThisAddress() << "\"];\n";
}

void CPrintVisitor::Visit( CNewObjectExpression *expression ) {
    long newObjId = generateId(expression);

    outputStream << newObjId << "\n";
    outputStream << newObjId << "[label = \"NewObjExp\", shape = \"circle\"];\n";

    outputStream << newObjId << "->";
    expression->getClassId()->Accept(this);
}

void CPrintVisitor::Visit( CNewIntArrayExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"NewIntArrayExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->getArrSize()->Accept(this);
}

void CPrintVisitor::Visit( CMethodCallExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"MethodCallExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->getBaseExpression()->Accept(this);

    outputStream << exprId << "->";
    expression->getMethodId()->Accept(this);

    if(expression->getArguments()) {
        outputStream << exprId << "->";
        expression->getArguments()->Accept(this);        
    }
}

void CPrintVisitor::Visit( CArrayLengthExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ArrayLengthExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->getValue()->Accept(this);
}

void CPrintVisitor::Visit( CArrayIndexExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"ArrayIndexExp\", shape = \"circle\"];\n";

    outputStream << exprId << "->";
    expression->getArrayId()->Accept(this);

    outputStream << exprId << "->";
    expression->getArrayIndex()->Accept(this);
}

void CPrintVisitor::Visit( CCompoundExpression *expression ) {
    long exprId = generateId(expression);

    outputStream << exprId << ";\n";
    outputStream << exprId << "[label = \"CompoundExp\", shape = \"circle\"];\n";

    if(expression->getLeftExpression()) {
        outputStream << exprId << "->";
        expression->getLeftExpression()->Accept(this);
    }

    if(expression->getRightExpression()) {
        outputStream << exprId << "->";
        expression->getRightExpression()->Accept(this);
    }
}

void CPrintVisitor::Visit( CVoidExpression *expression ) {
	long exprId = generateId(expression);

    outputStream << exprId << "\n";
    outputStream << exprId << "[label = \"VoidExp\", shape = \"circle\"];\n";
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