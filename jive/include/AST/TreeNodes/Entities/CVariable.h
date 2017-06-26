#pragma once

#include "CType.h"
#include "IEntity.h"
#include "CIdExpression.h"

namespace AST 
{

class CVariable : public IEntity
{
public:
   	CVariable( CType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	CType *type;
	CIdExpression *id;
};

}