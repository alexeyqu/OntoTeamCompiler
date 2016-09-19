class CCalculateVisitor
{
    int Visit( CNumberExpression* expr ) {
        return expr->Value;
    }

    int Visit( CBinaryExpression* expr ) {
        exp->LeftOperand->Accept(this);
        cout << exp->Operation;
        exp->RightOperand->Accept(this);
    }
};
