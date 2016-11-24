#include "CArrayIndexExpression.h"

CArrayIndexExpression::CArrayIndexExpression( IExpression *_id, IExpression *_index, CType *_type ) : \
    id( _id ), index( _index ), type( _type ) {}

void CArrayIndexExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

CType *CArrayIndexExpression::getType() {
    // return new CType( enums::INTEGER );
    return type;
}