#include "IRTree/TreeNodes/Stm/MOVE.h"

IExp* MOVE::GetDst() const { 
	return dest; 
}

IExp* MOVE::GetSrc() const { 
	return src; 
}

void MOVE::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}