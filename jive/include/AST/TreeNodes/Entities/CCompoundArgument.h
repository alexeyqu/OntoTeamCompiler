#pragma once

#include "../IEntity.h"

class CCompoundArgument : public IEntity
{
public:
   	CCompoundArgument( CArgument *_arg1, CCompoundArgument *_arg2 );

   	void Accept( IVisitor *visitor ) override;

	CArgument *arg1;
	CCompoundArgument *arg2;
};
