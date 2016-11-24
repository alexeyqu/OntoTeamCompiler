#include "CThisExpression.h"

CThisExpression::CThisExpression( std::size_t _address, IType *_type ) : \
	address( _address ), type( _type ) {}

void CThisExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

IType *CThisExpression::getType() {
    //return new CType( enums::FAKETYPE );
    return type;
}