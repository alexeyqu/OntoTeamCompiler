#include "CVariable.h"

namespace AST 
{
	
CVariable::CVariable( IType *_type, CIdExpression *_id ) : \
	type( _type ), id( _id ) {}

void CVariable::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}