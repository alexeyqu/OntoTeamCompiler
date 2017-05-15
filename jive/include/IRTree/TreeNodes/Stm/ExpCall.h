#pragma once

#include "../IStm.h"
#include "IRTree/IIRTreeVisitor.h"

class ExpCall : public IStm
{
public:
	ExpCall( CALL* _call ) : call( _call ) {};

	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IStm* Build( CExpList* kids );

private:
	CALL* call;
};
