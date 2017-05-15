#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class CALL : public IExp
{
public:
	CALL( IExp* _func, CExpList* _args ) : func( _func ), args( _args )	{};
	IExp* GetFunc() const;
	CExpList* GetArgs() const;
	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IExp* Build( CExpList* kids );

private:
	IExp* func;
	CExpList* args;
};