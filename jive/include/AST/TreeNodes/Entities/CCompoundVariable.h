#pragma once

#include "IEntity.h"

namespace AST 
{

class CCompoundVariable : public IEntity
{
public:
   	CCompoundVariable( CCompoundVariable *_var1, CVariable *_var2 );

   	void Accept( IVisitor *visitor ) override;

	CCompoundVariable *var1;
	CVariable *var2;
};
 
}