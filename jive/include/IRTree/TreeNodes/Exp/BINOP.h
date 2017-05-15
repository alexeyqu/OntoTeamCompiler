#pragma once

#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class BINOP : public IExp
{
public:
	BINOP( enums::TBinop _op, IExp* _left, IExp* _right )
		: op( _op ), left( _left ), right( _right ) {};
	enums::TBinop GetOp() const;
	IExp* GetLeft() const;
	IExp* GetRight() const;
	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IExp* Build( CExpList* kids );

private:
	enums::TBinop op;
	IExp* left;
	IExp* right;
};