#pragma once

#include "../IInstruction.h"

class OPER : public IInstruction {
public:
	OPER( const std::string& asmCode, 
		CTempList* dst, CTempList* src, CLabelList* jumps ) :
		usedVars( src ), definedVars( dst ), jumpTargets( jumps ) {
		asmCodeTemplate = asmCode;
	};

	OPER( const std::string& asmCode, CTempList* dst, CTempList* src ) :
		usedVars( src ), definedVars( dst ), jumpTargets( nullptr ) {
		asmCodeTemplate = asmCode;
	};
	CTempList* UsedVariables() const {
		return usedVars;
	}
	CTempList* DefinedVariables() const {
		return definedVars;
	}
	CLabelList* JumpTargets() const {
		return jumpTargets;	
	}

private:
	CTempList* usedVars;
	CTempList* definedVars;
	CLabelList* jumpTargets;		
};