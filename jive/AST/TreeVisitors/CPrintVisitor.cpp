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

void CPrintVisitor::Visit( CCompoundStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"CompoundStm\"];\n";

    file << stmId << "->";
    statement->leftStatement->Accept(this);

    file << stmId << "->";
    statement->rightStatement->Accept(this);
}

void CPrintVisitor::Visit( CAssignStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"AssignStm\"];\n";

    file << stmId << "->";
    statement->leftOperand->Accept(this);

    file << stmId << "->";
    statement->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CPrintStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"PrintStm\"];\n";

    file << stmId << "->";
    statement->operand->Accept(this);
}

void CPrintVisitor::Visit( CIfStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"IfStm\"];\n";

    file << stmId << "->";
    statement->expression->Accept(this);

    file << stmId << "->";
    statement->thenStatement->Accept(this);

    file << stmId << "->";
    statement->elseStatement->Accept(this);
}

void CPrintVisitor::Visit( CWhileStatement *statement ) {
    long stmId = generateId(statement);

    file << stmId << ";\n";
    file << stmId << "[label = \"WhileStm\"];\n";

    file << stmId << "->";
    statement->expression->Accept(this);

    file << stmId << "->";
    statement->loopStatement->Accept(this);
}

void CPrintVisitor::Visit( CIdExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"IdExp\"];\n";

    long nameId = generateId(&expression->name);
    file << exprId << "->" << nameId << ";\n";
    file << nameId << "[label = \"" << expression->name << "\"];\n";
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
        case enums::TArithmeticOperation::ADD:
            file << operationId << ";\n";
            file << operationId << "[label = \"+\" ];\n";
            break;

        case enums::TArithmeticOperation::SUB:
            file << operationId << ";\n";
            file << operationId << "[label = \"-\" ];\n";
            break;

        case enums::TArithmeticOperation::MUL:
            file << operationId << ";\n";
            file << operationId << "[label = \"*\" ];\n";
            break;

        case enums::TArithmeticOperation::DIV:
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

void CPrintVisitor::Visit( CBinaryBooleanExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << ";\n";
    file << exprId << "[label = \"BinBoolExp\"];\n";

    file << exprId << "->";
    expression->leftOperand->Accept(this);

    file << exprId << "->";
    long operationId = generateId(&expression->operation);
    switch(expression->operation) {
        case enums::TBooleanOperation::AND:
            file << operationId << ";\n";
            file << operationId << "[label = \"AND\" ];\n";
            break;

        case enums::TBooleanOperation::OR:
            file << operationId << ";\n";
            file << operationId << "[label = \"OR\" ];\n";
            break;

        case enums::TBooleanOperation::LESS:
            file << operationId << ";\n";
            file << operationId << "[label = \"<\" ];\n";
            break;

        case enums::TBooleanOperation::GREATER:
            file << operationId << ";\n";
            file << operationId << "[label = \">\" ];\n";
            break;
    }

    file << exprId << "->";
    expression->rightOperand->Accept(this);
}

void CPrintVisitor::Visit( CBooleanExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"BoolExp\"];\n";

    long valueId = generateId(&expression->value);
    file << exprId << "->" << valueId << ";\n";
    file << valueId << "[label = \"" << expression->value << "\"];\n";
}

void CPrintVisitor::Visit( CThisExpression *expression ) {
    long exprId = generateId(expression);

    file << exprId << "\n";
    file << exprId << "[label = \"ThisExp\"];\n";

    long addressId = generateId(&expression->address);
    file << exprId << "->" << addressId << ";\n";
    file << addressId << "[label = \"" << expression->address << "\"];\n";
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

std::size_t  CPrintVisitor::generateId( void *entity )
{
    if( entity == nullptr )
    {
        assert(!"Error in CPrintVisitor::generateId : nullptr");
    }

    return reinterpret_cast<long>( entity ); // TODO move to std::hash
}