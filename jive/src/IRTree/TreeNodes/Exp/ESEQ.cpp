#include "IRTree/TreeNodes/Exp/ESEQ.h"

IStm* ESEQ::GetStm() const { 
	return stm; 
}

IExp* ESEQ::GetExp() const { 
	return exp; 
}

void ESEQ::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}