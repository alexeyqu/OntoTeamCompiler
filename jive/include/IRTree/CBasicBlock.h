#pragma once

#include "IRTree/TreeNodes/IStm.h"
#include "IRTree/TreeNodes/Nodes.h"
#include <vector>

class CBasicBlock {
public:
	CBasicBlock() : Label( nullptr ), Jump( nullptr ) {};

	void Clear();
	void AddStm( IStm* stm );
	JUMP* GetJump() const;
	CJUMP* GetCjump() const;

	LABEL* Label; 
	std::vector<IStm*> FlowStms;
	IStm* Jump;
};
