#pragma once

#include "IEntity.h"

namespace AST 
{

class CCompoundMethod : public IEntity
{
public:
   	CCompoundMethod( CCompoundMethod *_method1, CMethod *_method2 ) : \
	   method1( _method1 ), method2( _method2 ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	CCompoundMethod *getNextMethod() const { return method1; }
	CMethod *getMethod() const { return method2; }

private:
	CCompoundMethod *method1;
	CMethod *method2;
};

}