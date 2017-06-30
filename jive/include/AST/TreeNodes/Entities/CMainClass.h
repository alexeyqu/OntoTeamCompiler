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
		IStatement *_statement ) : \
    CClass( _name, 
		nullptr, // BaseClass Id
		nullptr, // Fields
		new CCompoundMethod( nullptr, 
			new CMethod( new CType( jive::TType::VOID, CSymbol::makeSymbol( "void" ) ), // public static void
				new CIdExpression( CSymbol::makeSymbol( "main" ) ), // main
				new CCompoundArgument( nullptr, new CArgument( new CType( jive::TType::STRINGARRAY, CSymbol::makeSymbol( "String[]" ) ), _cmdArgs ) ), // String[] argId
				nullptr, // variables
				new CCompoundStatement( nullptr, _statement ), // statements
				new CVoidExpression() // retExpression
			) 
		) 
	) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }
};

}