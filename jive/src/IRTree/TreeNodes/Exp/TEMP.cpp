#include "IRTree/TreeNodes/Exp/TEMP.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

const CTemp* TEMP::GetTemp() const { 
	return temp; 
}
	
void TEMP::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* TEMP::Kids() {
	return nullptr;
}

IExp* TEMP::Build( CExpList* kids ) {
	return this;
}