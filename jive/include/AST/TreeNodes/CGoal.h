#pragma once

#include "IEntity.h"
#include "IExpression.h"
#include "IStatement.h"

namespace AST 
{

class CGoal : public IVisitorTarget 
{
public:
	CGoal ( IVisitorTarget *_left, IVisitorTarget *_right );
	
	void Accept( IVisitor *visitor ) override;

	IVisitorTarget *left;
	IVisitorTarget *right;
};

}