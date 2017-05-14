#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class MEM : public IExp
{
public:
	MEM( IExp* _exp )	: exp( _exp ) {};
	IExp* GetExp() const;
	void Accept( IIRTreeVisitor *visitor );
		
private:
	IExp* exp;
};
