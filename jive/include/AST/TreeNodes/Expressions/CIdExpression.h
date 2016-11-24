#pragma once

#include <string>
#include "IType.h"
#include "IExpression.h"

class CJiveEnvironment;

class CIdExpression : public IExpression
{
public:
   	CIdExpression( const char *_name, CJiveEnvironment *_jiveEnv, IType *_type = new CBuiltInType ( enums::IDENTIFIER ) );

   	void Accept( IVisitor *visitor ) override;
    IType *getType() override;

   	std::string name;
    IType *type;
    CJiveEnvironment *jiveEnv;
};