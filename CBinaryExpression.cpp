class CBinaryExpression : public IExpression {
   	IExpression* LeftOperand;
   	IExpression* RightOperand;
 
   	enum TOperationType {
         		OT_Plus,
         		OT_Minus,
   	};
   	TOperationType Operation;
 
   	virtual void Accept( IVisitor* v ) override;
};