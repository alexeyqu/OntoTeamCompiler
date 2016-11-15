#pragma once

#include "../IVisitor.h"
#include "../IVisitorTarget.h"
#include "../CProgram.h"
#include "../TreeNodes/CBinaryExpression.h"
#include "../TreeNodes/CNumberExpression.h"
#include <fstream>

class CPrintVisitor : public IVisitor 
{
public:
	void Start( IVisitorTarget *vertex, std::string graphname );
	void Visit( CProgram *program );
	void Visit( CBinaryExpression *expression );
	void Visit( CNumberExpression *expression );
	
private:
	std::ofstream file;
};