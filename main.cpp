#include "CAssignStatement.h"
#include "CBinaryExpression.h"
#include "CCompoundStatement.h"
#include "CLastExpressionList.h"
#include "CNumberExpression.h"
#include "CPrintStatement.h"
#include "CPrintVisitor.h"
#include "CIdExpression.h"

int main() {
  CNumberExpression five(5);
  CNumberExpression three(3);
  CBinaryExpression sum(&five, CBinaryExpression::OT_Plus, &three);
  CAssignStatement assign("a", &sum);
  CIdExpression id(assign.id);
  CLastExpressionList exList(&id);
  CPrintStatement print(&exList);
  CCompoundStatement comp(&assign, &print);

  CPrintVisitor visitor;
  visitor.Start(&comp, "g1.dot", "g1");

  return 0;
}
