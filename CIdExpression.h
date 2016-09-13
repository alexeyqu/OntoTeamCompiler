#include "IExpression.h"
#include <string>

class CIdExpression : public IExpression 
{
	std::string id;

public:
	
	CIdExpression( const std::string& id ); 
   	virtual void Accept( IVisitor* v ) override;
};