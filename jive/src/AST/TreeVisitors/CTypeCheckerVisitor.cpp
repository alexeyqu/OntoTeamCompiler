#include "AST/TreeVisitors/CTypeCheckerVisitor.h"

void CTypeCheckerVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept(this);
}

void CTypeCheckerVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CTypeCheckerVisitor::Visit( CGoal *goal )
{
    goal->tmp1->Accept(this);
	if (goal->tmp2) {
		goal->tmp2->Accept( this );
	}
}

void CTypeCheckerVisitor::Visit( CBuiltInType *type ) {
}

void CTypeCheckerVisitor::Visit( CUserType *type ) {
}

void CTypeCheckerVisitor::Visit( CVariable *entity ) {
    CSymbol* varName = CSymbol::GetSymbol( entity->id->name );
    CSymbol* varType = CSymbol::GetSymbol( entity->type->ToString() );
    if( varType != CSymbol::GetSymbol( "int" ) && 
		varType != CSymbol::GetSymbol( "boolean" ) && 
		varType != CSymbol::GetSymbol( "int[]" ) &&
        !table->GetClassByName( varType ) ) {
        std::cerr << "[" << entity->coordinates.first_line << ", " 
            << entity->coordinates.first_column << "] " 
            << "Error: Unknown type of variable \"" << varName->GetString() 
			<< "\": " << varType->GetString() << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->var1 ) {
        entity->var1->Accept(this);
    }
    entity->var2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CArgument *entity ) {
    CSymbol* argName = CSymbol::GetSymbol( entity->id->name );
    CSymbol* argType = CSymbol::GetSymbol( entity->type->ToString() );
    if( argType != CSymbol::GetSymbol( "int" ) && 
		argType != CSymbol::GetSymbol( "boolean" ) && 
		argType != CSymbol::GetSymbol( "int[]" ) &&
        !table->GetClassByName( argType ) ) {
        std::cerr << "[" << entity->coordinates.first_line << ", " 
            << entity->coordinates.first_column << "] " 
            << "Error: Unknown type of argument \"" << argName->GetString() 
			<< "\": " << argType->GetString() << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundArgument *entity ) {   
    if( entity->arg1 ) {
        entity->arg1->Accept(this);
    }
    entity->arg2->Accept(this); 
}

void CTypeCheckerVisitor::Visit( CMethod *entity ) {
    curMethodName = CSymbol::GetSymbol( entity->id->name );
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
    CSymbol* retExpType = CSymbol::GetSymbol( 
		entity->returnExpression->type->ToString() );
    CSymbol* retType = CSymbol::GetSymbol( entity->returnType->ToString() );
    if( retType != CSymbol::GetSymbol( "int" ) && 
		retType != CSymbol::GetSymbol( "boolean" ) && 
		retType != CSymbol::GetSymbol( "int[]" ) &&
            !table->GetClassByName( retType ) ) {
        std::cerr << "[" << entity->returnType->coordinates.first_line << ", " 
            << entity->returnType->coordinates.first_column << "] " 
            << "Error: Return type of method \"" << curMethodName->GetString()
            << "\" is of unknown type \"" << retType->GetString()  << "\".\n";
        curMethodName = nullptr;
        return;
    }
    if( retExpType != retType ) {
        std::cerr << "[" << entity->returnExpression->coordinates.first_line << ", " 
            << entity->returnExpression->coordinates.first_column << "] " 
            << "Error: Type of return expression doesn't match "
            << "method \"" << curMethodName->GetString() << "\" return type.\n"
            << "Expected: \"" << retType->GetString()  
			<< "\". Found: \"" << retExpType->GetString()  << "\".\n";
    }
    curMethodName = nullptr;
}

void CTypeCheckerVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->method1 ) {
        entity->method1->Accept(this);
    }
    entity->method2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CMainClass *entity ) {
    CSymbol* curClassName = CSymbol::GetSymbol( entity->name->name );
    CSymbol* curMethodName = CSymbol::GetSymbol( "main" );
    entity->statement->Accept(this);
    curMethodName = nullptr;
}

void CTypeCheckerVisitor::Visit( CClass *entity ) {
    curClassName = CSymbol::GetSymbol( entity->name->name );
    if( entity->parentName ) {
        auto symbol = table->GetClassByName( entity->parentName->name );
        if( !symbol ) {
            std::cerr << "[" << entity->parentName->coordinates.first_line << ", " 
                << entity->parentName->coordinates.first_column << "] " 
                << "Error: unknown base class \"" 
                << curClassName << "\" for class \"" 
                << curClassName << "\"\n";
        }
		auto parentClassName = CSymbol::GetSymbol( entity->parentName->name );
        while( parentClassName ) {
            if( curClassName == parentClassName ) {
                std::cerr << "[" << entity->name->coordinates.first_line << ", " 
                    << entity->name->coordinates.first_column << "] " 
                    << "Error: cyclic inheritance for class \"" 
                    << curClassName << "\" detected.\n";
                break;
            }
            auto parentSymbol = table->GetClassByName( parentClassName );
            if( !parentSymbol ) {
                break;
            } else {
                parentClassName = parentSymbol->parentName;
            }
        }
    }
    if( entity->methods ) {
        entity->methods->Accept(this);
    }
    curMethodName = nullptr;
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
    CSymbol* leftExpType = CSymbol::GetSymbol( 
		statement->leftOperand->type->ToString() );
    statement->rightOperand->Accept(this);
    CSymbol* rightExpType = CSymbol::GetSymbol( 
		statement->rightOperand->type->ToString() );
    if( leftExpType != rightExpType ) {
        std::cerr << "[" << statement->coordinates.first_line << ", " 
            << statement->coordinates.first_column << "] "  
            << "Error: Incorrect types of assign statement expressions.\n"
            << "Expected: \"" << leftExpType->GetString() 
			<< "\" and \"" << leftExpType->GetString() <<"\". "
            << "Found \"" << leftExpType->GetString() 
			<< "\" and \"" << rightExpType->GetString() <<"\".\n";
    }
}

void CTypeCheckerVisitor::Visit( CPrintStatement *statement ) {
    statement->operand->Accept(this);
    CSymbol* expType = CSymbol::GetSymbol( statement->operand->type->ToString() );
    if ( expType != CSymbol::GetSymbol( "int" ) ) {
        std::cerr << "[" << statement->operand->coordinates.first_line << ", " 
            << statement->operand->coordinates.first_column << "] "  
            << "Error: Incorrect type of expression in Print statement.\n"
            << "Expected: \"int\". Found \"" << expType->GetString() << "\"\n";
    }
}

void CTypeCheckerVisitor::Visit( CIfStatement *statement ) {
    statement->expression->Accept(this);
    CSymbol* expType = CSymbol::GetSymbol( statement->expression->type->ToString() );
    if ( expType != CSymbol::GetSymbol( "boolean" ) ) {
        std::cerr << "[" << statement->expression->coordinates.first_line << ", " 
            << statement->expression->coordinates.first_column << "] "
            << "Error: Incorrect type of expression in If statement.\n"
            << "Expected: \"boolean\". Found \"" << expType->GetString() << "\"\n";
    }
    statement->thenStatement->Accept(this);
    statement->elseStatement->Accept(this);
}

void CTypeCheckerVisitor::Visit( CWhileStatement *statement ) {
    statement->expression->Accept(this);
    CSymbol* expType = CSymbol::GetSymbol( statement->expression->type->ToString() );
    if ( expType != CSymbol::GetSymbol( "boolean" ) ) {
        std::cerr << "[" << statement->expression->coordinates.first_line << ", " 
            << statement->expression->coordinates.first_column << "] "
            << "Error: Incorrect type of expression in While statement.\n"
            << "Expected: \"boolean\". Found \"" << expType->GetString() << "\"\n";
    }
    statement->loopStatement->Accept(this);
}

void CTypeCheckerVisitor::Visit( CIdExpression *expression ) {
    CSymbol* name = CSymbol::GetSymbol( expression->name );
    auto classSymbol = table->GetClassByName( curClassName );
    auto varSymbol = classSymbol->fields.GetObject( name );
    if( varSymbol ) {
        expression->type = varSymbol->type;
        return;
    }
	auto curClassSymbol = classSymbol;
    while( curClassSymbol->parentName ) {
        auto parentClassSymbol = table->GetClassByName( curClassSymbol->parentName );
        auto parentClassFieldSymbol = parentClassSymbol->fields.GetObject( name );
        if( parentClassFieldSymbol ) {
            expression->type = parentClassFieldSymbol->type;
            return;
        }
		curClassSymbol = parentClassSymbol;
    }

    if( !curMethodName ) {
        std::cerr << "[" << expression->coordinates.first_line << ", " 
            << expression->coordinates.first_column << "] "
            << "Error: Unknown identifier \"" << name->GetString() << "\"\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE );
    } else {
        auto methodSymbol = classSymbol->methods.GetObject( curMethodName );
        auto argSymbol = methodSymbol->arguments.GetObject( name );
        if( !argSymbol ) {
            auto varSymbol = methodSymbol->variables.GetObject( name );
            if( !varSymbol ) {
                std::cerr << "[" << expression->coordinates.first_line << ", " 
                    << expression->coordinates.first_column << "] "
                    << "Error: Unknown identifier \"" << name->GetString() << "\"\n";
                expression->type = new CBuiltInType( enums::UNKNOWNTYPE );
            } else {
                expression->type = varSymbol->type;
            }
        } else {
            expression->type = argSymbol->type;
        }
    }
    if( CSymbol::GetSymbol( expression->type->ToString() ) == name ) {
        std::cerr << "[" << expression->coordinates.first_line << ", " 
            << expression->coordinates.first_column << "] "
            << "Error: The name of variable \"" << name->GetString() << "\" and its type are the same.\n";
    }
}

void CTypeCheckerVisitor::Visit( CBinaryExpression *expression ) {
    expression->leftOperand->Accept(this);
    CSymbol* leftExpType = CSymbol::GetSymbol(
		expression->leftOperand->type->ToString() );
    expression->rightOperand->Accept(this);
    CSymbol* rightExpType = CSymbol::GetSymbol(
		expression->rightOperand->type->ToString() );
    if( leftExpType != CSymbol::GetSymbol( "int" ) || 
		rightExpType != CSymbol::GetSymbol( "int" ) ) {
        std::cerr << "[" << expression->coordinates.first_line << ", " 
            << expression->coordinates.first_column << "] "
            << "Error: Incorrect types of binary operation.\n"
            << "Expected: \"int\" and \"int\". "
            <<"Found \"" << leftExpType->GetString() 
			<< "\" and \"" << rightExpType->GetString() <<"\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CNumberExpression *expression ) {
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CBinaryBooleanExpression *expression ) {
    expression->leftOperand->Accept(this);
    CSymbol* leftExpType = CSymbol::GetSymbol(
		expression->leftOperand->type->ToString() );
    expression->rightOperand->Accept(this);
    CSymbol* rightExpType = CSymbol::GetSymbol(
		expression->rightOperand->type->ToString() );
    if( expression->operation == enums::GREATER || expression->operation == enums::LESS ) {
        if( leftExpType != CSymbol::GetSymbol( "int" ) || 
			rightExpType != CSymbol::GetSymbol( "int" ) ) {
			std::cerr << "[" << expression->coordinates.first_line << ", " 
				<< expression->coordinates.first_column << "] "
				<< "Error: Incorrect types of binary operation.\n"
				<< "Expected: \"int\" and \"int\". "
				<<"Found \"" << leftExpType->GetString() 
				<< "\" and \"" << rightExpType->GetString() <<"\".\n";
        }
    } else {
        if( leftExpType != CSymbol::GetSymbol( "boolean" ) || 
			rightExpType != CSymbol::GetSymbol( "boolean" ) ) {
            std::cerr << "[" << expression->coordinates.first_line << ", " 
                << expression->coordinates.first_column << "] "
                << "Error: Incorrect types of binary operation.\n"
                << "Expected: \"int\" and \"int\". "
                <<"Found \"" << leftExpType->GetString() 
				<< "\" and \"" << rightExpType->GetString() <<"\".\n";
        }
    }
    expression->type = new CBuiltInType( enums::BOOLEAN );
}

void CTypeCheckerVisitor::Visit( CBooleanExpression *expression ) {
    expression->type = new CBuiltInType( enums::BOOLEAN );
}

void CTypeCheckerVisitor::Visit( CThisExpression *expression ) {
    expression->type = new CUserType( curClassName->GetString() );
}

void CTypeCheckerVisitor::Visit( CNewObjectExpression *expression ) {
    CSymbol* className = CSymbol::GetSymbol( expression->objTypeId->name );
    if( !table->GetClassByName( className ) ) {
        std::cerr << "[" << expression->objTypeId->coordinates.first_line << ", " 
            << expression->objTypeId->coordinates.first_column << "] "
            << "Error: Unknown class \"" << className->GetString() << "\"\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE );
    }
    expression->type = new CUserType( className->GetString() );
}

void CTypeCheckerVisitor::Visit( CNewIntArrayExpression *expression ) {
    expression->arrSize->Accept(this);
    CSymbol* sizeType = CSymbol::GetSymbol( expression->arrSize->type->ToString() );
    if( sizeType != CSymbol::GetSymbol( "int" ) ) {
        std::cerr << "[" << expression->arrSize->coordinates.first_line << ", " 
            << expression->arrSize->coordinates.first_column << "] "
            << "Error: Incorrect type of array size.\n"
            << "Expected: \"int\". "
            <<"Found \"" << sizeType->GetString() << "\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGERARRAY );    
}

void CTypeCheckerVisitor::Visit( CMethodCallExpression *expression ) {
    expression->base->Accept(this);
    CSymbol* baseName = CSymbol::GetSymbol( expression->base->type->ToString() );
    auto classSymbol = table->GetClassByName( baseName );
    if( !classSymbol ) {
        std::cerr << "[" << expression->base->coordinates.first_line << ", " 
            << expression->base->coordinates.first_column << "] "
            << "Error: Unknown class \"" << baseName->GetString()
            << "\" method call.\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE ); 
        return;
    }
    CSymbol* methodName = CSymbol::GetSymbol( expression->methodId->name );
    auto methodSymbol = classSymbol->methods.GetObject( methodName );
    if( !methodSymbol ) {
        std::cerr << "[" << expression->methodId->coordinates.first_line << ", " 
            << expression->methodId->coordinates.first_column << "] "
            << "Error: Method \"" << methodName->GetString() << "\" in class \""
            << baseName->GetString() << "\" doesn't exist.\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE ); 
        return;
    }
    auto methodArgumentsTypes = methodSymbol->argumentTypes;
    curCallArgumentsTypes.clear();
    if( expression->arg ) {
        expression->arg->Accept(this);        
    }
    if( methodArgumentsTypes.size() != curCallArgumentsTypes.size() ) {
        std::cerr << "[" << expression->methodId->coordinates.first_line << ", " 
            << expression->methodId->coordinates.first_column << "] "
            << "Error: Method \"" << methodName->GetString() << "\" of class \"" 
            << baseName->GetString() << "\" expected to take " 
			<< methodArgumentsTypes.size() << " arguments but takes " 
			<< curCallArgumentsTypes.size() << " arguments\n";
        expression->type = methodSymbol->type; 
        return;
    }
    for( std::size_t i = 0; i < methodArgumentsTypes.size(); ++i ) {
        bool found = false;
        CSymbol* methodTypeName = CSymbol::GetSymbol(
			methodArgumentsTypes[i]->ToString() );
        CSymbol* curTypeName = CSymbol::GetSymbol(
			curCallArgumentsTypes[i]->ToString() );
        CSymbol* startTypeName = curTypeName;
        if( methodTypeName == curTypeName ) {
            found = true;
        } else {
            if( !( curTypeName == CSymbol::GetSymbol( "int" ) || 
				curTypeName == CSymbol::GetSymbol( "bool" ) || 
				curTypeName == CSymbol::GetSymbol( "int[]" ) ) ) {
                while( curTypeName || curTypeName != startTypeName ) {
                    curTypeName = table->GetClassByName( curTypeName )->parentName;
                    if( methodTypeName == curTypeName ) {
                        found = true;
                        break;
                    } 
                }
            }
        }
        if( !found ) {
            std::cerr << "[" << curCallArgumentsTypes[i]->coordinates.first_line << ", " 
                << curCallArgumentsTypes[i]->coordinates.first_column << "] "
                << "Error: " << i + 1 << "th argument's type of method \"" 
                << methodName->GetString() << "\" call of class \"" 
                << baseName->GetString() << "\" doesn't match to method argument type.\n"
                << "Expected: \"" << methodArgumentsTypes[i]->ToString() 
                << "\". Found \"" << curCallArgumentsTypes[i]->ToString() << "\".\n";
        }
    }
    expression->type = methodSymbol->type;
}

void CTypeCheckerVisitor::Visit( CArrayLengthExpression *expression ) {
    expression->exp->Accept(this);
    CSymbol* expType = CSymbol::GetSymbol( expression->exp->type->ToString() );
    if( expType != CSymbol::GetSymbol( "int[]" ) ) {
        std::cerr << "[" << expression->exp->coordinates.first_line << ", " 
            << expression->exp->coordinates.first_column << "] "
            << "Error: Incorrect type of array.\n"
            << "Expected: \"int[]\". "
            << "Found \"" << expType->GetString() << "\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CArrayIndexExpression *expression ) {
    expression->id->Accept(this);
	CSymbol* idType = CSymbol::GetSymbol( expression->id->type->ToString() );
    if( idType != CSymbol::GetSymbol( "int[]" ) ) {
       std::cerr << "[" << expression->id->coordinates.first_line << ", " 
            << expression->id->coordinates.first_column << "] "
            << "Error: Incorrect type of array.\n"
            << "Expected: \"int[]\". "
            << "Found \"" << idType->GetString() << "\".\n";
    }
    expression->index->Accept(this);
    CSymbol* indexType = CSymbol::GetSymbol( expression->index->type->ToString() );
    if( indexType != CSymbol::GetSymbol( "int" ) ) {
        std::cerr << "[" << expression->index->coordinates.first_line << ", " 
            << expression->index->coordinates.first_column << "] "
            << "Error: Incorrect type of array index.\n"
            << "Expected: \"int\". "
            << "Found \"" << indexType->GetString() << "\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CCompoundExpression *expression ) {
    if(expression->leftExpression) {
        expression->leftExpression->Accept(this);
    }

    if(expression->rightExpression) {
        expression->rightExpression->Accept(this);
        expression->rightExpression->type->coordinates = 
			expression->rightExpression->coordinates;
        curCallArgumentsTypes.push_back( expression->rightExpression->type );
    }
}