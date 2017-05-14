#include "IRTree/Temp/CTempList.h"	

CTempList::CTempList( const CTemp* one, const CTemp* two ) {
	head = one;
	tail = new CTempList( two );
}
	
CTempList::CTempList( const CTemp* one, const CTemp* two, const CTemp* three ) {
	head = one;
	tail = new CTempList( two, three );
}

const CTemp* CTempList::GetHead() const { 
	return head; 
}

const CTempList* CTempList::GetTail() const { 
	return tail; 
}