#include "CArrayIndexExpression.h"

CArrayIndexExpression::CArrayIndexExpression( IExpression *_id, IExpression *_index, IType *_type ) : \
    id( _id ), index( _index ), type( _type ) {}

void CArrayIndexExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

IType *CArrayIndexExpression::getType() {
    // return new CType( enums::INTEGER );
    return type;
}