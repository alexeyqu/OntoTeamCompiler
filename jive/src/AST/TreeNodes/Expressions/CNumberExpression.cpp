#include "CNumberExpression.h"

CNumberExpression::CNumberExpression( const char *_number, IType *_type ) : number( atoi( _number ) ), type( _type ) {}

void CNumberExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

IType *CNumberExpression::getType() {
    //return new CType( enums::INTEGER );
    return type;
}