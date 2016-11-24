#pragma once

#include <string>
#include "../IExpression.h"

class CThisExpression : public IExpression
{
public:
   	CThisExpression( std::size_t _address = 0, CType *_type = new CType ( enums::FAKETYPE ) );

   	void Accept( IVisitor *visitor ) override;
    CType *getType() override;

   	std::size_t address;
    CType *type;
};