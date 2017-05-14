#include "IRTree/TreeNodes/Stm/JUMP.h"
#include "IRTree/TreeNodes/Exp/NAME.h"

JUMP::JUMP( CLabel* label ) : exp( new NAME( label ) ), targets( new CLabelList( label ) ) {};

IExp* JUMP::GetExp() const { 
	return exp; 
}

CLabelList* JUMP::GetTargets() const { 
	return targets; 
}

void JUMP::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}