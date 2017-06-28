#pragma once

#include "IEntity.h"

namespace AST 
{

class CCompoundVariable : public IEntity
{
public:
   	CCompoundVariable( CCompoundVariable *_var1, CVariable *_var2 ) : \
		var1( _var1 ), var2( _var2 ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	CCompoundVariable *getNextVariable() const { return var1; }
	CVariable *getVariable() const { return var2; }

private:
	CCompoundVariable *var1;
	CVariable *var2;
};
 
}