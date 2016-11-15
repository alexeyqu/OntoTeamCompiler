#include "CPrintVisitor.h"

// TODO: fix .dot labels

void CPrintVisitor::Start( IVisitorTarget *vertex, std::string graphname ) {
    std::string filename = graphname + ".dot";
    file.open(filename.c_str());

    file << "digraph " << graphname << " {\n";

    vertex->Accept(this);

    file << "\n}";

    file.close();
}

void CPrintVisitor::Visit( CProgram *program ) {
    program->expression->Accept(this);
}

void CPrintVisitor::Visit( CBinaryExpression *expression ) {

    file << reinterpret_cast<long>(expression) << ";\n";
    file << reinterpret_cast<long>(expression) << "[label = \"BinExp\"];\n";

    file << reinterpret_cast<long>(expression) << "->";
    expression->leftOperand->Accept(this);

    file << reinterpret_cast<long>(expression) << "->";
    switch(expression->operation) {
        case enums::TOperation::ADD:
            file << reinterpret_cast<long>(&expression->operation) << ";\n";
            file << reinterpret_cast<long>(&expression->operation) << "[label= \"+\" ];\n";
            break;

        case enums::TOperation::SUB:
            file << reinterpret_cast<long>(&expression->operation) << ";\n";
            file << reinterpret_cast<long>(&expression->operation) << "[label= \"-\" ];\n";
            break;

        case enums::TOperation::MUL:
            file << reinterpret_cast<long>(&expression->operation) << ";\n";
            file << reinterpret_cast<long>(&expression->operation) << "[label= \"*\" ];\n";
            break;

        case enums::TOperation::DIV:
            file << reinterpret_cast<long>(&expression->operation) << ";\n";
            file << reinterpret_cast<long>(&expression->operation) << "[label= \"/\" ];\n";
            break;
    }

    file << reinterpret_cast<long>(expression) << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CNumberExpression *expression ) {
    file << reinterpret_cast<long>(expression) << "\n";
    file << reinterpret_cast<long>(expression) << "[label = \"NumExp\"];\n";
    file << reinterpret_cast<long>(expression) << "->" << reinterpret_cast<long>(&expression->number) << ";\n";
    file << reinterpret_cast<long>(&expression->number) << "[label=" << expression->number << "];\n";
}
