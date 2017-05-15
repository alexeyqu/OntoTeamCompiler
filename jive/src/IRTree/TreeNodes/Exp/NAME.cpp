#include "IRTree/TreeNodes/Exp/NAME.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

const CLabel* NAME::GetLabel() const { 
	return label; 
}

void NAME::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* NAME::Kids() {
	return nullptr;
}

IExp* NAME::Build( CExpList* kids ) {
	return this;
}