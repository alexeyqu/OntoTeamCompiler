#include "IRTree/TreeNodes/Exp/CONST.h"

int CONST::GetValue() const { 
	return value; 
}

void CONST::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

