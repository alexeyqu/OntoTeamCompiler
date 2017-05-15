#pragma once

#include "IRTree/IIRTreeVisitor.h"

class IStm
{
public:
	virtual ~IStm() {};
	virtual void Accept( IIRTreeVisitor* visitor ) = 0;

	virtual CExpList* Kids() = 0;
	virtual IStm* Build( CExpList* kids ) = 0;
};