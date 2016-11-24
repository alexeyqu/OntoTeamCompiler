#include "CArrayLengthExpression.h"

CArrayLengthExpression::CArrayLengthExpression( IExpression *_exp, IType *_type ) : exp( _exp ), type( _type ) {}

void CArrayLengthExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

IType *CArrayLengthExpression::getType() {
    // return new CType( enums::INTEGER );
    return type;
}