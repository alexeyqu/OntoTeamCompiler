#include "CThisExpression.h"

CThisExpression::CThisExpression( std::size_t _address ) : \
	address( _address ) {}

void CThisExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}