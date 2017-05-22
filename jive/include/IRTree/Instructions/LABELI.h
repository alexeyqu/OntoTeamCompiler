#pragma once

#include "../IInstruction.h"

class LABELI : public IInstruction {
	public:
		LABELI( const std::string& asmCode, CLabel* _label ) :
			label( _label ) {
			asmCodeTemplate = asmCode;
		};
		CTempList* UsedVariables() const {
			return nullptr;
		}
		CTempList* DefinedVariables() const {
			return nullptr;
		}
		CLabelList* JumpTargets() const {
			return new CLabelList( label );
		}
		
	private:
		CLabel* label;
	};