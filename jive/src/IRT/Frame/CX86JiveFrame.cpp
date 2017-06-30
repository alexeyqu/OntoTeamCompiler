#include "CX86JiveFrame.h"

namespace IRT
{

CX86JiveFrame::CX86JiveFrame( CSymbol *_symbol ) : symbol( _symbol ), paramsCount( 0 ),
	stackPointer( new CTemp( CSymbol::makeSymbol( "SP" )  ) ),
	basePointer( new CTemp( CSymbol::makeSymbol( "BP" ) ) ),
	returnPointer( new CTemp( CSymbol::makeSymbol( "RP" ) ) ),
	prologueLabel( new CLabel() ), 
	bodyLabel( new CLabel() ), 
	epilogueLabel( new CLabel() ) 
{
	CTemp *eax = new CTemp( CSymbol::makeSymbol( "EAX" ) );
	CTemp *ecx = new CTemp( CSymbol::makeSymbol( "ECX" ) );
	CTemp *edx = new CTemp( CSymbol::makeSymbol( "EDX" ) );

	defaultRegs = new CTempList( eax, 
		new CTempList( ecx, 
			new CTempList( edx )
		)
	);
}

IAccess *CX86JiveFrame::getAccess( CSymbol *_symbol ) const {
	auto local = locals.getObject( _symbol );
	if ( local ) {
		return local;
	}

	auto formal = params.getObject( _symbol );
	if ( formal ) {
		return formal;
	}

	return nullptr;
}
	
}