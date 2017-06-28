#pragma once

#include "CType.h"
#include "IEntity.h"
#include "CVariable.h"

namespace AST 
{

class CArgument : public CVariable
{
public:
   	CArgument( CType *_type, CIdExpression *_id ) : CVariable( _type, _id ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }
};

}