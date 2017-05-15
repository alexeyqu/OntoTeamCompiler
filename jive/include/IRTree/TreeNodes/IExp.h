#pragma once

#include "IRTree/IIRTreeVisitor.h"

class IExp
{
public:
	virtual ~IExp() {};
	virtual void Accept( IIRTreeVisitor *visitor ) = 0;

	virtual CExpList* Kids() = 0;
	virtual IExp* Build( CExpList* kids ) = 0;
};