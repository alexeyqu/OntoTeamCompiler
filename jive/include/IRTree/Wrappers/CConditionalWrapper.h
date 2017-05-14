#pragma once

#include "../ISubtreeWrapper.h"

class CConditionalWrapper : public ISubtreeWrapper
{
public:
	IExp* ToExp() const override;
	IStm* ToStm() const override;
	IStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const = 0;
};