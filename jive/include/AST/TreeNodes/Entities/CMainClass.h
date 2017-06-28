 #pragma once

#include "IEntity.h"
#include "IExpression.h"
#include "IStatement.h"
#include "CClass.h"
#include "CCompoundMethod.h"
#include "CCompoundArgument.h"
#include "CCompoundStatement.h"
#include "CCompoundVariable.h"
#include "CIdExpression.h"
#include "CMethod.h"
#include "CArgument.h"
#include "CVoidExpression.h"

namespace AST 
{

class CMainClass : public CClass
{
public:
	CMainClass( CIdExpression *_name, 
		CIdExpression *_cmdArgs,
		IStatement *_statement );

	void Accept( IVisitor *visitor ) override;
};

}