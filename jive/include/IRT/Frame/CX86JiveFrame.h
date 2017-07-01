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
	void addField( CSymbol *_symbol ) { fields.insertObject( _symbol, new CInFrame( thisOffset, thisPointer ) ); thisPointer += wordSize; }

	int getParamsCount() const { return paramsCount; }
	IAccess *getAccess( CSymbol *_symbol ) const;

	static int getWordSize() { return wordSize; }

	CTemp *getBasePointer() const { return basePointer; }
	CTemp *getThisPointer() const { return thisPointer; }
	CTemp *getReturnAddress() const { return returnAddress; }

	CLabel *getPrologueLabel() const { return prologueLabel; }
	CLabel *getBodyLabel() const { return bodyLabel; }
	CLabel *getEpilogueLabel() const { return epilogueLabel; }

	CTempList *getDefaultRegs() const;

private:
    CSymbol *symbol;

	int paramsCount;
	int stackOffset;
	int thisOffset;

	CSymbolStorage<IAccess *> params;
	CSymbolStorage<IAccess *> locals;
	CSymbolStorage<IAccess *> fields;

	CTemp *basePointer;
	CTemp *thisPointer;
	CTemp *returnAddress;

	CTempList *defaultRegs;

	CLabel *prologueLabel;
	CLabel *bodyLabel;
	CLabel *epilogueLabel;

	static const int wordSize = 4;

};

}