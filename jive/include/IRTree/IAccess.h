#pragma once

#include "TreeNodes/IExp.h"
#include "IRTree/Temp/CTemp.h"

class IAccess {
	public:
		virtual ~IAccess() {}
		virtual IExp* GetExp() const = 0;
};