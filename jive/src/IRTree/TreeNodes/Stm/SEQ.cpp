#include "IRTree/TreeNodes/Stm/SEQ.h"

IStm* SEQ::GetLeft() const { 
	return left; 
}

IStm* SEQ::GetRight() const { 
	return right; 
}

void SEQ::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}