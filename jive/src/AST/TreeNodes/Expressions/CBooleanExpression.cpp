#include "CBooleanExpression.h"

CBooleanExpression::CBooleanExpression( bool _value ) : value( _value ), type( enums::BOOLEAN ) {}

void CBooleanExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

enums::TType CBooleanExpression::getType() {
	return type;
}