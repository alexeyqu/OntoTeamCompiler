#include "CNewObjectExpression.h"

CNewObjectExpression::CNewObjectExpression( CIdExpression *_objTypeId, CType *_type ) : objTypeId( _objTypeId ), type( _type ) {}

void CNewObjectExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

CType *CNewObjectExpression::getType() {
   // return new CType( enums::CLASS );
    return type;
}