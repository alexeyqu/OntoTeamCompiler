#include "../IStm.h"
#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class EXP : public IStm
{
public:
	EXP( IExp* _exp )	: exp( _exp ) {};
	IExp* GetExp() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	IExp* exp;
};