#include "CArrayIndexExpression.h"

CArrayIndexExpression::CArrayIndexExpression( IExpression *_id, IExpression *_index ) : \
    id( _id ), index( _index ) {}

void CArrayIndexExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}
