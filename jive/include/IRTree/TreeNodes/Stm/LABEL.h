#include "../IStm.h"
#include "IRTree/IIRTreeVisitor.h"
#include "IRTree/Temp/CLabel.h"

class LABEL : public IStm
{
public:
	LABEL( CLabel* _label ) : label( _label ) {};
	CLabel* GetLabel() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	CLabel* label;
};