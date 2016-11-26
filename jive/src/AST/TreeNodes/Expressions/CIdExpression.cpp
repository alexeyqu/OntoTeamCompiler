#include "CIdExpression.h"

#include "CJiveEnvironment.h"
extern CJiveEnvironment *jiveEnv;

CIdExpression::CIdExpression( const char *_name ) : \
	name( _name ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}