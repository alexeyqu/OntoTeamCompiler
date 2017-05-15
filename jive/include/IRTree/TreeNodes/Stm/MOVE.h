#include "../IStm.h"
#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class MOVE : public IStm
{
public:
	MOVE( IExp* _dest, IExp* _src ) : dest( _dest ), src( _src ) {};
	IExp* GetDest() const;
	IExp* GetSrc() const;
	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IStm* Build( CExpList* kids );

private:
	IExp* dest;
	IExp* src;
};