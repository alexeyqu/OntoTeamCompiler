 #pragma once

#include <cstdlib>
#include "IExpression.h"

namespace AST 
{

class CArrayIndexExpression : public IExpression
{
public:
	CArrayIndexExpression( IExpression *_id, IExpression *_index ) : \
		id( _id ), index( _index ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	IExpression *getArrayId() const { return id; }
	IExpression *getArrayIndex() const { return index; }

private:
	IExpression *id;
	IExpression *index;
};

}