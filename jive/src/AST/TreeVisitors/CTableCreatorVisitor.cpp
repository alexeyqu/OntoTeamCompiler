#include "AST/TreeVisitors/CTableCreatorVisitor.h"

void CTableCreatorVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept(this);
}

void CTableCreatorVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CTableCreatorVisitor::Visit( CGoal *goal ) {
    goal->tmp1->Accept(this);
	if (goal->tmp2) {
		goal->tmp2->Accept( this );
	}
}

void CTableCreatorVisitor::Visit( CBuiltInType *type ) {
}

void CTableCreatorVisitor::Visit( CUserType *type ) {
}

void CTableCreatorVisitor::Visit( CVariable *entity ) {
    CVariableSymbol* varSymbol = new CVariableSymbol(entity->id->name, entity->type );
    if( curMethodSymbol == nullptr ) {
        if( curClassSymbol->fields.GetObject( varSymbol->name ) ) {
            std::cerr << "[" << entity->id->coordinates.first_line << ", " 
                << entity->id->coordinates.first_column << "] "  
                << "Error: Redefinition of the field \"" << varSymbol->GetName() << "\"\n";
            delete varSymbol;
            return;
        }
        curClassSymbol->fields.InsertObject( varSymbol->name, varSymbol );
    } else {
        if( curMethodSymbol->arguments.GetObject( varSymbol->name ) ) {
            std::cerr << "[" << entity->id->coordinates.first_line << ", " 
                << entity->id->coordinates.first_column << "] " 
                << "Error: Redeclaration of argument \"" << varSymbol->GetName() << "\"\n";
            return;
        }
        if( curMethodSymbol->variables.GetObject( varSymbol->name ) ) {
            std::cerr << "[" << entity->id->coordinates.first_line << ", " 
                << entity->id->coordinates.first_column << "] "  
                << "Error: Redeclaration of variable \"" << varSymbol->GetName() << "\"\n";
            delete varSymbol;
            return;
        }
        curMethodSymbol->variables.InsertObject(varSymbol->name, varSymbol );
    }
}

void CTableCreatorVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->var1 ) {
        entity->var1->Accept(this);
    }
    entity->var2->Accept(this);
}

void CTableCreatorVisitor::Visit( CArgument *entity ) {
    CVariableSymbol* varSymbol = new CVariableSymbol(entity->id->name, entity->type );
    curMethodSymbol->argumentTypes.push_back( varSymbol->type );
    if( curMethodSymbol->arguments.GetObject( varSymbol->name ) ) {
        std::cerr << "[" << entity->id->coordinates.first_line << ", " 
            << entity->id->coordinates.first_column << "] " 
            << "Error: Redeclaration of argument \"" << varSymbol->GetName() << "\"\n";
        delete varSymbol;
        return;
    }
    curMethodSymbol->arguments.InsertObject( varSymbol->name, varSymbol );
}

void CTableCreatorVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->arg1 ) {
    	entity->arg1->Accept(this);
	}
    entity->arg2->Accept(this);
}

void CTableCreatorVisitor::Visit( CMethod *entity ) {
    CMethodSymbol* methodSymbol = new CMethodSymbol( entity->id->name, entity->returnType );
    if( curClassSymbol->methods.GetObject( methodSymbol->name ) ) {
        std::cerr << "[" << entity->id->coordinates.first_line << ", " 
            << entity->id->coordinates.first_column << "] "
            << "Error: Redeclaration of method \"" 
			<< methodSymbol->GetName() << "\"\n";
        delete methodSymbol;
        return;
    }
    curClassSymbol->methods.InsertObject( methodSymbol->name, methodSymbol );
    curMethodSymbol = methodSymbol;
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
}

void CTableCreatorVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->method1 ) {
            entity->method1->Accept(this);
    }
    entity->method2->Accept(this);
}

void CTableCreatorVisitor::Visit( CMainClass *entity ) {
    CClassSymbol* classSymbol = new CClassSymbol( entity->name->name,
        new CBuiltInType( enums::CLASS ) );
    table->AddClass( classSymbol );
    curClassSymbol = classSymbol;
    CMethodSymbol* methodSymbol = new CMethodSymbol( "main", new CBuiltInType( enums::VOID ) );
    classSymbol->methods.InsertObject( methodSymbol->name , methodSymbol );
    curMethodSymbol = methodSymbol;
    CVariableSymbol* varSymbol = new CVariableSymbol( entity->cmdArgs->name, new CBuiltInType( enums::STRINGARRAY ) );
    methodSymbol->arguments.InsertObject( varSymbol->name, varSymbol );
}

void CTableCreatorVisitor::Visit( CClass *entity ) {
    if( table->GetClassByName( entity->name->name ) ) {
        std::cerr << "[" << entity->name->coordinates.first_line << ", " 
            << entity->name->coordinates.first_column << "] " 
            << "Error: Redefinition of class \"" << entity->name->name << "\"\n";
        return;
    }
	CClassSymbol* classSymbol = new CClassSymbol( entity->name->name,
        new CBuiltInType( enums::CLASS ) );
    table->AddClass( classSymbol );
    curClassSymbol = classSymbol;
    curMethodSymbol = nullptr;

    if( entity->parentName ) {
		classSymbol->parentName = CSymbol::GetSymbol( entity->parentName->name );
    }

    if( entity->fields ) {
            entity->fields->Accept(this);
    }

    if( entity->methods ) {
            entity->methods->Accept(this);
    }
}

void CTableCreatorVisitor::Visit( CCompoundClass *entity ) {

    if( entity->class1 ) {
        entity->class1->Accept(this);
    }
    entity->class2->Accept(this);
}


void CTableCreatorVisitor::Visit( CCompoundStatement *statement ) {
}

void CTableCreatorVisitor::Visit( CAssignStatement *statement ) {
}

void CTableCreatorVisitor::Visit( CPrintStatement *statement ) {
}

void CTableCreatorVisitor::Visit( CIfStatement *statement ) {
}

void CTableCreatorVisitor::Visit( CWhileStatement *statement ) {
}

void CTableCreatorVisitor::Visit( CIdExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CBinaryExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CNumberExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CBinaryBooleanExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CBooleanExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CThisExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CNewObjectExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CNewIntArrayExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CMethodCallExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CArrayLengthExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CArrayIndexExpression *expression ) {
}

void CTableCreatorVisitor::Visit( CCompoundExpression *expression ) {
} 
