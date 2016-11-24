#pragma once

#include <string>
#include "../IExpression.h"

class CThisExpression : public IExpression
{
public:
   	CThisExpression( std::size_t _address = 0, IType *_type = new CBuiltInType ( enums::FAKETYPE ) );

   	void Accept( IVisitor *visitor ) override;
    IType *getType() override;

   	std::size_t address;
    IType *type;
};