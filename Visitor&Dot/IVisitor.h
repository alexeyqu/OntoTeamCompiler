#pragma once

class IVisitorTarget;
class CCompoundStatement;
class CIdExpression;
class CBinaryExpression;
class CNumberExpression;
class CAssignStatement;
class CPrintStatement;
class CLastExpressionList;

class IVisitor
{
public:
	virtual void Visit( CCompoundStatement* ) = 0;
	virtual void Visit( CIdExpression* ) = 0;
	virtual void Visit( CBinaryExpression* ) = 0;
   	virtual void Visit( CNumberExpression* ) = 0;
   	virtual void Visit( CAssignStatement* ) = 0;
   	virtual void Visit( CPrintStatement* ) = 0;
   	virtual void Visit( CLastExpressionList* ) = 0;
};
