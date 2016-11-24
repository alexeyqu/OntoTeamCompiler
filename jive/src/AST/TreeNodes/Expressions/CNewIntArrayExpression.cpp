#include "CNewIntArrayExpression.h"

CNewIntArrayExpression::CNewIntArrayExpression( IExpression *_arrSize, IType *_type ) : arrSize( _arrSize ), type( _type ) {}

void CNewIntArrayExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

IType *CNewIntArrayExpression::getType() {
    // return new CType( enums::INTEGERARRAY );
    return type;
}