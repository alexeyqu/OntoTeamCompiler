#include <stdlib.h>
#include "../IVisitor.h"
#include "CNumberExpression.h"

CNumberExpression::CNumberExpression( const char *_number ) : number( atoi( _number ) ) {}

void CNumberExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}