#pragma once

#include "IAccess.h"
#include "ST/CSymbol.h"
#include "ST/CSymbolStorage.h"
#include "IRTree/Temp/CLabel.h"
#include "IRTree/Temp/CTempList.h"

class CFrame {
public:
	CFrame( CSymbol* _name );

	void AddField( CSymbol* name );
	void AddFormal( CSymbol* name );
	void AddLocal( CSymbol* name );
	int GetFormalCount() const;
	IAccess* FindVariable( CSymbol* name ) const;
	static int GetWordSize();
	CTemp* FramePointer() const;
	CTemp* ThisPointer() const;
	CTemp* ReturnPointer() const;
	CSymbol* GetMethodName() const;
	CLabel* GetPrologueLabel() const;
	CLabel* GetStartLabel() const;
	CLabel* GetEpilogueLabel() const;
	CTempList* GetCallDefArgs() const;

	CTempList* callDefArgs;

private:
	static const int wordSize = 4;
	CSymbol* name;

	int formalsCount;
	int thisOffset;
	int frameOffset;
	
	CSymbolStorage<IAccess*> fields;
	CSymbolStorage<IAccess*> formals;
	CSymbolStorage<IAccess*> locals;

	CTemp* framePointer;
	CTemp* thisPointer;
	CTemp* returnPointer;

	CLabel* prologueLabel;
	CLabel* bodyLabel;
	CLabel* epilogueLabel;
};