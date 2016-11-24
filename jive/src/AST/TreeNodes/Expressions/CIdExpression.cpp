#include "CIdExpression.h"

#include "CJiveEnvironment.h"
extern CJiveEnvironment *jiveEnv;

CIdExpression::CIdExpression( const char *_name, CJiveEnvironment *_jiveEnv, IType *_type ) : \
	name( _name ), jiveEnv( _jiveEnv ), type( _type ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

IType *CIdExpression::getType() {
   // std::cout << this->name << "\n";
    return jiveEnv->symbolTable->Lookup(this)->type;
}