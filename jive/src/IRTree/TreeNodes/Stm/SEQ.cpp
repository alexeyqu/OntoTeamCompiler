#include "IRTree/TreeNodes/Stm/SEQ.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"
#include <cassert>

IStm* SEQ::GetLeft() const { 
	return left; 
}

IStm* SEQ::GetRight() const { 
	return right; 
}

void SEQ::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* SEQ::Kids() {
	assert( false );
	return nullptr;
}

IStm* SEQ::Build( CExpList* kids ) {
	assert( false );
	return nullptr;
}