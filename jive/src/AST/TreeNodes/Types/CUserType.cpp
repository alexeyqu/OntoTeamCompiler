#include "CUserType.h"

CUserType::CUserType( CSymbol *_name ) : \
	IType( enums::TType::CLASS ), name( _name ) {}

void CUserType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

// TODO bring flyweight<std::string> here