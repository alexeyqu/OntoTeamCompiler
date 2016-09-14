#pragma once

#include "IVisitor.h"
#include "IVisitorTarget.h"
#include "CAssignStatement.h"
#include "CBinaryExpression.h"
#include "CCompoundStatement.h"
#include "CLastExpressionList.h"
#include "CNumberExpression.h"
#include "CPrintStatement.h"
#include "CPrintVisitor.h"
#include "CIdExpression.h"
#include <fstream>

class CPrintVisitor : public IVisitor {
	public:
		void Start(IVisitorTarget*, std::string, std::string);
		void Visit(CCompoundStatement*);
		void Visit(CAssignStatement*);
		void Visit(CLastExpressionList*);
		void Visit(CBinaryExpression*);
		void Visit(CNumberExpression*);
		void Visit(CIdExpression*);
		void Visit(CPrintStatement*);
	private:
    	std::ofstream file;
};