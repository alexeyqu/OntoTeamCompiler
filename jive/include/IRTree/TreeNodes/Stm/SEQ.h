#include "../IStm.h"
#include "IRTree/IIRTreeVisitor.h"

class SEQ : public IStm
{
public:
	SEQ( IStm* _left, IStm* _right ) : left( _left ), right( _right ) {};
	IStm* GetLeft() const;
	IStm* GetRight() const;
	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IStm* Build( CExpList* kids );

private:
	IStm* left;
	IStm* right;
};