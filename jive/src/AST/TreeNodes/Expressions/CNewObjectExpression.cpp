#include "CNewObjectExpression.h"

namespace AST 
{

CNewObjectExpression::CNewObjectExpression( CIdExpression *_objTypeId ) : objTypeId( _objTypeId ) {}

void CNewObjectExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}