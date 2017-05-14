#include "../IStm.h"
#include "../IExp.h"
#include "IRTree/Temp/CLabelList.h"
#include "IRTree/IIRTreeVisitor.h"

class JUMP : public IStm
{
public:
	JUMP( IExp* _exp, CLabelList* _targets ) : exp( _exp ), targets( _targets ) {};
	JUMP( CLabel* label );
	IExp* GetExp() const;
	CLabelList* GetTargets() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	IExp* exp;
	CLabelList* targets;
};