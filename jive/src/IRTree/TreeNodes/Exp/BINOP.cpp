#include "IRTree/TreeNodes/Exp/BINOP.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

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

CExpList* BINOP::Kids() {
	return new CExpList( left, new CExpList( right, nullptr ) );
}

IExp* BINOP::Build( CExpList* kids ) {
	return new BINOP( op, kids->GetHead(), kids->GetTail()->GetHead() );
}