#include "CTypeCheckerVisitor.h"

CTypeCheckerVisitor::CTypeCheckerVisitor( std::map<std::string, CClassSymbol*>& _table ) {
    table = _table;
}

void CTypeCheckerVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept(this);
}

void CTypeCheckerVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CTypeCheckerVisitor::Visit( CGoal *goal )
{
    goal->tmp1->Accept(this);
    goal->tmp2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CBuiltInType *type ) {
}

void CTypeCheckerVisitor::Visit( CUserType *type ) {
}

void CTypeCheckerVisitor::Visit( CVariable *entity ) {
    std::string varName = entity->id->name;
    std::string varType = entity->type->ToString();
    if( varType != "int" && varType != "boolean" && varType != "int[]" &&
        table.find( varType ) == table.end() ) {
        std::cerr << "[" << entity->coordinates.first_line << ", " 
            << entity->coordinates.first_column << "] " 
            << "Error: Unknown type of variable \"" << varName << "\": " << varType << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->var1 ) {
        entity->var1->Accept(this);
    }
    entity->var2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CArgument *entity ) {
    std::string argName = entity->id->name;
    std::string argType = entity->type->ToString();
    if( argType != "int" && argType != "boolean" && argType != "int[]" &&
        table.find( argType ) == table.end() ) {
        std::cerr << "[" << entity->coordinates.first_line << ", " 
            << entity->coordinates.first_column << "] " 
            << "Error: Unknown type of argument \"" << argName << "\": " << argType << ".\n";
    }
}

void CTypeCheckerVisitor::Visit( CCompoundArgument *entity ) {   
    if( entity->arg1 ) {
        entity->arg1->Accept(this);
    }
    entity->arg2->Accept(this); 
}

void CTypeCheckerVisitor::Visit( CMethod *entity ) {
    curMethodName = entity->id->name;
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
    std::string retExpType = entity->returnExpression->type->ToString();
    std::string retType = entity->returnType->ToString();
    if( retType != "int" && retType != "boolean" && retType != "int[]" &&
            table.find( retType ) == table.end() ) {
        std::cerr << "[" << entity->returnType->coordinates.first_line << ", " 
            << entity->returnType->coordinates.first_column << "] " 
            << "Error: Return type of method \"" << curMethodName 
            << "\" is of unknown type \"" << retType  << "\".\n";
        curMethodName = "";
        return;
    }
    if( retExpType != retType ) {
        std::cerr << "[" << entity->returnExpression->coordinates.first_line << ", " 
            << entity->returnExpression->coordinates.first_column << "] " 
            << "Error: Type of return expression doesn't match "
            << "method \"" << curMethodName << "\" return type.\n"
            << "Expected: \"" << retType  << "\". Found: \"" << retExpType  << "\".\n";
    }
    curMethodName = "";
}

void CTypeCheckerVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->method1 ) {
        entity->method1->Accept(this);
    }
    entity->method2->Accept(this);
}

void CTypeCheckerVisitor::Visit( CMainClass *entity ) {
    curClassName = entity->name->name;
    curMethodName = "main";
    entity->statement->Accept(this);
    curMethodName = "";
}

void CTypeCheckerVisitor::Visit( CClass *entity ) {
    curClassName = entity->name->name;
    if( entity->parentName ) {
        std::string parentName = entity->parentName->name;
        auto parentIt = table.find( parentName );
        if( parentIt == table.end() ) {
            std::cerr << "[" << entity->parentName->coordinates.first_line << ", " 
                << entity->parentName->coordinates.first_column << "] " 
                << "Error: unknown base class \"" 
                << curClassName << "\" for class \"" 
                << curClassName << "\"\n";
        }
        while( !parentName.empty() ) {
            if( curClassName == parentName ) {
                std::cerr << "[" << entity->name->coordinates.first_line << ", " 
                    << entity->name->coordinates.first_column << "] " 
                    << "Error: cyclic inheritance for class \"" 
                    << curClassName << "\" detected.\n";
                break;
            }
            auto parentIt = table.find( parentName );
            if( parentIt == table.end() ) {
                break;
            } else {
                parentName = parentIt->second->parentName;
            }
        }
    }
    if( entity->methods ) {
        entity->methods->Accept(this);
    }
    curMethodName = "";
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
    std::string leftExpType = statement->leftOperand->type->ToString();
    statement->rightOperand->Accept(this);
    std::string rightExpType = statement->rightOperand->type->ToString();
    if( leftExpType != rightExpType ) {
        std::cerr << "[" << statement->coordinates.first_line << ", " 
            << statement->coordinates.first_column << "] "  
            << "Error: Incorrect types of assign statement expressions.\n"
            << "Expected: \"" << leftExpType << "\" and \"" << leftExpType <<"\". "
            << "Found \"" << leftExpType << "\" and \"" << rightExpType <<"\".\n";
    }
}

void CTypeCheckerVisitor::Visit( CPrintStatement *statement ) {
    statement->operand->Accept(this);
    std::string expType = statement->operand->type->ToString();
    if ( expType != "int" ) {
        std::cerr << "[" << statement->operand->coordinates.first_line << ", " 
            << statement->operand->coordinates.first_column << "] "  
            << "Error: Incorrect type of expression in Print statement.\n"
            << "Expected: \"int\". Found \"" << expType << "\"\n";
    }
}

void CTypeCheckerVisitor::Visit( CIfStatement *statement ) {
    statement->expression->Accept(this);
    std::string expType = statement->expression->type->ToString();
    if ( expType != "boolean" ) {
        std::cerr << "[" << statement->expression->coordinates.first_line << ", " 
            << statement->expression->coordinates.first_column << "] "
            << "Error: Incorrect type of expression in If statement.\n"
            << "Expected: \"boolean\". Found \"" << expType << "\"\n";
    }
    statement->thenStatement->Accept(this);
    statement->elseStatement->Accept(this);
}

void CTypeCheckerVisitor::Visit( CWhileStatement *statement ) {
    statement->expression->Accept(this);
    std::string expType = statement->expression->type->ToString();
    if ( expType != "boolean" ) {
        std::cerr << "[" << statement->expression->coordinates.first_line << ", " 
            << statement->expression->coordinates.first_column << "] "
            << "Error: Incorrect type of expression in While statement.\n"
            << "Expected: \"boolean\". Found \"" << expType << "\"\n";
    }
    statement->loopStatement->Accept(this);
}

void CTypeCheckerVisitor::Visit( CIdExpression *expression ) {
    std::string name = expression->name;
    auto classIt = table.find( curClassName );
    auto fieldIt = classIt->second->fields.find( name );
    if( fieldIt != classIt->second->fields.end() ) {
        expression->type = fieldIt->second->type;
        return;
    }

    if( classIt->second->parentName != "" ) {
        auto parentClassIt = table.find( classIt->second->parentName );
        auto parentClassFieldIt = parentClassIt->second->fields.find( name );
        if( parentClassFieldIt != parentClassIt->second->fields.end() ) {
            expression->type = parentClassFieldIt->second->type;
            return;
        }
    }

    if( curMethodName == "" ) {
        std::cerr << "[" << expression->coordinates.first_line << ", " 
            << expression->coordinates.first_column << "] "
            << "Error: Unknown identifier \"" << name << "\"\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE );
    } else {
        auto methodIt = classIt->second->methods.find( curMethodName );
        auto argIt = methodIt->second->arguments.find( name );
        if( argIt == methodIt->second->arguments.end() ) {
            auto varIt = methodIt->second->variables.find( name );
            if( varIt == methodIt->second->variables.end() ) {
                std::cerr << "[" << expression->coordinates.first_line << ", " 
                    << expression->coordinates.first_column << "] "
                    << "Error: Unknown identifier \"" << name << "\"\n";
                expression->type = new CBuiltInType( enums::UNKNOWNTYPE );
            } else {
                expression->type = varIt->second->type;
            }
        } else {
            expression->type = argIt->second->type;
        }
    }
    if( expression->type->ToString() == name ) {
        std::cerr << "[" << expression->coordinates.first_line << ", " 
            << expression->coordinates.first_column << "] "
            << "Error: The name of variable \"" << name << "\" and its type are the same.\n";
    }
}

void CTypeCheckerVisitor::Visit( CBinaryExpression *expression ) {
    expression->leftOperand->Accept(this);
    std::string leftExpType = expression->leftOperand->type->ToString();
    expression->rightOperand->Accept(this);
    std::string rightExpType = expression->rightOperand->type->ToString();
    if( leftExpType != "int" || rightExpType != "int" ) {
        std::cerr << "[" << expression->coordinates.first_line << ", " 
            << expression->coordinates.first_column << "] "
            << "Error: Incorrect types of binary operation.\n"
            << "Expected: \"int\" and \"int\". "
            <<"Found \"" << leftExpType << "\" and \"" << rightExpType <<"\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CNumberExpression *expression ) {
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CBinaryBooleanExpression *expression ) {
    expression->leftOperand->Accept(this);
    std::string leftExpType = expression->leftOperand->type->ToString();
    expression->rightOperand->Accept(this);
    std::string rightExpType = expression->rightOperand->type->ToString();
    if( expression->operation == enums::GREATER || expression->operation == enums::LESS ) {
        if( leftExpType != "int" || rightExpType != "int" ) {
        std::cerr << "[" << expression->coordinates.first_line << ", " 
            << expression->coordinates.first_column << "] "
            << "Error: Incorrect types of binary operation.\n"
            << "Expected: \"int\" and \"int\". "
            <<"Found \"" << leftExpType << "\" and \"" << rightExpType <<"\".\n";
        }
    } else {
        if( leftExpType != "boolean" || rightExpType != "boolean" ) {
            std::cerr << "[" << expression->coordinates.first_line << ", " 
                << expression->coordinates.first_column << "] "
                << "Error: Incorrect types of binary operation.\n"
                << "Expected: \"int\" and \"int\". "
                <<"Found \"" << leftExpType << "\" and \"" << rightExpType <<"\".\n";
        }
    }
    expression->type = new CBuiltInType( enums::BOOLEAN );
}

void CTypeCheckerVisitor::Visit( CBooleanExpression *expression ) {
    expression->type = new CBuiltInType( enums::BOOLEAN );
}

void CTypeCheckerVisitor::Visit( CThisExpression *expression ) {
    expression->type = new CUserType( curClassName );
}

void CTypeCheckerVisitor::Visit( CNewObjectExpression *expression ) {
    std::string className = expression->objTypeId->name;
    if( table.find( className ) == table.end() ) {
        std::cerr << "[" << expression->objTypeId->coordinates.first_line << ", " 
            << expression->objTypeId->coordinates.first_column << "] "
            << "Error: Unknown class \"" << className << "\"\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE );
    }
    expression->type = new CUserType( className );
}

void CTypeCheckerVisitor::Visit( CNewIntArrayExpression *expression ) {
    expression->arrSize->Accept(this);
    std::string sizeType = expression->arrSize->type->ToString();
    if( sizeType != "int" ) {
        std::cerr << "[" << expression->arrSize->coordinates.first_line << ", " 
            << expression->arrSize->coordinates.first_column << "] "
            << "Error: Incorrect type of array size.\n"
            << "Expected: \"int\". "
            <<"Found \"" << sizeType << "\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGERARRAY );    
}

void CTypeCheckerVisitor::Visit( CMethodCallExpression *expression ) {
    expression->base->Accept(this);
    std::string baseName = expression->base->type->ToString();
    auto classIt = table.find( baseName );
    if( classIt == table.end() ) {
        std::cerr << "[" << expression->base->coordinates.first_line << ", " 
            << expression->base->coordinates.first_column << "] "
            << "Error: Unknown class \"" << baseName 
            << "\" method call.\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE ); 
        return;
    }
    std::string methodName = expression->methodId->name;
    auto methodIt = classIt->second->methods.find( methodName );
    if( methodIt == classIt->second->methods.end() ) {
        std::cerr << "[" << expression->methodId->coordinates.first_line << ", " 
            << expression->methodId->coordinates.first_column << "] "
            << "Error: Method \"" << methodName << "\" in class \""
            << baseName << "\" doesn't exist.\n";
        expression->type = new CBuiltInType( enums::UNKNOWNTYPE ); 
        return;
    }
    auto mehodArgumentsTypes = methodIt->second->argumentTypes;
    curCallArgumentsTypes.clear();
    if( expression->arg ) {
        expression->arg->Accept(this);        
    }
    if( mehodArgumentsTypes.size() != curCallArgumentsTypes.size() ) {
        std::cerr << "[" << expression->methodId->coordinates.first_line << ", " 
            << expression->methodId->coordinates.first_column << "] "
            << "Error: Method \"" << methodName << "\" of class \"" 
            << baseName << "\" expected to take " << mehodArgumentsTypes.size()
            << " arguments but takes " << curCallArgumentsTypes.size() << " arguments\n";
        expression->type = methodIt->second->type; 
        return;
    }
    for( std::size_t i = 0; i < mehodArgumentsTypes.size(); ++i ) {
        bool found = false;
        std::string mehodTypeName = mehodArgumentsTypes[i]->ToString();
        std::string curTypeName = curCallArgumentsTypes[i]->ToString();
        std::string startTypeName = curTypeName;
        if( mehodTypeName == curTypeName ) {
            found = true;
        } else {
            if( !( curTypeName == "int" || curTypeName == "bool" || curTypeName == "int[]" ) ) {
                while( curTypeName != "" || curTypeName != startTypeName ) {
                    curTypeName = table[curTypeName]->parentName;
                    if( mehodTypeName == curTypeName ) {
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
                << methodName << "\" call of class \"" 
                << baseName << "\" doesn't match to method argument type.\n"
                << "Expected: \"" << mehodArgumentsTypes[i]->ToString() 
                << "\". Found \"" << curCallArgumentsTypes[i]->ToString() << "\".\n";
        }
    }
    expression->type = methodIt->second->type;
}

void CTypeCheckerVisitor::Visit( CArrayLengthExpression *expression ) {
    expression->exp->Accept(this);
    std::string expType = expression->exp->type->ToString();
    if( expType != "int[]" ) {
        std::cerr << "[" << expression->exp->coordinates.first_line << ", " 
            << expression->exp->coordinates.first_column << "] "
            << "Error: Incorrect type of array.\n"
            << "Expected: \"int[]\". "
            << "Found \"" << expType << "\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CArrayIndexExpression *expression ) {
    expression->id->Accept(this);
    std::string idType = expression->id->type->ToString();
    if( idType != "int[]" ) {
       std::cerr << "[" << expression->id->coordinates.first_line << ", " 
            << expression->id->coordinates.first_column << "] "
            << "Error: Incorrect type of array.\n"
            << "Expected: \"int[]\". "
            << "Found \"" << idType << "\".\n";
    }
    expression->index->Accept(this);
    std::string indexType = expression->index->type->ToString();
    if( indexType != "int" ) {
        std::cerr << "[" << expression->index->coordinates.first_line << ", " 
            << expression->index->coordinates.first_column << "] "
            << "Error: Incorrect type of array index.\n"
            << "Expected: \"int\". "
            << "Found \"" << indexType << "\".\n";
    }
    expression->type = new CBuiltInType( enums::INTEGER );
}

void CTypeCheckerVisitor::Visit( CCompoundExpression *expression ) {
    if(expression->leftExpression) {
        expression->leftExpression->Accept(this);
    }

    if(expression->rightExpression) {
        expression->rightExpression->Accept(this);
        expression->rightExpression->type->coordinates = expression->rightExpression->coordinates;
        curCallArgumentsTypes.push_back( expression->rightExpression->type );
    }
}