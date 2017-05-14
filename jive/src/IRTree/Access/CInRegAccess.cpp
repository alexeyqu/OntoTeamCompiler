#include "IRTree/Access/CInRegAccess.h"
#include "IRTree/TreeNodes/Exp/TEMP.h"
#include "IRTree/CFrame.h"

IExp* CInRegAccess::GetExp() const {
	return new TEMP( registerId );
}