#include "CAssignStatement.h"
#include "CBinaryExpression.h"
#include "CCompoundStatement.h"
#include "CLastExpressionList.h"
#include "CNumberExpression.h"
#include "CPrintStatement.h"
#include "CPrintVisitor.h"
#include "CCalcVisitor.h"
#include "CIdExpression.h"
#include <iostream>

int main() {
  CNumberExpression five(5);
  CNumberExpression three(3);
  CBinaryExpression sum(&five, CBinaryExpression::OT_Plus, &three);
  CAssignStatement assign("a", &sum);
  CIdExpression id(assign.id);
  CLastExpressionList exList(&id);
  CPrintStatement print(&exList);
  CCompoundStatement comp(&assign, &print);

  CPrintVisitor printVisitor;
  printVisitor.Start(&comp, "graph1.dot", "graph1");
  CCalcVisitor calcVisitor;
  calcVisitor.Start(&comp);
  std::cout << calcVisitor.head->value << std::endl;

  return 0;
}
