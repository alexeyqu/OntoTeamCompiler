#include "CMainClass.h"

namespace AST 
{

CMainClass::CMainClass( CIdExpression *_name, 
        CIdExpression *_cmdArgs,
        IStatement *_statement ) : \
    CClass( _name, 
		nullptr, // BaseClass Id
		nullptr, // Fields
		new CCompoundMethod( nullptr, new CMethod( new CType( jive::TType::VOID, new CSymbol( "void" ) ), // public static void main
			new CIdExpression( new CSymbol( "main" ) ),
			new CCompoundArgument( nullptr, new CArgument( new CType( jive::TType::STRINGARRAY, new CSymbol( "String[]" ) ), _cmdArgs ) ), // String[] argId
			nullptr, // variables
			new CCompoundStatement( nullptr, _statement ), // statements
			new CVoidExpression() // retExpression
			) 
		) 
	)
{

}

void CMainClass::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}

}
 