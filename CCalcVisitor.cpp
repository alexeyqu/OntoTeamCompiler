#include "CCalcVisitor.h"

CCalcVisitor::CCalcVisitor() {
	head = new VariablesTable("", 0, 0, 0, 0);
}

void CCalcVisitor::Start( IVisitorTarget* target ) {
	target->Accept(this);
}

void CCalcVisitor::Visit( CCompoundStatement* stmt ) {
	stmt->leftStatement->Accept(this);
	stmt->rightStatement->Accept(this);
}

void CCalcVisitor::Visit( CIdExpression* expr ) {
	VariablesTable* current = head;
	while( current->name != expr->id ) {
		current = current->next;
	}
	head = new VariablesTable(expr->id, current->value, expr, head, head->tail);
}

void CCalcVisitor::Visit( CBinaryExpression* expr ) {
	expr->leftOperand->Accept(this);
	expr->rightOperand->Accept(this);
	int result;
	int leftResult;
	int rightResult;
	VariablesTable* current = head;
	while( current->node != expr->leftOperand ) {
		current = current->next;
	}
	current = head;
	leftResult = current->value;
	while( current->node != expr->leftOperand ) {
		current = current->next;
	}
	rightResult = current->value;
	switch( expr->operation ) {
		case (CBinaryExpression::OT_Plus):
			result = leftResult + rightResult;
			break;
		case (CBinaryExpression::OT_Minus):
			result = leftResult - rightResult;
	}
	head = new VariablesTable("", result, expr, head, head->tail);
}

void CCalcVisitor::Visit( CNumberExpression* expr ) {
	head = new VariablesTable("", expr->value, expr, head, head->tail);
}

void CCalcVisitor::Visit( CAssignStatement* stmt ) {
	VariablesTable* current = head;
	while( current->node != stmt->expression ) {
		current = current->next;
	}
	head = new VariablesTable(stmt->id, current->value, stmt, head, head->tail);
}

void CCalcVisitor::Visit( CPrintStatement* stmt ) {
	stmt->expression->Accept(this);
}

void CCalcVisitor::Visit( CLastExpressionList* expr ) {
	expr->expression->Accept(this);
	VariablesTable* current = head;
	while( current->node != expr->expression ) {
		current = current->next;
	}
	head = new VariablesTable(current->name, current->value, expr, head, head->tail);
}

CCalcVisitor::~CCalcVisitor() {
	VariablesTable* current = head;
	while (current != current->tail) {
		VariablesTable* next = current->next;
		delete current;
		current = next;
	}
	delete current;
}