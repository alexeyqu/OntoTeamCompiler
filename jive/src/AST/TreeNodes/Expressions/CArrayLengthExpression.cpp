#include "CArrayLengthExpression.h"

CArrayLengthExpression::CArrayLengthExpression( IExpression *_exp, CType *_type ) : exp( _exp ), type( _type ) {}

void CArrayLengthExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

CType *CArrayLengthExpression::getType() {
    // return new CType( enums::INTEGER );
    return type;
}