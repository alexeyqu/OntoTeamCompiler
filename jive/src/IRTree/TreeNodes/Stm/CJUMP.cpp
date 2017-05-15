#include "IRTree/TreeNodes/Stm/CJUMP.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"
#include <cassert>

enums::TCJump CJUMP::GetOp() const { 
	return op; 
}

enums::TCJump CJUMP::GetNotOp() const {
	using namespace enums;
	switch( op ) {
	case EQ:  
		return NE;
	case NE:  
		return EQ;
	case LT:  
		return GE;
	case GE:  
		return LT;
	case GT:  
		return LE;
	case LE:  
		return GT;
	default:
		assert( false );
	}
}

IExp* CJUMP::GetLeft() const { 
	return left; 
}
	
IExp* CJUMP::GetRight() const { 
	return right; 
}

CLabel* CJUMP::GetIfTrue() const { 
	return ifTrue; 
}

CLabel* CJUMP::GetIfFalse() const { 
	return ifFalse; 
}

void CJUMP::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* CJUMP::Kids() {
	return new CExpList( left, new CExpList( right, nullptr ) );
}

IStm* CJUMP::Build( CExpList* kids ) {
	return new CJUMP( op, kids->GetHead(), 
		kids->GetTail()->GetHead(), ifTrue, ifFalse ); 
}