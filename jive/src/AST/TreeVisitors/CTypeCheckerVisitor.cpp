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
        << "Error: Unknown type of variable " << entity->getString() << ": " << argType->getString() << ".\n";
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

	if( jiveEnv->typeMap->lookup( returnExpressionType ) == nullptr ) {
		outputStream << OUT_COORDINATES( entity )
			<< " CMethod::return type of " << curMethodSymbol->getString()
			<< " is of unknown type " << returnExpressionType->getString()  << ".\n";
		curMethodSymbol = nullptr;
		return;
	}
	if( !( *returnExpressionType == *entity->getReturnType() ) ) {
		outputStream << OUT_COORDINATES( entity ) 
			<< " CMethod::return type of " << curMethodSymbol->getString()
			<< " Expected: " << entity->getReturnType()->getString()  << ". Found: " << returnExpressionType->getString()  << ".\n";
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
                << " CClass::getParentSymbol() " 
                << entity->getParentString() << " is unknown for " 
                << entity->getString() << "\n";
        }

        CClassSymbol *parentClassSymbol = jiveEnv->classMap->lookup( entity->getParentSymbol() );

        while( parentClassSymbol ) {
            if( curClassSymbol == parentClassSymbol ) {
                outputStream << OUT_COORDINATES( entity->getParentId() )
                    << " CClass::cyclic inheritance in " 
                    << entity->getString() << "\n";
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
			<< " CAssignStatement " << lType->getString() << " and " << lType->getString() << "\n";
	}
}

void CTypeCheckerVisitor::Visit( CPrintStatement *statement ) {
    statement->getExpression()->Accept( this );
	CType *expressionType = statement->getExpression()->getType();

	if( expressionType->getPrimitiveType() != TType::INTEGER ) {
		outputStream << OUT_COORDINATES( statement )
			<< " CPrintStatement " << expressionType->getString() << "\n";
	}
}

void CTypeCheckerVisitor::Visit( CIfStatement *statement ) {
    statement->getExpression()->Accept( this );
	CType *expressionType = statement->getExpression()->getType();

	if( expressionType->getPrimitiveType() != TType::BOOLEAN ) {
		outputStream << OUT_COORDINATES( statement )
			<< " CIfStatement " << "\t" << expressionType->getString() << "\n";
	}

    statement->getThenStatement()->Accept( this );
    statement->getElseStatement()->Accept( this );
}

void CTypeCheckerVisitor::Visit( CWhileStatement *statement ) {
    statement->getExpression()->Accept( this );
	CType *expressionType = statement->getExpression()->getType();

	if( expressionType->getPrimitiveType() != TType::BOOLEAN ) {
		outputStream << OUT_COORDINATES( statement )
			<< " CWhileStatement " << expressionType->getString() << "\n";
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
			<< " CIdExpression::lookupField " << symbol->getString() << "\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, symbol ) );
		return;
	}

	if( curMethodSymbol->lookupArgument( symbol ) == nullptr ) {
		if( curMethodSymbol->lookupVariable( symbol ) == nullptr ) {
			outputStream << OUT_COORDINATES( expression ) 
				<< " CIdExpression::lookupVariable " << symbol->getString() << " in method " << curMethodSymbol->getString() << "\n";
			expression->setType( new CType( TType::UNKNOWNTYPE, symbol ) );
			return;
		}

		expression->setType( jiveEnv->typeMap->lookup( curMethodSymbol->lookupVariable( symbol )->getTypeSymbol() ) );
	} else {
		expression->setType( jiveEnv->typeMap->lookup( curMethodSymbol->lookupArgument( symbol )->getTypeSymbol() ) );
	}

	if( symbol->getString() == expression->getType()->getString() ) {
		outputStream << OUT_COORDINATES( expression ) 
			<< " CIdExpression type and name collision in " << symbol->getString() << " in method " << curMethodSymbol->getString() << "\n";
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
			<< " CBinaryExpression " << leftType->getString() << " and " << rightType->getString() << "\n";
	}
	
	expression->setType( leftType );
}

void CTypeCheckerVisitor::Visit( CNumberExpression *expression ) {
	expression->setType( new CType( TType::INTEGER, new CSymbol( "int" ) ) );
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
				<< " CBinaryExpression " << leftType->getString() << " and " << rightType->getString() << "\n";
		}
	} else {
		if( leftType->getPrimitiveType() != TType::BOOLEAN || 
			rightType->getPrimitiveType() != TType::BOOLEAN ) 
		{
			outputStream << OUT_COORDINATES( expression )
				<< " CBinaryExpression " << leftType->getString() << " and " << rightType->getString() << "\n";
		}
	}
	
	expression->setType( new CType( TType::BOOLEAN, new CSymbol( "boolean" ) ) );
}

void CTypeCheckerVisitor::Visit( CBooleanExpression *expression ) {
	expression->setType( new CType( TType::BOOLEAN, new CSymbol( "boolean" ) ) );
 }

void CTypeCheckerVisitor::Visit( CThisExpression *expression ) {
	expression->setType( jiveEnv->typeMap->lookup( curClassSymbol->getTypeSymbol() ) );
}

void CTypeCheckerVisitor::Visit( CNewObjectExpression *expression ) {
    CSymbol *objTypeSymbol = expression->getClassId()->getSymbol();
	if( jiveEnv->classMap->lookup( objTypeSymbol ) == nullptr ) {
		outputStream << OUT_COORDINATES( expression->getClassId() )
			<< " CNewObjectExpression::getClassId() " << objTypeSymbol->getString() << "\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, objTypeSymbol ) );
		return;
	}

	// std::cerr << OUT_COORDINATES( expression->getClassId() ) <<
	// 	" CNewObjectExpression::getClassId() " << jiveEnv->typeMap->lookup( jiveEnv->classMap->lookup( objTypeSymbol )->getTypeSymbol() )->getString() 
	// 	<< "\n" << objTypeSymbol->getString() << "\n\n";

	expression->setType( jiveEnv->typeMap->lookup( jiveEnv->classMap->lookup( objTypeSymbol )->getTypeSymbol() ) );
}

void CTypeCheckerVisitor::Visit( CNewIntArrayExpression *expression ) {
	expression->getArrSize()->Accept( this );
	CType *arrSizeType = expression->getArrSize()->getType();

	if( arrSizeType->getPrimitiveType() != TType::INTEGER ) {
		outputStream << OUT_COORDINATES( expression->getArrSize() )
			<< " CNewIntArrayExpression " << arrSizeType->getString() << "\n";
	}

	expression->setType( new CType( TType::INTEGERARRAY, new CSymbol( "int[]" ) ) );
}

void CTypeCheckerVisitor::Visit( CMethodCallExpression *expression ) {
    expression->getBaseExpression()->Accept( this );
	CType *baseType = expression->getBaseExpression()->getType();
	if( jiveEnv->classMap->lookup( baseType->getSymbol() ) == nullptr ) {
		outputStream << OUT_COORDINATES( expression->getBaseExpression() )
			<< " CMethodCallExpression::getBaseExpression() " << baseType->getString() << "\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, baseType->getSymbol() ) );
		return;
	}

	CClassSymbol *baseClassSymbol = jiveEnv->classMap->lookup( baseType->getSymbol() );

	// std::cerr << baseClassSymbol->getString() << '\n';
	// std::cerr << expression->getMethodId()->getString() << '\n';
	CMethodSymbol *methodSymbol = baseClassSymbol->lookupMethod( expression->getMethodId()->getSymbol() );
	// std::cerr << methodSymbol->getString() << '\n';
	if( methodSymbol == nullptr ) {
		outputStream << OUT_COORDINATES( expression->getMethodId() )
			<< " CMethodCallExpression::getMethodId() " << expression->getMethodId()->getString() << "\n";

		expression->setType( new CType( TType::UNKNOWNTYPE, expression->getMethodId()->getSymbol() ) );
		return;
	}

	curCallArgTypes.clear();
    if( expression->getArguments() ) {
        expression->getArguments()->Accept( this );        
    }

	if( curCallArgTypes.size() != methodSymbol->getArgumentsCount() ) {
		outputStream << OUT_COORDINATES( expression->getMethodId() )
			<< " CMethodCallExpression::getArgumentsCount() " << methodSymbol->getArgumentsCount() 
			<< " Found: " << curCallArgTypes.size() << "\n";

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
		// }
	}
	
	expression->setType( jiveEnv->typeMap->lookup( methodSymbol->getTypeSymbol() ) );
	// std::cerr << expression->getType()->getString() << "\n\n";
}

void CTypeCheckerVisitor::Visit( CArrayLengthExpression *expression ) {
    expression->getValue()->Accept( this );
	CType *arrLengthType = expression->getValue()->getType();
	if( arrLengthType->getPrimitiveType() != TType::INTEGERARRAY ) {
		outputStream << OUT_COORDINATES( expression->getValue() )
			<< " CArrayLengthExpression " << arrLengthType->getString() << "\n";
	}

	expression->setType( new CType( TType::INTEGER, new CSymbol( "int" ) ) );
}

void CTypeCheckerVisitor::Visit( CArrayIndexExpression *expression ) {
    expression->getArrayId()->Accept( this );
	CType *arrayNodeType = expression->getArrayId()->getType();
	if( arrayNodeType->getPrimitiveType() != TType::INTEGERARRAY ) {
		outputStream << OUT_COORDINATES( expression->getArrayId() )
			<< " CArrayIndexExpression::getArrayId() " << arrayNodeType->getString() << "\n";
	}

    expression->getArrayIndex()->Accept( this );
	CType *arrayIndexType = expression->getArrayIndex()->getType();
	if( arrayIndexType->getPrimitiveType() != TType::INTEGER ) {
		outputStream << OUT_COORDINATES( expression->getArrayIndex() )
			<< " CArrayIndexExpression::getArrayIndex() " << arrayIndexType->getString() << "\n";
	}

	expression->setType( new CType( TType::INTEGER, new CSymbol( "int" ) ) );
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
	expression->setType( new CType( TType::VOID, new CSymbol( "void" ) ) );
}

}