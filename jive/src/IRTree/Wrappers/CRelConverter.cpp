#include "IRTree/Wrappers/CRelConverter.h"

IStm* CRelConverter::ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const {
	return new CJUMP( op, left, right, ifTrue, ifFalse );
}