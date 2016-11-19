#include "CType.h"

CType::CType( enums::TType _type ) : \
	type( _type ) {}

void CType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}