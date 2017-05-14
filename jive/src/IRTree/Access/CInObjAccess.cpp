#include "IRTree/Access/CInObjAccess.h"
#include "IRTree/TreeNodes/Nodes.h"
#include "IRTree/CFrame.h"

IExp* CInObjAccess::GetExp() const {
	return new MEM(	new BINOP( enums::BO_ADD,
		new TEMP( thisPointer ), new CONST( offset ) )	);
}