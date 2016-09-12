class IVisitor 
{
	virtual void Visit( CBinaryExpression* ) = 0;
   	virtual void Visit( CNumberExpression* ) = 0;
}
