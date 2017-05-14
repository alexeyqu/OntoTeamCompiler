#include "IRTree/TreeNodes/Stm/EXP.h"

IExp* EXP::GetExp() const { 
	return exp; 
}

void EXP::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}
