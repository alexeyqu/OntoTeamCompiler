#include "CArray.h"

CArray::CArray( CType *_type, int _size ) : \
	type( _type ), size( _size ) {}

void CArray::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}