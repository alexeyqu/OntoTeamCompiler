#pragma once

#include "../IStm.h"
#include "IRTree/IIRTreeVisitor.h"

class MoveCall : public IStm
{
public:
	MoveCall( TEMP* _dest, CALL* _src ) : dest( _dest ), src( _src ) {};

	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IStm* Build( CExpList* kids );

private:
	TEMP* dest;
	CALL* src;
};
