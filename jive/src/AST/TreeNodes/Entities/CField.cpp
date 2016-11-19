#include "CField.h"

CField::CField( CType *_type, CIdExpression *_id ) : \
	type( _type ), id( _id ) {}

void CField::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}