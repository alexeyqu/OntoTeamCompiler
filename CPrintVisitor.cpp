class CPrintVisitor : public IVisitor
{
    void Visit( CNumberExpression* expr )
    {
        cout << expr->Value;
    }

    void Visit( CBinaryExpression* expr )
    {
        exp->LeftOperand->Accept( this );
        
        cout << exp->Operation;

        exp->RightOperand->Accept( this );
    }
}
