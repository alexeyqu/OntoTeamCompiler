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
    program->getRoot()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CGoal *goal )
{
    goal->getLeft()->Accept( this );

    goal->getRight()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CType *type ) {
}

void CTypeCheckerVisitor::Visit( CVariable *entity ) {
    CType *varType = entity->getType();
    if( jiveEnv->typeTable->lookup( varType ) == nullptr ) 
    {
        outputStream << OUT_COORDINATES( entity )
        << "Error: Unknown type of variable \"" << entity->getString() << "\": " << varType->getString() << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->getNextVariable() ) {
        entity->getNextVariable()->Accept( this );
    }
    entity->getVariable()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CArgument *entity ) {
    CType *argType = entity->getType();
    if( jiveEnv->typeTable->lookup( argType ) == nullptr ) 
    {
        outputStream << OUT_COORDINATES( entity )
        << "Error: Unknown type of variable \"" << entity->getString() << "\": " << argType->getString() << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->getNextArgument() ) {
    	entity->getNextArgument()->Accept( this );
	}
    entity->getArgument()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CMethod *entity ) {
 //   curMethodSymbol = curClassSymbol->lookupMethod( entity );
	// assert( curMethodSymbol );

    if( entity->getArguments() ) {
    	entity->getArguments()->Accept( this );
	}

    if( entity->getVariables() ) {
        entity->getVariables()->Accept( this );
    }

    if( entity->getStatements() ) {
        entity->getStatements()->Accept( this );
    }

    entity->getReturnExpression()->Accept( this );

	// CType *retExpType = entity->returnExpression->type;

	// if( jiveEnv->typeTable->lookup( retExpType ) ) {
	// 	outputStream << OUT_COORDINATES( entity )
	// 		<< "Error: Return type of method \"" << "FIXIT" /*curMethodName */
	// 		<< "\" is of unknown type \"" << entity->returnType->getSymbol()->get()  << "\".\n";
	// 	// curMethodName = "";
	// 	return;
	// }
	// if( retExpType != entity->returnType ) {
	// 	outputStream << OUT_COORDINATES( entity ) 
	// 		<< "Error: Type of return expression doesn't match "
	// 		<< "method \"" <<  "FIXIT" /*curMethodName */ << "\" return type.\n"
	// 		<< "Expected: \"" << entity->returnType->getSymbol()->get()  << "\". Found: \"" << retExpType->getSymbol()->get()  << "\".\n";
	// }
	// curMethodName = "";
}

void CTypeCheckerVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->getNextMethod() ) {
		entity->getNextMethod()->Accept( this );
    }
    entity->getMethod()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CMainClass *entity ) {
    curClassSymbol = jiveEnv->classTable->lookup( entity );
    assert( curClassSymbol != nullptr );

    entity->getMethods()->getMethod()->Accept( this );

    curMethodSymbol = nullptr;
}

void CTypeCheckerVisitor::Visit( CClass *entity ) {
    curClassSymbol = jiveEnv->classTable->lookup( entity );
    
    if( entity->getParentId() ) {
        if( jiveEnv->classTable->lookup( entity->getParentSymbol() ) == nullptr ) {
            outputStream << OUT_COORDINATES( entity->getParentId() )
                << "Error: unknown base class \"" 
                << entity->getParentString() << "\" for class \"" 
                << entity->getString() << "\"\n";
        }

        CClassSymbol *parentClassSymbol = jiveEnv->classTable->lookup( entity->getParentSymbol() );

        while( parentClassSymbol ) {
            if( curClassSymbol == parentClassSymbol ) {
                outputStream << OUT_COORDINATES( entity->getParentId() )
                    << "Error: cyclic inheritance for class \"" 
                    << entity->getString() << "\" detected.\n";
                break;
            }

            parentClassSymbol = parentClassSymbol->getBaseClass();
        }
    }

    if( entity->getFields() ) {
		entity->getFields()->Accept( this );
    }

    if( entity->getMethods() ) {
		entity->getMethods()->Accept( this );
    }
}

void CTypeCheckerVisitor::Visit( CCompoundClass *entity ) {
    if( entity->getNextClass() ) {
        entity->getNextClass()->Accept( this );
    }
    entity->getClass()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CCompoundStatement *statement ) {
    if(statement->getLeftStatement()) {
        statement->getLeftStatement()->Accept( this );
    }

    if(statement->getRightStatement()) {
        statement->getRightStatement()->Accept( this );
    }
}

void CTypeCheckerVisitor::Visit( CAssignStatement *statement ) {
    statement->getLValue()->Accept( this );
    statement->getRValue()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CPrintStatement *statement ) {
    statement->getExpression()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CIfStatement *statement ) {
    statement->getExpression()->Accept( this );
    statement->getThenStatement()->Accept( this );
    statement->getElseStatement()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CWhileStatement *statement ) {
    statement->getExpression()->Accept( this );
    statement->getStatement()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CIdExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CBinaryExpression *expression ) {
    expression->getLeftOperand()->Accept( this );
    expression->getRightOperand()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CNumberExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CBinaryBooleanExpression *expression ) {
    expression->getLeftOperand()->Accept( this );
    expression->getRightOperand()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CBooleanExpression *expression ) {
 
 }

void CTypeCheckerVisitor::Visit( CThisExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CNewObjectExpression *expression ) {
    expression->getClassId()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CNewIntArrayExpression *expression ) {

}

void CTypeCheckerVisitor::Visit( CMethodCallExpression *expression ) {
    expression->getBaseExpression()->Accept( this );
    expression->getMethodId()->Accept( this );

    if(expression->getArguments()) {
        expression->getArguments()->Accept( this );        
    }
}

void CTypeCheckerVisitor::Visit( CArrayLengthExpression *expression ) {
    expression->getValue()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CArrayIndexExpression *expression ) {
    expression->getArrayId()->Accept( this );
    expression->getArrayIndex()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CCompoundExpression *expression ) {
    if(expression->getLeftExpression()) {
        expression->getLeftExpression()->Accept( this );
    }

    if(expression->getRightExpression()) {
        expression->getRightExpression()->Accept( this );
    }
}

void CTypeCheckerVisitor::Visit( CVoidExpression *expression ) {
}

}