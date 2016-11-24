#pragma once

#include <string>
#include "CType.h"
#include "IExpression.h"

class CJiveEnvironment;

class CIdExpression : public IExpression
{
public:
   	CIdExpression( const char *_name, CJiveEnvironment *_jiveEnv, CType *_type = new CType ( enums::IDENTIFIER ) );

   	void Accept( IVisitor *visitor ) override;
    CType *getType() override;

   	std::string name;
    CType *type;
    CJiveEnvironment *jiveEnv;
};