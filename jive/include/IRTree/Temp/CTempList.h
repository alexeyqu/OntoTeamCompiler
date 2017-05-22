#pragma once

#include "CTemp.h"

class CTempList
{
public:
	CTempList( CTemp* _head, CTempList* _tail ) : 
		head( _head ), tail( _tail ) {};
	CTempList( CTemp* _head ) : head( _head ), tail( nullptr ) {};
	CTempList( CTemp* one, CTemp* two );
	CTempList( CTemp* one, CTemp* two, CTemp* three );
	CTemp* GetHead() const;
	CTempList* GetTail() const;
private:
	CTemp* head;
	CTempList* tail;
};