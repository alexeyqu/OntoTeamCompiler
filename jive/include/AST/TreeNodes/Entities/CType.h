#pragma once

#include "../IEntity.h"

class CType : public IEntity
{
public:
   	CType( enums::TType _type );

   	void Accept( IVisitor *visitor ) override;

	enums::TType type;
};