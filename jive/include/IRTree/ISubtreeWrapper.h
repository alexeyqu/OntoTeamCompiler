#pragma once

#include "TreeNodes/IExp.h"
#include "TreeNodes/IStm.h"
#include "Temp/CLabel.h"

class ISubtreeWrapper
{
public:
	virtual ~ISubtreeWrapper() {}
	virtual IExp* ToExp() const = 0;
	virtual IStm* ToStm() const = 0;
	virtual IStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const = 0;
};