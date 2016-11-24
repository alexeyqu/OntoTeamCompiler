#include "CIdExpression.h"

#include "CJiveEnvironment.h"
extern CJiveEnvironment *jiveEnv;

CIdExpression::CIdExpression( const char *_name, IType *_type ) : \
	name( _name ), type( _type ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

IType *CIdExpression::getType() {
   // std::cout << this->name << "\n";
    return type;
}