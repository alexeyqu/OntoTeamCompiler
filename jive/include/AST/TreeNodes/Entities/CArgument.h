#pragma once

#include "CType.h"
#include "IEntity.h"

namespace AST 
{

class CArgument : public IEntity
{
public:
   	CArgument( CType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	CType *type;
	CIdExpression *id;
};

}