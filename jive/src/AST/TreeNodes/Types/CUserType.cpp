#include "CUserType.h"

CUserType::CUserType( CClass *_typeClass ) : \
	IType( enums::TType::USERTYPE ), typeClass( _typeClass ) {}

void CUserType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
} 
