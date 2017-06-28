#include "CArgument.h"

namespace AST 
{

CArgument::CArgument( CType *_type, CIdExpression *_id ) : \
	CVariable( _type, _id ) {}

void CArgument::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}