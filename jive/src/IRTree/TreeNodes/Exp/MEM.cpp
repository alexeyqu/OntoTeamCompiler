#include "IRTree/TreeNodes/Exp/MEM.h"

IExp* MEM::GetExp() const { 
	return exp; 
}

void MEM::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}