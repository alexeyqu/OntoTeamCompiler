#include "CNumberExpression.h"

CNumberExpression::CNumberExpression( const char *_number, CType *_type ) : number( atoi( _number ) ), type( _type ) {}

void CNumberExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

CType *CNumberExpression::getType() {
    //return new CType( enums::INTEGER );
    return type;
}