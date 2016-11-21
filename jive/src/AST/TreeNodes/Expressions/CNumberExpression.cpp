#include "CNumberExpression.h"

CNumberExpression::CNumberExpression( const char *_number ) : number( atoi( _number ) ), type( enums::INTEGER ) {}

void CNumberExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

enums::TType CNumberExpression::getType() {
	return type;
}