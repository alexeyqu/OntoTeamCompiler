#include "CUserType.h"

namespace AST 
{

CUserType::CUserType( CSymbol *_name ) : \
	IType( jive::TType::CLASS ), name( _name ) {}

void CUserType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

CSymbol CUserType::getSymbol() {
	return *name;
}

}