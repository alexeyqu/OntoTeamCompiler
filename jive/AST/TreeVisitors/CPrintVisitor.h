#pragma once

#include "../IVisitor.h"
#include "../IVisitorTarget.h"
#include "../CProgram.h"
#include "../TreeNodes/CBinaryExpression.h"
#include "../TreeNodes/CNumberExpression.h"
#include <fstream>

class CPrintVisitor : public IVisitor {
public:

	void Start(IVisitorTarget*, std::string, std::string);
	void Visit(CProgram*);
	void Visit(CBinaryExpression*);
	void Visit(CNumberExpression*);
	
private:

	std::ofstream file;
};