#include "CPrintVisitor.h"

void CPrintVisitor::Start(IVisitorTarget* vertex, std::string filename, std::string graphname) {
        file.open(filename.c_str());
        file << "digraph " << graphname << " {\n";
        vertex->Accept(this);
        file << "\n}";
        file.close();
}

void CPrintVisitor::Visit(CBinaryExpression* expression) {
    file << "Operation" << "->";
    expression->leftOperand->Accept(this);
    file << "Operation" << "->";
    switch(expression->operation) {
        case CBinaryExpression::OT_Plus:
            file << "Plus" << ";\n";
            break;
        case CBinaryExpression::OT_Minus:
            file << "Minus" << ";\n";
            break;
    }
    file << "Operation" << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit(CCompoundStatement* statement) {
    file << "Compound" << "->";
    statement->leftStatement->Accept(this);
    file << "Compound" << "->";
    statement->rightStatement->Accept(this);
}

void CPrintVisitor::Visit(CIdExpression* expression) {
    file << "ExpId" << "->" << expression->id << ";";
}

void CPrintVisitor::Visit(CNumberExpression* expression) {
    file << "NumExp" << "->" << expression->value << ";\n";
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
    file << "Assign" << "->" << statement->id << ";\n";
    file << "Assign" << "->";
    statement->expression->Accept(this);
}

void CPrintVisitor::Visit(CLastExpressionList* expressionList) {
    file << "Last expression list" << "->";
    expressionList->expression->Accept(this);
}

void CPrintVisitor::Visit(CPrintStatement* printStatement) {
    file << "Print statement" << "->";
    printStatement->expression->Accept(this);
}