/*#include "IVisitorTarget.cpp"
#include "IExpression.cpp"
#include "CNumberExpression.cpp"
#include "CBinaryExpression.cpp"
#include "IVisitor.cpp"
#include "CPrintVisitor.cpp"
*/
#include <stdlib.h>
#include <iostream>

using std::cout;

enum TOperationType
{
    OT_Plus = 1,
    OT_Minus = 2,
};

class IVisitor;

class IVisitorTarget
{
public:
   	virtual void Accept( IVisitor* ) = 0;
};

class IExpression : public IVisitorTarget {
};

class CNumberExpression : public IExpression
{
public:
   	int Value;

   	virtual void Accept( IVisitor* v );
};

class CBinaryExpression : public IExpression
{
public:
   	IExpression* LeftOperand;
   	IExpression* RightOperand;

   	TOperationType Operation;

    virtual void Accept( IVisitor* v );
};


class IVisitor
{
public:
	virtual void Visit( CBinaryExpression* ) = 0;
   	virtual void Visit( CNumberExpression* ) = 0;
};

void CNumberExpression::Accept( IVisitor* v )
{
    v->Visit(this);
}

void CBinaryExpression::Accept( IVisitor* v )
{
    v->Visit(this);
}

class CPrintVisitor : public IVisitor
{
public:
    void Visit( CNumberExpression* expr )
    {
        cout << expr->Value;
    }

    void Visit( CBinaryExpression* expr )
    {
        expr->LeftOperand->Accept( this );

        cout << expr->Operation;

        expr->RightOperand->Accept( this );
    }
};

int main()
{
    CNumberExpression three;

    three.Value = 3;

    CNumberExpression five;

    five.Value = 5;

    CBinaryExpression plus;

    plus.LeftOperand = &three;
    plus.RightOperand = &five;
    plus.Operation = OT_Plus;

    CPrintVisitor myPrintVisitor;

    myPrintVisitor.Visit (&plus);

    return 0;
}
