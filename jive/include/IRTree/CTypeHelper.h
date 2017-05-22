#pragma once

#include "TreeNodes/Nodes.h"

class CTypeHelper {
public:
	static SEQ* IsSEQ( IStm* stm ) { return dynamic_cast< SEQ* >( stm ); }
	static MOVE* IsMOVE( IStm* stm ) { return dynamic_cast< MOVE* >( stm ); }
	static EXP* IsEXP( IStm* stm ) { return dynamic_cast< EXP* >( stm ); }
	static JUMP* IsJUMP( IStm* stm ) { return dynamic_cast< JUMP* >( stm ); }
	static CJUMP* IsCJUMP( IStm* stm ) { return dynamic_cast< CJUMP* >( stm ); }
	static LABEL* IsLABEL( IStm* stm ) { return dynamic_cast< LABEL* >( stm ); }

	static MEM* IsMEM( IExp* exp ) { return dynamic_cast<MEM*>( exp ); }
	static BINOP* IsBINOP( IExp* exp ) { return dynamic_cast<BINOP*>( exp ); }
	static CONST* IsCONST( IExp* exp ) { return dynamic_cast<CONST*>( exp ); }
	static CALL* IsCALL( IExp* exp ) { return dynamic_cast<CALL*>( exp ); }
	static NAME* IsNAME( IExp* exp ) { return dynamic_cast<NAME*>( exp ); }
	static TEMP* IsTEMP( IExp* exp ) { return dynamic_cast<TEMP*>( exp ); }
};
