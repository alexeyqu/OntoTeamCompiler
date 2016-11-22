#pragma once

#include "../IEntity.h"

class CCompoundArgument : public IEntity
{
public:
   	CCompoundArgument( CCompoundArgument *_arg1, CArgument *_arg2 );

   	void Accept( IVisitor *visitor ) override;

	CCompoundArgument *arg1;
	CArgument *arg2;
};
