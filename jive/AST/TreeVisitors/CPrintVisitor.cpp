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
    long exprId = generateId(expression);

    file << exprId << ";\n";
    file << exprId << "[label = \"BinExp\"];\n";

    file << exprId << "->";
    expression->leftOperand->Accept(this);

    file << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TOperation::ADD:
            file << operationId << ";\n";
            file << operationId << "[label= \"+\" ];\n";
            break;

        case enums::TOperation::SUB:
            file << operationId << ";\n";
            file << operationId << "[label= \"-\" ];\n";
            break;

        case enums::TOperation::MUL:
            file << operationId << ";\n";
            file << operationId << "[label= \"*\" ];\n";
            break;

        case enums::TOperation::DIV:
            file << operationId << ";\n";
            file << operationId << "[label= \"/\" ];\n";
            break;
    }

    file << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CNumberExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"NumExp\"];\n";

    long numberId = generateId(&expression->number);
    file << exprId << "->" << numberId << ";\n";
    file << numberId << "[label=" << expression->number << "];\n";
}

std::size_t  CPrintVisitor::generateId( void *entity )
{
    if( entity == nullptr )
    {
        assert(!"Error in CPrintVisitor::generateId : nullptr");
    }

    return reinterpret_cast<long>( entity );
}