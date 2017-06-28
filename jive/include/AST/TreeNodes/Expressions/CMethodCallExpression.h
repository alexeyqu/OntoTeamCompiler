#pragma once

#include "IExpression.h"

namespace AST 
{

class CMethodCallExpression : public IExpression
{
public:
	CMethodCallExpression( IExpression *_base, CIdExpression *_methodId, IExpression *_arg ) : \
		base( _base ), methodId( _methodId ), arg( _arg ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }
		
	CSymbol *getMethodSymbol() const { return methodId->getSymbol(); }
	boost::flyweight<std::string> &getMethodString() const { return methodId->getString(); }

	IExpression *getBaseExpression() const { return base; }
	CIdExpression *getMethodId() const { return methodId; }
	IExpression *getArguments() const { return arg; }

private:
	IExpression *base;
	CIdExpression *methodId;
	IExpression *arg;
};

}