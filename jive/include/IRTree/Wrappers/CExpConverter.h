#pragma once

#include "../ISubtreeWrapper.h"

class CExpConverter : public ISubtreeWrapper
{
public:
	CExpConverter( IExp* _expr ) : expr( _expr ) {}
	IExp* ToExp() const override;
	IStm* ToStm() const override;
	IStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const override;

private:
	IExp* expr;
};