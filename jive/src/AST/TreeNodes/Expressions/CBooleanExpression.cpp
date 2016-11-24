#include "CBooleanExpression.h"

CBooleanExpression::CBooleanExpression( bool _value, IType *_type ) : value( _value ), type( _type ) {}

void CBooleanExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

IType *CBooleanExpression::getType() {
    // return new CType( enums::BOOLEAN );
    return type;
}