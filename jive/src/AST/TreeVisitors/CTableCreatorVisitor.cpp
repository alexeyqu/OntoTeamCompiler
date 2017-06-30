#include "CTableCreatorVisitor.h"
#include "CJiveEnvironment.h"

namespace AST
{

using jive::CJiveEnvironment;

void CTableCreatorVisitor::Start( IVisitorTarget *vertex ) {
    vertex->Accept( this );
}

void CTableCreatorVisitor::Visit( CProgram *program ) {
    program->getRoot()->Accept( this );
}

void CTableCreatorVisitor::Visit( CGoal *goal ) {
    goal->getLeft()->Accept( this );
    goal->getRight()->Accept( this );
}

void CTableCreatorVisitor::Visit( CType *type ) {
}

void CTableCreatorVisitor::Visit( CVariable *entity ) {
    CTypeSymbol *varTypeSymbol = jiveEnv->typeMap->lookup( entity->getType() );
    if( varTypeSymbol == nullptr ) {
        varTypeSymbol = new CTypeSymbol( entity->getType()->getSymbol() );
    }

    CVariableSymbol *varSymbol = new CVariableSymbol( entity->getSymbol(), varTypeSymbol, entity );
    if( curMethodSymbol == nullptr ) {
        if( curClassSymbol->lookupField( varSymbol ) != nullptr ) {
            outputStream << "Error: Redefinition of the field \"" << varSymbol->getString() << "\"\n";
            delete varSymbol;
            return;
        }
        curClassSymbol->insertField( varSymbol );
    } else {
        if( curMethodSymbol->lookupArgument( varSymbol->getSymbol() ) != nullptr ) {
            outputStream << "Error: Redeclaration of argument \"" << varSymbol->getString() << "\"\n";
            delete varSymbol;
            return;
        }
        if( curMethodSymbol->lookupVariable( varSymbol ) != nullptr ) {
            outputStream << "Error: Redeclaration of variable \"" << varSymbol->getString() << "\"\n";
            delete varSymbol;
            return;
        }
        curMethodSymbol->insertVariable( varSymbol );
    }
}

void CTableCreatorVisitor::Visit( CCompoundVariable *entity ) {
    if( entity->getNextVariable() ) {
        entity->getNextVariable()->Accept( this );
    }
    entity->getVariable()->Accept( this );
}

void CTableCreatorVisitor::Visit( CArgument *entity ) {
    CTypeSymbol *argTypeSymbol = jiveEnv->typeMap->lookup( entity->getType() );
    if( argTypeSymbol == nullptr ) {
        argTypeSymbol = new CTypeSymbol( entity->getType()->getSymbol() );
    }

    CVariableSymbol *argSymbol = new CVariableSymbol( entity->getSymbol(), argTypeSymbol, entity );
    if( curMethodSymbol->lookupArgument( argSymbol->getSymbol() ) != nullptr ) {
		outputStream << "Error: Redeclaration of argument \"" << argSymbol->getString() << "\"\n";
		delete argSymbol;
		return;
	}
    curMethodSymbol->insertArgument( argSymbol );
}

void CTableCreatorVisitor::Visit( CCompoundArgument *entity ) {
    if( entity->getNextArgument() ) {
    	entity->getNextArgument()->Accept( this );
	}
    entity->getArgument()->Accept( this );
}

void CTableCreatorVisitor::Visit( CMethod *entity ) {    
    CTypeSymbol *methodTypeSymbol = jiveEnv->typeMap->lookup( entity->getReturnType() );
    if( methodTypeSymbol == nullptr ) {
        methodTypeSymbol = new CTypeSymbol( entity->getReturnType()->getSymbol() );
    }

    CMethodSymbol *methodSymbol = new CMethodSymbol( entity->getSymbol(), methodTypeSymbol, entity );
    if( curClassSymbol->lookupMethod( methodSymbol ) != nullptr ) {
        outputStream << "Error: Redeclaration of variable \"" << methodSymbol->getString() << "\"\n";
            delete methodSymbol;
            return;
    }
    curClassSymbol->insertMethod( methodSymbol );

    curMethodSymbol = methodSymbol;
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
}

void CTableCreatorVisitor::Visit( CCompoundMethod *entity ) {
    if( entity->getNextMethod() ) {
		entity->getNextMethod()->Accept( this );
    }
    entity->getMethod()->Accept( this );
}

void CTableCreatorVisitor::Visit( CMainClass *entity ) {
    CTypeSymbol *mainClassTypeSymbol = new CTypeSymbol( entity->getSymbol() );
    jiveEnv->typeMap->insert( new CType( jive::CLASS, entity->getSymbol() ), mainClassTypeSymbol );

    CClassSymbol *classSymbol = new CClassSymbol( entity->getSymbol(), mainClassTypeSymbol, nullptr, entity );
    jiveEnv->classMap->insert( entity, classSymbol );

    curClassSymbol = classSymbol;

	entity->getMethods()->getMethod()->Accept( this );
}

void CTableCreatorVisitor::Visit( CClass *entity ) {
    CTypeSymbol *classTypeSymbol = new CTypeSymbol( entity->getSymbol() );
    jiveEnv->typeMap->insert( new CType( jive::CLASS, entity->getSymbol() ), classTypeSymbol );

    CClassSymbol *classSymbol = new CClassSymbol( entity->getSymbol(), classTypeSymbol, nullptr, entity );
    if( jiveEnv->classMap->lookup( entity ) != nullptr ) {
        outputStream << "Error: Redefinition of class \"" << classSymbol->getString() << "\"\n";
            delete classSymbol;
            return;
    }
    jiveEnv->classMap->insert( entity, classSymbol );
    curClassSymbol = classSymbol;
    curMethodSymbol = nullptr;

    if( entity->getParentId() ) {
        classSymbol->setBaseClass( jiveEnv->classMap->lookup( entity->getParentSymbol() ) );
        if( classSymbol->getBaseClass() == nullptr ) {
            classSymbol->setBaseClass( new CClassSymbol( entity->getParentSymbol(), new CTypeSymbol( entity->getParentSymbol() ), nullptr, nullptr ) );
        }
    }

    if( entity->getFields() ) {
		entity->getFields()->Accept( this );
    }

    if( entity->getMethods() ) {
		entity->getMethods()->Accept( this );
    }
}

void CTableCreatorVisitor::Visit( CCompoundClass *entity ) {

    if( entity->getNextClass() ) {
        entity->getNextClass()->Accept( this );
    }
    entity->getClass()->Accept( this );
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