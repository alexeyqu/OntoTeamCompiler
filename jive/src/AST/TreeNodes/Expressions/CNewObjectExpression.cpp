#include "CNewObjectExpression.h"

CNewObjectExpression::CNewObjectExpression( CIdExpression *_objTypeId, IType *_type ) : objTypeId( _objTypeId ), type( _type ) {}

void CNewObjectExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

IType *CNewObjectExpression::getType() {
   // return new CType( enums::CLASS );
    return type;
}