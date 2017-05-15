#include "IRTree/TreeNodes/Exp/ESEQ.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"
#include <cassert>

IStm* ESEQ::GetStm() const { 
	return stm; 
}

IExp* ESEQ::GetExp() const { 
	return exp; 
}

void ESEQ::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* ESEQ::Kids() {
	assert( false );
	return nullptr;
}

IExp* ESEQ::Build( CExpList* kids ) {
	assert( false );
	return nullptr;
}