#include <stdlib.h>
#include "../IVisitor.h"
#include "CIdExpression.h"

CIdExpression::CIdExpression( const char *_name, std::size_t *_address ) : \
	name( _name ), address( _address ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}