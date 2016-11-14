#include "CPrintVisitor.h"

// TODO: fix .dot labels

void CPrintVisitor::Start(IVisitorTarget* vertex, std::string filename, std::string graphname) {
    file.open(filename.c_str());
    file << "digraph " << graphname << " {\n";

    vertex->Accept(this);

    file << "\n}";
    file.close();
}

void CPrintVisitor::Visit(CProgram* program) {
    program->expr->Accept(this);
}

void CPrintVisitor::Visit(CBinaryExpression* expression) {

    file << reinterpret_cast<long>(expression) << ";\n";
    file << reinterpret_cast<long>(expression) << "[label = \"BinExp\"];\n";

    file << reinterpret_cast<long>(expression) << "->";
    expression->leftOperand->Accept(this);

    file << reinterpret_cast<long>(expression) << "->";
    switch(expression->operation) {
        case CBinaryExpression::OT_Plus:
            file << static_cast<int>(expression->operation) << ";\n";
            file << static_cast<int>(expression->operation) << "[label=Plus];\n";
            break;

        case CBinaryExpression::OT_Minus:
            file << static_cast<int>(expression->operation) << ";\n";
            file << static_cast<int>(expression->operation) << "[label=Minus];\n";
            break;
    }

    file << reinterpret_cast<long>(expression) << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit(CNumberExpression* expression) {
    file << reinterpret_cast<long>(expression) << "\n";
    file << reinterpret_cast<long>(expression) << "[label = \"NumExp\"];\n";
    file << reinterpret_cast<long>(expression) << "->" << expression->number << ";\n";
}
