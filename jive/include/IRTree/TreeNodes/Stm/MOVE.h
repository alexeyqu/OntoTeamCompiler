#include "../IStm.h"
#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class MOVE : public IStm
{
public:
	MOVE( IExp* _dest, IExp* _src ) : dest( _dest ), src( _src ) {};
	IExp* GetDst() const;
	IExp* GetSrc() const;
	void Accept( IIRTreeVisitor *visitor );
private:
	IExp* dest;
	IExp* src;
};