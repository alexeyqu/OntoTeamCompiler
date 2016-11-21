#pragma once

#include <fstream>
#include <cassert>
#include "../CProgram.h"

class CPrintVisitor : public IVisitor 
{
public:
	void Start( IVisitorTarget *vertex, std::string graphname );
	
	void Visit( CProgram *program );
   	void Visit( CCompoundTmp *tmp );
	void Visit( CType *entity );
	void Visit( CLocalVariable *entity );
	void Visit( CCompoundStatement *statement );
	void Visit( CAssignStatement *statement );
	void Visit( CPrintStatement *statement );
	void Visit( CIfStatement *statement );
	void Visit( CWhileStatement *statement );
	void Visit( CIdExpression *expression );
	void Visit( CBinaryExpression *expression );
	void Visit( CNumberExpression *expression );   	
	void Visit( CBinaryBooleanExpression *expression );
   	void Visit( CBooleanExpression *expression );
	
private:
	std::size_t generateId( void *entity );

	std::ofstream file;
};