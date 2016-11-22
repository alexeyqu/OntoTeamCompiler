#pragma once

#include "../IEntity.h"
#include "../IExpression.h"

class CVariable : public IEntity
{
public:
   	CVariable( IEntity *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	IEntity *type;
	CIdExpression *id;
};