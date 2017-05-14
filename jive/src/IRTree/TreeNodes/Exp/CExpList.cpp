#pragma once

#include "IRTree/TreeNodes/Exp/CExpList.h"

CExpList* CExpList::GetHead() const { 
	return head; 
}
	
IExp* CExpList::GetTail() const { 
	return tail; 
}
	
void CExpList::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}