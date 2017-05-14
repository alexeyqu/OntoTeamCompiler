#pragma once

#include "../ISubtreeWrapper.h"

class CStmConverter : public ISubtreeWrapper
{
public:
	CStmConverter( IStm* _stm ) : stm( _stm ) {}
	IExp* ToExp() const override;
	IStm* ToStm() const override;
	IStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const override;
private:
	IStm* stm;
};