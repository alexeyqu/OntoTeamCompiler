#include "CArgument.h"

namespace AST 
{

CArgument::CArgument( CType *_type, CIdExpression *_id ) : \
	type( _type ), id( _id ) {}

void CArgument::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}