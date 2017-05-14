#pragma once

#include "CTemp.h"

class CTempList
{
public:
	CTempList( const CTemp* _head, const CTempList* _tail ) : 
		head( _head ), tail( _tail ) {};
	CTempList( const CTemp* _head ) : head( _head ), tail( nullptr ) {};
	CTempList( const CTemp* one, const CTemp* two );
	CTempList( const CTemp* one, const CTemp* two, const CTemp* three );
	const CTemp* GetHead() const;
	const CTempList* GetTail() const;
private:
	const CTemp* head;
	const CTempList* tail;
};