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
    if( jiveEnv->typeMap->lookup( varType ) == nullptr ) 
    {
        outputStream << OUT_COORDINATES( entity )
        << "Error: Unknown type of variable " << entity->getString() << ": " << varType->getString() << ".\n";
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
    if( jiveEnv->typeMap->lookup( argType ) == nullptr ) 
    {
        outputStream << OUT_COORDINATES( entity )
        << "Error: Unknown type of argument " << entity->getString() << ": " << argType->getString() << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->getNextArgument() ) {
    	entity->getNextArgument()->Accept( this );
	}
    entity->getArgument()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CMethod *entity ) {
   curMethodSymbol = curClassSymbol->lookupMethod( entity->getSymbol() );

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

	CType *returnExpressionType = entity->getReturnExpression()->getType();
	if( jiveEnv->typeMap->lookup( entity->getReturnType() ) == nullptr ) {
		outputStream << OUT_COORDINATES( entity )
			<< "Error: Return type of method \"" << curMethodSymbol->getString() 
			<< "\" is of unknown type \"" << entity->getReturnType()->getString() << "\".\n";

		curMethodSymbol = nullptr;
		return;
	}
	if( !( *returnExpressionType == *entity->getReturnType() ) ) {
		outputStream << OUT_COORDINATES( entity ) 
			<< "Error: Type of return expression doesn't match "
			<< "method \"" << curMethodSymbol->getString() << "\" return type.\n"
			<< "Expected: \"" << entity->getReturnType()->getString()  << "\". Found: \"" << returnExpressionType->getString()  << "\".\n";
	}

	curMethodSymbol = nullptr;
}

void CTypeCheckerVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->getNextMethod() ) {
		entity->getNextMethod()->Accept( this );
    }
    entity->getMethod()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CMainClass *entity ) {
    curClassSymbol = jiveEnv->classMap->lookup( entity );
    assert( curClassSymbol != nullptr );

    entity->getMethods()->getMethod()->Accept( this );

    curMethodSymbol = nullptr;
}

void CTypeCheckerVisitor::Visit( CClass *entity ) {
    curClassSymbol = jiveEnv->classMap->lookup( entity );
    
    if( entity->getParentId() ) {
        if( jiveEnv->classMap->lookup( entity->getParentSymbol() ) == nullptr ) {
            outputStream << OUT_COORDINATES( entity->getParentId() )
				<< "Error: unknown base class \"" 
				<< entity->getParentString() << "\" for class \"" 
				<< entity->getString() << "\"\n";
        }

        CClassSymbol *parentClassSymbol = jiveEnv->classMap->lookup( entity->getParentSymbol() );

        while( parentClassSymbol ) {
            if( curClassSymbol == parentClassSymbol ) {
                outputStream << OUT_COORDINATES( entity->getParentId() )
					<< "Error: cyclic inheritance for class \"" 
					<< entity->getString()  << "\" detected.\n";
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
	CType *lType = statement->getLValue()->getType();
    statement->getRValue()->Accept( this );
	CType *rType = statement->getRValue()->getType();

	if( !( *lType == *rType ) ) {
		outputStream << OUT_COORDINATES( statement )
			<< "Error: Incorrect types of assign statement expressions.\n"
			<< "Lvalue: \"" << lType->getString() << "\", RValue: \"" << lType->getString() <<"\".\n";
	}
}

void CTypeCheckerVisitor::Visit( CPrintStatement *statement ) {
    statement->getExpression()->Accept( this );
	CType *expressionType = statement->getExpression()->getType();

	if( expressionType->getPrimitiveType() != TType::INTEGER ) {
		outputStream << OUT_COORDINATES( statement )
			<< "Error: Incorrect type of expression in Print statement.\n"
			<< "Expected: \"int\". Found \"" << expressionType->getString() << "\"\n";
	}
}

void CTypeCheckerVisitor::Visit( CIfStatement *statement ) {
    statement->getExpression()->Accept( this );
	CType *expressionType = statement->getExpression()->getType();

	if( expressionType->getPrimitiveType() != TType::BOOLEAN ) {
		outputStream << OUT_COORDINATES( statement )
			<< "Error: Incorrect type of expression in If statement.\n"
			<< "Expected: \"boolean\". Found \"" << expressionType->getString() << "\".\n";
	}

    statement->getThenStatement()->Accept( this );
    statement->getElseStatement()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CWhileStatement *statement ) {
    statement->getExpression()->Accept( this );
	CType *expressionType = statement->getExpression()->getType();

	if( expressionType->getPrimitiveType() != TType::BOOLEAN ) {
		outputStream << OUT_COORDINATES( statement )
			<< "Error: Incorrect type of expression in While statement.\n"
			<< "Expected: \"boolean\". Found \"" << expressionType->getString() << "\"\n";
	}

	statement->getStatement()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CIdExpression *expression ) {
	CSymbol *symbol = expression->getSymbol();

	if( curClassSymbol->lookupField( symbol ) ) {
		expression->setType( jiveEnv->typeMap->lookup( curClassSymbol->lookupField( symbol )->getTypeSymbol() ) );
		return;
	}

	if( curClassSymbol->getBaseClass() ) {
		if( curClassSymbol->getBaseClass()->lookupField( symbol ) ) {
			expression->setType( jiveEnv->typeMap->lookup( curClassSymbol->getBaseClass()->lookupField( symbol )->getTypeSymbol() ) );
			return;
		}
	}

	if( curMethodSymbol == nullptr ) {
		outputStream << OUT_COORDINATES( expression )
			<< "Error: Unknown identifier \"" << symbol->getString() << "\"\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, symbol ) );
		return;
	}

	if( curMethodSymbol->lookupArgument( symbol ) == nullptr ) {
		if( curMethodSymbol->lookupVariable( symbol ) == nullptr ) {
			outputStream << OUT_COORDINATES( expression ) 
				<< "Error: Unknown identifier \"" << symbol->getString() << "\"\n";
			expression->setType( new CType( TType::UNKNOWNTYPE, symbol ) );
			return;
		}

		expression->setType( jiveEnv->typeMap->lookup( curMethodSymbol->lookupVariable( symbol )->getTypeSymbol() ) );
	} else {
		expression->setType( jiveEnv->typeMap->lookup( curMethodSymbol->lookupArgument( symbol )->getTypeSymbol() ) );
	}

	if( symbol->getString() == expression->getType()->getString() ) {
		outputStream << OUT_COORDINATES( expression ) 
			<< "Error: The name of variable \"" << symbol->getString()  << "\" and its type are the same.\n";
	}
}

void CTypeCheckerVisitor::Visit( CBinaryExpression *expression ) {
    expression->getLeftOperand()->Accept( this );
	CType *leftType = expression->getLeftOperand()->getType();
    expression->getRightOperand()->Accept( this );
	CType *rightType = expression->getRightOperand()->getType();
	
	if( leftType->getPrimitiveType() != TType::INTEGER || 
		rightType->getPrimitiveType() != TType::INTEGER ) 
	{
		outputStream << OUT_COORDINATES( expression )
			<< "Error: Incorrect types of binary operation.\n"
			<< "Expected: \"int\" and \"int\". "
			<<"Found \"" << leftType->getString()  << "\" and \"" << rightType->getString() <<"\".\n";
	}
	
	expression->setType( leftType );
}

void CTypeCheckerVisitor::Visit( CNumberExpression *expression ) {
	expression->setType( new CType( TType::INTEGER, CSymbol::makeSymbol( "int" ) ) );
}

void CTypeCheckerVisitor::Visit( CBinaryBooleanExpression *expression ) {
    expression->getLeftOperand()->Accept( this );
	CType *leftType = expression->getLeftOperand()->getType();
    expression->getRightOperand()->Accept( this );
	CType *rightType = expression->getRightOperand()->getType();
	jive::TBooleanOperation operation = expression->getOperator();
	
	if( operation == jive::TBooleanOperation::LESS ||
		operation == jive::TBooleanOperation::GREATER )
	{
		if( leftType->getPrimitiveType() != TType::INTEGER || 
			rightType->getPrimitiveType() != TType::INTEGER ) 
		{
			outputStream << OUT_COORDINATES( expression ) << " </> "
				<< "Error: Incorrect types of binary operation.\n"
				<< "Expected: \"int\" and \"int\". "
				<<"Found \"" << leftType->getString() << "\" and \"" << rightType->getString() <<"\".\n";
		}
	} else {
		if( leftType->getPrimitiveType() != TType::BOOLEAN || 
			rightType->getPrimitiveType() != TType::BOOLEAN ) 
		{
			outputStream << OUT_COORDINATES( expression )
				<< "Error: Incorrect types of binary operation.\n"
				<< "Expected: \"boolean\" and \"boolean\". "
				<<"Found \"" << leftType->getString() << "\" and \"" << rightType->getString() <<"\".\n";
		}
	}
	
	expression->setType( new CType( TType::BOOLEAN, CSymbol::makeSymbol( "boolean" ) ) );
}

void CTypeCheckerVisitor::Visit( CBooleanExpression *expression ) {
	expression->setType( new CType( TType::BOOLEAN, CSymbol::makeSymbol( "boolean" ) ) );
 }

void CTypeCheckerVisitor::Visit( CThisExpression *expression ) {
	expression->setType( jiveEnv->typeMap->lookup( curClassSymbol->getTypeSymbol() ) );
}

void CTypeCheckerVisitor::Visit( CNewObjectExpression *expression ) {
    CSymbol *objTypeSymbol = expression->getClassId()->getSymbol();
	if( jiveEnv->classMap->lookup( objTypeSymbol ) == nullptr ) {
		outputStream << OUT_COORDINATES( expression->getClassId() )
			<< "Error: Unknown class \"" << objTypeSymbol->getString() << "\"\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, objTypeSymbol ) );
		return;
	}

	expression->setType( jiveEnv->typeMap->lookup( jiveEnv->classMap->lookup( objTypeSymbol )->getTypeSymbol() ) );
}

void CTypeCheckerVisitor::Visit( CNewIntArrayExpression *expression ) {
	expression->getArrSize()->Accept( this );
	CType *arrSizeType = expression->getArrSize()->getType();

	if( arrSizeType->getPrimitiveType() != TType::INTEGER ) {
		outputStream << OUT_COORDINATES( expression->getArrSize() )
			<< "Error: Incorrect type of array size.\n"
			<< "Expected: \"int\". "
			<<"Found \"" << arrSizeType->getString() << "\".\n";
	}

	expression->setType( new CType( TType::INTEGERARRAY, CSymbol::makeSymbol( "int[]" ) ) );
}

void CTypeCheckerVisitor::Visit( CMethodCallExpression *expression ) {
    expression->getBaseExpression()->Accept( this );
	CType *baseType = expression->getBaseExpression()->getType();
	if( jiveEnv->classMap->lookup( baseType->getSymbol() ) == nullptr ) {
		outputStream << OUT_COORDINATES( expression->getBaseExpression() )
			<< "Error: Unknown class \"" << baseType->getString() 
			<< "\" method call.\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, baseType->getSymbol() ) );
		return;
	}

	CClassSymbol *baseClassSymbol = jiveEnv->classMap->lookup( baseType->getSymbol() );

	CMethodSymbol *methodSymbol = baseClassSymbol->lookupMethod( expression->getMethodId()->getSymbol() );
	if( methodSymbol == nullptr ) {
		outputStream << OUT_COORDINATES( expression->getMethodId() )
			<< "Error: Method \"" << expression->getMethodId()->getString() << "\" in class \""
			<< baseType->getString()  << "\" doesn't exist.\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, expression->getMethodId()->getSymbol() ) );
		return;
	}

	curCallArgTypes.clear();
    if( expression->getArguments() ) {
        expression->getArguments()->Accept( this );        
    }

	if( curCallArgTypes.size() != methodSymbol->getArgumentsCount() ) {
		outputStream << OUT_COORDINATES( expression->getMethodId() )
			<< "Error: Method \"" << expression->getMethodId()->getString() << "\" of class \"" 
			<< baseType->getString() << "\" expected to take " << methodSymbol->getArgumentsCount() 
			<< " arguments but takes " << curCallArgTypes.size() << " arguments\n";

		expression->setType( jiveEnv->typeMap->lookup( methodSymbol->getTypeSymbol() ) );
		return;
	}

	for( int i = 0; i < curCallArgTypes.size(); i++ ) {
		bool match = true;

		// CTypeSymbol *callArgType = jiveEnv->typeMap->lookup( curCallArgTypes[i] );
		// CTypeSymbol *protoType = methodSymbol->getArguments()[i]->getTypeSymbol();
		
		// if( *callArgType == *protoType ) {
		// 	match = true;
		// } else {
		// 	// FIXIT perform upcast of callArgType
		// }

		// if( !match ) {
		// 	outputStream << OUT_COORDINATES( curCallArgTypes[i] )
		// 		<< " CMethodCallExpression::getArguments() " << ( i + 1 )
		// 		<< " Expected: " << protoType->getString() << " Found: " << callArgType->getString() << "\n";
				// 	<< "Error: " << i + 1 << "th argument's type of method \"" 
				// << methodName << "\" call of class \"" 
				// << baseName << "\" doesn't match to method argument type.\n"
				// << "Expected: \"" << mehodArgumentsTypes[i]->ToString() 
				// << "\". Found \"" << curCallArgumentsTypes[i]->ToString() << "\".\n";
		// }
	}
	
	expression->setType( jiveEnv->typeMap->lookup( methodSymbol->getTypeSymbol() ) );
}

void CTypeCheckerVisitor::Visit( CArrayLengthExpression *expression ) {
    expression->getValue()->Accept( this );
	CType *arrLengthType = expression->getValue()->getType();
	if( arrLengthType->getPrimitiveType() != TType::INTEGERARRAY ) {
		outputStream << OUT_COORDINATES( expression->getValue() )
			<< "Error: Incorrect type of array.\n"
			<< "Expected: \"int[]\". "
			<< "Found \"" << arrLengthType->getString() << "\".\n";
	}

	expression->setType( new CType( TType::INTEGER, CSymbol::makeSymbol( "int" ) ) );
}

void CTypeCheckerVisitor::Visit( CArrayIndexExpression *expression ) {
    expression->getArrayId()->Accept( this );
	CType *arrayNodeType = expression->getArrayId()->getType();
	if( arrayNodeType->getPrimitiveType() != TType::INTEGERARRAY ) {
		outputStream << OUT_COORDINATES( expression->getArrayId() )
			<< "Error: Incorrect type of array.\n"
			<< "Expected: \"int[]\". "
			<< "Found \"" << arrayNodeType->getString() << "\".\n";
	}

    expression->getArrayIndex()->Accept( this );
	CType *arrayIndexType = expression->getArrayIndex()->getType();
	if( arrayIndexType->getPrimitiveType() != TType::INTEGER ) {
		outputStream << OUT_COORDINATES( expression->getArrayIndex() )
			<< "Error: Incorrect type of array index.\n"
			<< "Expected: \"int\". "
			<< "Found \"" << arrayIndexType->getString() << "\".\n";
	}

	expression->setType( new CType( TType::INTEGER, CSymbol::makeSymbol( "int" ) ) );
}

void CTypeCheckerVisitor::Visit( CCompoundExpression *expression ) {
    if(expression->getLeftExpression()) {
        expression->getLeftExpression()->Accept( this );
    }

    if(expression->getRightExpression()) {
        expression->getRightExpression()->Accept( this );
		expression->getRightExpression()->getType()->coordinates = expression->getRightExpression()->coordinates;
		curCallArgTypes.push_back( expression->getRightExpression()->getType() );
    }
}

void CTypeCheckerVisitor::Visit( CVoidExpression *expression ) {
	expression->setType( new CType( TType::VOID, CSymbol::makeSymbol( "void" ) ) );
}

}