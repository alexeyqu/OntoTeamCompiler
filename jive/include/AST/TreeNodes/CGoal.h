#pragma once

#include "IEntity.h"
#include "IExpression.h"
#include "IStatement.h"

namespace AST 
{

class CGoal : public IVisitorTarget 
{
public:
	CGoal ( IVisitorTarget *_left, IVisitorTarget *_right ) : \
		left( _left ), right( _right ) {}
	
	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IVisitorTarget *getLeft() { return left; }
	IVisitorTarget *getRight() { return right; }

private:
	IVisitorTarget *left;
	IVisitorTarget *right;
};

}