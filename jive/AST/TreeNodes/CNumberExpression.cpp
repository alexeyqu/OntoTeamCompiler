#include <stdlib.h>
#include "../IVisitor.h"
#include "CNumberExpression.h"

CNumberExpression::CNumberExpression( const char* number ) {
	this->number = atoi(number);
}

void CNumberExpression::Accept( IVisitor* v ) {
	v->Visit( this );
}