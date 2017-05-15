#pragma once

#include "IRTree/TreeNodes/Exp/CExpList.h"

IExp* CExpList::GetHead() const { 
	return head; 
}
	
CExpList* CExpList::GetTail() const { 
	return tail; 
}
	
void CExpList::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}