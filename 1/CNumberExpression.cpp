#include "IVisitor.h"
#include "CNumberExpression.h"

CNumberExpression::CNumberExpression( int value ) {
	this->value = value;
}

void CNumberExpression::Accept( IVisitor* v ) {
	v->Visit( this );
}
