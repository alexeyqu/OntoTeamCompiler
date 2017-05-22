#pragma once

#include "../IInstruction.h"

class MOVEI : public IInstruction {
public:
	MOVEI( const std::string& asmCode, CTemp* _dst, CTemp* _src ) :
		dst( _dst ), src( _src ) {
		asmCodeTemplate = asmCode;
	}
	CTempList* UsedVariables() const {
		return new CTempList( src );
	}
	CTempList* DefinedVariables() const {
		return new CTempList( dst );
	}
	CLabelList* JumpTargets() const {
		return nullptr;
	}

private:
	CTemp* dst;
	CTemp* src;
};
