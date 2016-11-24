#include "CMethodCallExpression.h"

CMethodCallExpression::CMethodCallExpression( IExpression *_base, CIdExpression *_methodId, IExpression *_arg, IType *_type ) : \
    base( _base ), methodId( _methodId ), arg( _arg ), type( _type ) {}

void CMethodCallExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

IType *CMethodCallExpression::getType() {
    // return new CType( enums::FAKETYPE );
    return type;
}