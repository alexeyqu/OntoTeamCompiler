class CNumberExpression : public IExpression 
{
   	int Value;
 
   	virtual void Accept( IVisitor* v ) override;
};
