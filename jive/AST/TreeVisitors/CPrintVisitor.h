#pragma once

#include <fstream>
#include <cassert>
#include "../IVisitor.h"
#include "../IVisitorTarget.h"
#include "../CProgram.h"
#include "../TreeNodes/CCompoundStatement.h"
#include "../TreeNodes/CAssignStatement.h"
#include "../TreeNodes/CPrintStatement.h"
#include "../TreeNodes/CIdExpression.h"
#include "../TreeNodes/CBinaryExpression.h"
#include "../TreeNodes/CNumberExpression.h"

class CPrintVisitor : public IVisitor 
{
public:
	void Start( IVisitorTarget *vertex, std::string graphname );
	
	void Visit( CProgram *program );
	void Visit( CCompoundStatement *statement );
	void Visit( CAssignStatement *statement );
	void Visit( CPrintStatement *statement );
	void Visit( CIdExpression *expression );
	void Visit( CBinaryExpression *expression );
	void Visit( CNumberExpression *expression );
	
private:
	std::size_t generateId( void *entity );

	std::ofstream file;
};