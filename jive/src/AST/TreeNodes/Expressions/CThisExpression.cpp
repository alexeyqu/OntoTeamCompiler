#include "CThisExpression.h"

CThisExpression::CThisExpression( std::size_t _address, CType *_type ) : \
	address( _address ), type( _type ) {}

void CThisExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

CType *CThisExpression::getType() {
    //return new CType( enums::FAKETYPE );
    return type;
}