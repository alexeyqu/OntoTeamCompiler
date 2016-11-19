#pragma once

#include "IExpression.h"
#include "IStatement.h"
#include "IEntity.h"

class CCompoundTmp : public IVisitorTarget 
{
public:
	CCompoundTmp ( IVisitorTarget *_tmp1, IVisitorTarget *_tmp2 );
	
	void Accept( IVisitor *visitor ) override;

	IVisitorTarget *tmp1;
	IVisitorTarget *tmp2;
};