#pragma once

#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

// Выражения в обратном порядке

class CExpList
{
public:
	CExpList( IExp* _head, CExpList* _tail ) : head( _head ), tail( _tail ) {};
	IExp* GetHead() const;
	CExpList* GetTail() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	IExp* head;
	CExpList* tail;
};
