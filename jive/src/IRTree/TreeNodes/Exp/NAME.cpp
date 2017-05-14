#include "IRTree/TreeNodes/Exp/NAME.h"

const CLabel* NAME::GetLabel() const { 
	return label; 
}

void NAME::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}