#include "CTableCreatorVisitor.h"
#include "CJiveEnvironment.h"

namespace AST
{

using jive::CJiveEnvironment;

void CTableCreatorVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept(this);
}

void CTableCreatorVisitor::Visit( CProgram *program ) {
    program->rootVertex->Accept(this);
}

void CTableCreatorVisitor::Visit( CGoal *goal ) {
    goal->left->Accept(this);
    goal->right->Accept(this);
}

void CTableCreatorVisitor::Visit( CType *type ) {
}

void CTableCreatorVisitor::Visit( CVariable *entity ) {
    CTypeSymbol *varTypeSymbol = jiveEnv->typeTable->lookup( entity->type );
    if( varTypeSymbol == nullptr ) {
        varTypeSymbol = new CTypeSymbol( entity->type->getSymbol() );
    }

    CVariableSymbol* varSymbol = new CVariableSymbol( entity->id->name, varTypeSymbol, entity );
    if( curMethodSymbol == nullptr ) {
        if( curClassSymbol->fields.find( varSymbol ) != curClassSymbol->fields.end() ) {
            std::cerr << "Error: Redefinition of the field \"" << varSymbol->name << "\"\n";
            delete varSymbol;
            return;
        }
        curClassSymbol->fields.insert( varSymbol );
    } else {
        if( curMethodSymbol->arguments.find( varSymbol ) != curMethodSymbol->arguments.end() ) {
            std::cerr << "Error: Redeclaration of argument \"" << varSymbol->name << "\"\n";
            delete varSymbol;
            return;
        }
        if( curMethodSymbol->variables.find( varSymbol ) != curMethodSymbol->variables.end() ) {
            std::cerr << "Error: Redeclaration of variable \"" << varSymbol->name << "\"\n";
            delete varSymbol;
            return;
        }
        curMethodSymbol->variables.insert( varSymbol );
    }
}

void CTableCreatorVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->var1 ) {
        entity->var1->Accept(this);
    }
    entity->var2->Accept(this);
}

void CTableCreatorVisitor::Visit( CArgument *entity ) {
    CTypeSymbol *argTypeSymbol = jiveEnv->typeTable->lookup( entity->type );
    if( argTypeSymbol == nullptr ) {
        argTypeSymbol = new CTypeSymbol( entity->type->getSymbol() );
    }

    CVariableSymbol* argSymbol = new CVariableSymbol( entity->id->name, argTypeSymbol, entity );
    if( curMethodSymbol->arguments.find( argSymbol ) != curMethodSymbol->arguments.end() ) {
            std::cerr << "Error: Redeclaration of variable \"" << argSymbol->name << "\"\n";
            delete argSymbol;
            return;
        }
    curMethodSymbol->arguments.insert( argSymbol );
}

void CTableCreatorVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->arg1 ) {
    	entity->arg1->Accept(this);
	}
    entity->arg2->Accept(this);
}

void CTableCreatorVisitor::Visit( CMethod *entity ) {    
    CTypeSymbol *methodTypeSymbol = jiveEnv->typeTable->lookup( entity->returnType );
    if( methodTypeSymbol == nullptr ) {
        methodTypeSymbol = new CTypeSymbol( entity->returnType->getSymbol() );
    }

    CMethodSymbol* methodSymbol = new CMethodSymbol( entity->id->name, methodTypeSymbol, entity );
    if( curClassSymbol->methods.find( methodSymbol ) != curClassSymbol->methods.end() ) {
        std::cerr << "Error: Redeclaration of variable \"" << methodSymbol->name << "\"\n";
            delete methodSymbol;
            return;
    }
    curClassSymbol->methods.insert( methodSymbol );

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
    CTypeSymbol *mainClassTypeSymbol = new CTypeSymbol( entity->name->name );
    jiveEnv->typeTable->insert( new CType( jive::CLASS, entity->name->name ), mainClassTypeSymbol );

    CClassSymbol* classSymbol = new CClassSymbol( entity->name->name, mainClassTypeSymbol, nullptr, entity );
    jiveEnv->classTable->insert( entity, classSymbol );

    curClassSymbol = classSymbol;

	entity->methods->method2->Accept(this);
}

void CTableCreatorVisitor::Visit( CClass *entity ) {
    CTypeSymbol *classTypeSymbol = new CTypeSymbol( entity->name->name );
    jiveEnv->typeTable->insert( new CType( jive::CLASS, entity->name->name ), classTypeSymbol );

    CClassSymbol* classSymbol = new CClassSymbol( entity->name->name, classTypeSymbol, nullptr, entity );
    if( jiveEnv->classTable->lookup( entity ) != nullptr ) {
        std::cerr << "Error: Redefinition of class \"" << classSymbol->name << "\"\n";
            delete classSymbol;
            return;
    }
    jiveEnv->classTable->insert( entity, classSymbol );
    curClassSymbol = classSymbol;
    curMethodSymbol = nullptr;

    if( entity->parentName ) {
        classSymbol->baseClass = jiveEnv->classTable->lookup( entity->parentName->name );
        if( classSymbol->baseClass == nullptr ) {
            classSymbol->baseClass = new CClassSymbol( entity->parentName->name, new CTypeSymbol( entity->parentName->name ), nullptr, nullptr );
        }
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

void CTableCreatorVisitor::Visit( CVoidExpression *expression ) {
} 

}