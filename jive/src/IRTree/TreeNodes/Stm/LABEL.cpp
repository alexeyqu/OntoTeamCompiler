#include "IRTree/TreeNodes/Stm/LABEL.h"

CLabel* LABEL::GetLabel() const { 
	return label; 
}

void LABEL::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}