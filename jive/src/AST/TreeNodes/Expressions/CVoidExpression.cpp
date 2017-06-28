#include "CVoidExpression.h"

namespace AST 
{

CVoidExpression::CVoidExpression() : \
	IExpression() {}

void CVoidExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}