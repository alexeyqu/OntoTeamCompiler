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
    program->statement->Accept(this);
}

void CPrintVisitor::Visit( CAssignStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"=\"];\n";

    file << stmId << "->";
    statement->leftOperand->Accept(this);

    file << stmId << "->";
    statement->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CIdExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"IdExp\"];\n";

    long nameId = generateId(&expression->name);
    file << exprId << "->" << nameId << ";\n";
    file << nameId << "[label = \"" << expression->name << "\", xlabel = \"" << expression->address << "\"];\n";
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
            file << operationId << "[label = \"+\" ];\n";
            break;

        case enums::TOperation::SUB:
            file << operationId << ";\n";
            file << operationId << "[label = \"-\" ];\n";
            break;

        case enums::TOperation::MUL:
            file << operationId << ";\n";
            file << operationId << "[label = \"*\" ];\n";
            break;

        case enums::TOperation::DIV:
            file << operationId << ";\n";
            file << operationId << "[label = \"/\" ];\n";
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
    file << numberId << "[label = \"" << expression->number << "\"];\n";
}

std::size_t  CPrintVisitor::generateId( void *entity )
{
    if( entity == nullptr )
    {
        assert(!"Error in CPrintVisitor::generateId : nullptr");
    }

    return reinterpret_cast<long>( entity ); // TODO move to std::hash
}