#pragma once

#include "CLabel.h"

class CLabelList
{
public:
	CLabelList( CLabel* _head, CLabelList* _tail )
		: head( _head ), tail( _tail ) {};
	CLabelList( CLabel* _head ): head( _head ), tail( nullptr ) {};
	CLabelList::CLabelList( CLabel* one, CLabel* two ) :
		head( one ), tail( new CLabelList( two ) ) {}
	CLabel* GetHead() const;
	CLabelList* GetTail() const;
private:
	CLabel* head;
	CLabelList* tail;
};