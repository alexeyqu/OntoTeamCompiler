#pragma once

#include "IEntity.h"

namespace AST 
{

class CCompoundArgument : public IEntity
{
public:
   	CCompoundArgument( CCompoundArgument *_arg1, CArgument *_arg2 ) : \
	   arg1( _arg1 ), arg2( _arg2 ) {}
	
   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	CCompoundArgument *getNextArgument() const { return arg1; }
	CArgument *getArgument() const { return arg2; }

private:
	CCompoundArgument *arg1;
	CArgument *arg2;
};

}