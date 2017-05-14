#include "IRTree/TreeNodes/Exp/BINOP.h"

enums::TBinop BINOP::GetOp() const { 
	return op; 
}

IExp* BINOP::GetLeft() const { 
	return left; 
}

IExp* BINOP::GetRight() const { 
	return right; 
}

void BINOP::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}