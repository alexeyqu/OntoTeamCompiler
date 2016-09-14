#pragma once

#include "IVisitor.h"
#include "IVisitorTarget.h"
#include <fstream>

class CPrintVisitor: public IVisitor {
	public:
		void Start(IVisitorTarget*, const std::string&, const std::string&);
		void Visit(CCompoundStatement*); //+
		void Visit(CAssignStatement*); //+
		void Visit(CLastExpressionList*);//+
		void Visit(CBinaryExpression*); //+
		void Visit(CNumberExpression*); //+
		void Visit(CIdExpression*); //+
		void Visit(CPrintStatement*);
	private:
    	std::ofstream file;
};