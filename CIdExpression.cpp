class CIdExpression : public IExpression 
{
	std:string id;
   	int Value;
 
   	virtual void Accept( IVisitor* v ) override;
};