#include "AST/TreeNodes/Entities/CCompoundArgument.h"

CCompoundArgument::CCompoundArgument( CArgument *_arg1, CCompoundArgument *_arg2 ) : 
	arg1( _arg1 ), arg2( _arg2 ) {}

void CCompoundArgument::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}