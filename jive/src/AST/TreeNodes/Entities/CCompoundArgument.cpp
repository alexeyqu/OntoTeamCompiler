#include "AST/TreeNodes/Entities/CCompoundArgument.h"

CCompoundArgument::CCompoundArgument( 
	CCompoundArgument *_arg1, 
	CArgument *_arg2 ) : \
	arg1( _arg1 ), arg2( _arg2 ) {}

void CCompoundArgument::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}