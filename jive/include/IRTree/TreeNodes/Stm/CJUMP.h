#include "../IStm.h"
#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"
#include "IRTree/Temp/CLabel.h"
#include "jive.h"

class CJUMP : public IStm
{
public:
	CJUMP( enums::TCJump _op, IExp* _left, IExp* _right, 
		CLabel* _ifTrue, CLabel* _ifFalse )
		: op( _op ), left( _left ), right( _right ), 
		ifTrue( _ifTrue ), ifFalse( _ifFalse ) {};
	enums::TCJump GetOp() const;
	enums::TCJump GetNotOp() const;
	IExp* GetLeft() const;
	IExp* GetRight() const;
	CLabel* GetIfTrue() const;
	CLabel* GetIfFalse() const;
	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IStm* Build( CExpList* kids );

private:
	enums::TCJump op;
	IExp* left;
	IExp* right;
	CLabel* ifTrue;
	CLabel* ifFalse;
};