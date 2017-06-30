#pragma once

#include "IVisitorTarget.h"
#include "Types.h"

namespace AST 
{

class IExpression : public IVisitorTarget {
public:
	IExpression() { type = new CType( jive::TType::VOID, CSymbol::makeSymbol( "???" ) ); }
	CType *getType() const { return type; }

	void setType( CType *_type ) { type = _type; }

private:
	CType *type;
};

}