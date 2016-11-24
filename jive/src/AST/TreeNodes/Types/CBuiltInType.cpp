#include "CBuiltInType.h"

CBuiltInType::CBuiltInType( enums::TType _type ) : \
	IType( _type ) {}

void CBuiltInType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}