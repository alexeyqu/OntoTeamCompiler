#pragma once

#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class CExpList : public IExp
{
public:
	CExpList( CExpList*  _head, IExp* _tail ) : head( _head ), tail( _tail ) {};
	CExpList* GetHead() const;
	IExp* GetTail() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	CExpList* head;
	IExp* tail;
};
