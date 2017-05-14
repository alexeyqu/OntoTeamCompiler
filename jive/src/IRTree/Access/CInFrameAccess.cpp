#include "IRTree/Access/CInFrameAccess.h"
#include "IRTree/TreeNodes/Nodes.h"
#include "IRTree/CFrame.h"

IExp* CInFrameAccess::GetExp() const {
	return new MEM(	new BINOP( enums::BO_ADD,
		new TEMP( framePointer ), new CONST( offset ) )	);
}