#include "CUserType.h"

CUserType::CUserType( std::string _name ) : \
	IType( enums::TType::CLASS ), name( _name ) {}

void CUserType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

std::string CUserType::ToString() {
	return name;
} 
