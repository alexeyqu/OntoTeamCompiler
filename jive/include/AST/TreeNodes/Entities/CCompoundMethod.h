#pragma once

#include "IEntity.h"

class CCompoundMethod : public IEntity
{
public:
   	CCompoundMethod( CCompoundMethod *_method1, CMethod *_method2 );

   	void Accept( IVisitor *visitor ) override;

	CCompoundMethod *method1;
	CMethod *method2;
};

