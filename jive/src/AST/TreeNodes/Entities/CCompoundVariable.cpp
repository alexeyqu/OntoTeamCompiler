#include "CCompoundVariable.h"

namespace AST 
{

CCompoundVariable::CCompoundVariable( 
	CCompoundVariable *_var1, 
	CVariable *_var2 ) : \
	var1( _var1 ), var2( _var2 ) {}

void CCompoundVariable::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}