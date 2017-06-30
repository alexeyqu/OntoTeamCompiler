#pragma once

#include "CInFrame.h"
#include "CInReg.h"
#include "CSymbol.h"
#include "CSymbolStorage.h"
#include "CTempList.h"
#include "CLabel.h"

namespace IRT
{

using ST::CSymbol;

class CX86JiveFrame
{
public:
    CX86JiveFrame( CSymbol *_symbol );

	void addParam( CSymbol *_symbol ) { params.insertObject( _symbol, new CInReg( new CTemp() ) ); paramsCount++; }
	void addLocal( CSymbol *_symbol ) { locals.insertObject( _symbol, new CInFrame( stackOffset, basePointer ) ); stackOffset += wordSize; }

	int getParamsCount() const { return paramsCount; }
	IAccess *getAccess( CSymbol *_symbol ) const;

	static int getWordSize() { return wordSize; }

	CTemp *getBasePointer() const { return basePointer; }
	CTemp *getStackPointer() const { return stackPointer; }
	CTemp *getReturnPointer() const { return returnPointer; }

	CLabel *getPrologueLabel() const { return prologueLabel; }
	CLabel *getBodyLabel() const { return bodyLabel; }
	CLabel *getEpilogueLabel() const { return epilogueLabel; }

	CTempList *getDefaultRegs() const;

private:
    CSymbol *symbol;

	int paramsCount;
	int stackOffset;

	CSymbolStorage<IAccess *> params;
	CSymbolStorage<IAccess *> locals;

	CTemp *basePointer;
	CTemp *stackPointer;
	CTemp *returnPointer;

	CTempList *defaultRegs;

	CLabel *prologueLabel;
	CLabel *bodyLabel;
	CLabel *epilogueLabel;

	static const int wordSize = 4;

};

}