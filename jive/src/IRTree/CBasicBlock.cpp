#include "IRTree/CBasicBlock.h"

void CBasicBlock::Clear() {
	Label = nullptr;
	Jump = nullptr;
	FlowStms.clear();
}

void CBasicBlock::AddStm( IStm* stm ) {
	FlowStms.push_back( stm );
}

JUMP* CBasicBlock::GetJump() const { 
	return dynamic_cast<JUMP*>( Jump ); 
}

CJUMP* CBasicBlock::GetCjump() const { 
	return dynamic_cast<CJUMP*>( Jump ); 
}