#include "CLocalVariable.h"

CLocalVariable::CLocalVariable( CType *_type, CIdExpression *_id ) : \
	type( _type ), id( _id ) {}

void CLocalVariable::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

enums::TType CLocalVariable::getType() {
	return type->type;
}