#include "IRTree/CFrame.h"
#include "IRTree/Access.h"

CFrame::CFrame( CSymbol* _name ) : name( _name ), formalsCount( 0 ),
	thisPointer( new CTemp() ),
	framePointer( new CTemp( CSymbol::GetSymbol("FP") ) ),
	returnPointer( new CTemp( CSymbol::GetSymbol( "RP" ) ) ),
	prologueLabel( new CLabel() ), 
	bodyLabel( new CLabel() ), 
	epilogueLabel( new CLabel() )
{
	CTemp* eax = new CTemp( CSymbol::GetSymbol( "EAX" ) );
	CTemp* ecx = new CTemp( CSymbol::GetSymbol( "ECX" ) );
	CTemp* edx = new CTemp( CSymbol::GetSymbol( "EDX" ) );

	callDefArgs = new CTempList( eax, 
		new CTempList( ecx, 
			new CTempList( edx )
		)
	);
}

void CFrame::AddField( CSymbol* name ) {
	fields.InsertObject( name, new CInObjAccess( thisOffset, thisPointer ) );
	thisOffset += wordSize;
}

void CFrame::AddFormal( CSymbol* name ) {
	formals.InsertObject( name, new CInRegAccess( new CTemp() ) );
	formalsCount++;
}

void CFrame::AddLocal( CSymbol* name ) {
	locals.InsertObject( name, new CInFrameAccess( frameOffset, framePointer ) );
	frameOffset += wordSize;
}

int CFrame::GetFormalCount() const { 
	return formalsCount; 
}

IAccess* CFrame::FindVariable( CSymbol* name ) const {
	auto local = locals.GetObject( name );
	if ( local ) {
		return local;
	}

	auto formal = formals.GetObject( name );
	if ( formal ) {
		return formal;
	}

	auto field = fields.GetObject( name );
	if ( field ) {
		return field;
	}

	return nullptr;
}

int CFrame::GetWordSize() { 
	return wordSize; 
}

CTemp* CFrame::FramePointer() const { 
	return framePointer; 
}

CTemp* CFrame::ThisPointer() const { 
	return thisPointer; 
}

CTemp* CFrame::ReturnPointer() const { 
	return returnPointer;  
}

CSymbol* CFrame::GetMethodName() const { 
	return name; 
}

CLabel* CFrame::GetPrologueLabel() const { 
	return prologueLabel; 
}

CLabel* CFrame::GetStartLabel() const { 
	return bodyLabel; 
}

CLabel* CFrame::GetEpilogueLabel() const { 
	return epilogueLabel; 
}

CTempList* CFrame::GetCallDefArgs() const {
	return callDefArgs;
}