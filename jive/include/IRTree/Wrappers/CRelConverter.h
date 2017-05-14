#pragma once

#include "CConditionalWrapper.h"
#include "IRTree/TreeNodes/Nodes.h"

class CRelConverter : public CConditionalWrapper
{
public:
	CRelConverter( enums::TCJump _op, IExp* _left, IExp* _right )
		:  left( _left ), right( _right ), op( _op ) {};
	IStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const;

private:
	IExp* left;
	IExp* right;
	enums::TCJump op;
};