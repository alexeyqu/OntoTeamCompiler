#include "CBooleanExpression.h"

CBooleanExpression::CBooleanExpression( bool _value, CType *_type ) : value( _value ), type( _type ) {}

void CBooleanExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

CType *CBooleanExpression::getType() {
    // return new CType( enums::BOOLEAN );
    return type;
}