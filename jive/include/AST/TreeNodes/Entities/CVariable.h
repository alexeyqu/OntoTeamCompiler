#pragma once

#include "IType.h"
#include "IEntity.h"
#include "CIdExpression.h"

namespace AST 
{

class CVariable : public IEntity
{
public:
   	CVariable( IType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	IType *type;
	CIdExpression *id;
};

}