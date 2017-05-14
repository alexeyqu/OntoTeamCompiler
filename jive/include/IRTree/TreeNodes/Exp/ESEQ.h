#include "../IExp.h"
#include "../IStm.h"
#include "IRTree/IIRTreeVisitor.h"

class ESEQ : public IExp
{
public:
	ESEQ( IStm* _stm, IExp* _exp ) : stm( _stm ), exp( _exp ) {};
	IStm* GetStm() const;
	IExp* GetExp() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	IStm* stm;
	IExp* exp;
};