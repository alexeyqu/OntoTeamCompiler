#include "CMethodCallExpression.h"

CMethodCallExpression::CMethodCallExpression( IExpression *_base, CIdExpression *_methodId, IExpression *_arg ) : \
    base( _base ), methodId( _methodId ), arg( _arg ) {}

void CMethodCallExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}