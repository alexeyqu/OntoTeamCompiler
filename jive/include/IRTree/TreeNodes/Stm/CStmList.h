#pragma once

#include "../IStm.h"
#include "IRTree/IIRTreeVisitor.h"

class CStmList : public IStm
{
public:
	CStmList( IStm* _head, CStmList* _tail ) : head( _head ), tail( _tail ) {};
	IStm* GetHead() const;
	CStmList* GetTail() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	IStm* head;
	CStmList* tail;
};
