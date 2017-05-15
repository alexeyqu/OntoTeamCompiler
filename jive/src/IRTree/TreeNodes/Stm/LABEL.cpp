#include "IRTree/TreeNodes/Stm/LABEL.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

CLabel* LABEL::GetLabel() const { 
	return label; 
}

void LABEL::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* LABEL::Kids() {
	return nullptr;
}

IStm* LABEL::Build( CExpList* kids ) {
	return this;
}