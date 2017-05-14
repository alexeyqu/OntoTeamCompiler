#include "IRTree/TreeNodes/Exp/TEMP.h"

const CTemp* TEMP::GetTemp() const { 
	return temp; 
}
	
void TEMP::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}