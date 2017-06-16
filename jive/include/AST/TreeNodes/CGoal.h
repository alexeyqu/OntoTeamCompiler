#pragma once

#include "IEntity.h"
#include "IExpression.h"
#include "IStatement.h"

class CGoal : public IVisitorTarget 
{
public:
	CGoal ( IVisitorTarget *_tmp1, IVisitorTarget *_tmp2 );
	
	void Accept( IVisitor *visitor ) override;

	IVisitorTarget *tmp1;
	IVisitorTarget *tmp2;
};