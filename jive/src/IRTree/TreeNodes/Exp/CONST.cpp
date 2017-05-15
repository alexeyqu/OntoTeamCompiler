#include "IRTree/TreeNodes/Exp/CONST.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

int CONST::GetValue() const { 
	return value; 
}

void CONST::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* CONST::Kids() { 
	return nullptr; 
}

IExp* CONST::Build( CExpList* kids ) { 
	return this;
}

