#include "CPrintVisitor.h"

void CPrintVisitor::Start(IVisitorTarget* vertex, const std::string& filename, const std::string& graphname) {
        file.open(filename);
        file << "digraph " << graphname << " {\n";
        vertex->Accept(this);
        file << "\n}";
        file.close();
}

void CPrintVisitor::Visit(CBinaryExpression* expression) {
    switch(expression->operation) {
        case 'OT_Plus':
            file << "+" << "->";
        case 'OT_Minus':
            file << "-" << "->";
    }
    expression->leftOperand->Accept(this);

    switch(expression->operation) {
        case 'OT_Plus':
            file << ";\n" << "+" << "->";
        case 'OT_Minus':
            file << ";\n" << "-" << "->";
    }
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit(CCompoundStatement* statement) {
    file << " compound " << "->";
    statement->leftStatement->Accept(this);
    file << ";\n compound " << "->";
    statement->rightStatement>Accept(this);
}

void CPrintVisitor::Visit(CIdExpression* expression) {
    file << expression->id;
}

void CPrintVisitor::Visit(CNumberExpression* expression) {
    file << expression->value;
}

void CPrintVisitor::Visit(CAssignStatement* statement) {
    file << "=" << "-";
    statement->id->Accept(this);
    file << "=" << "->";
    statement->expression->Accept(this);
}

void CPrintVisitor::Visit(CLastExpessionList* expressionList) {
    file << "last expression list" << "->";
    expressionList->expression->Accept(this);
}

void CPrintVisitor::Visit(CPrintStatement* printStatement) {
    file << "print statement" << "->";
    printStatement->statement->Accept(this);
}
