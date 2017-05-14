#pragma once

namespace enums {
	enum TArithmeticOperation { ADD, SUB, MUL, DIV, MOD };
	enum TBooleanOperation { AND, OR, LESS, GREATER };
	enum TType { INTEGER, INTEGERARRAY, BOOLEAN, STRING, STRINGARRAY, CLASS, IDENTIFIER, UNKNOWNTYPE, USERTYPE, VOID };
	enum TBinop { BO_ADD, BO_SUB, BO_MUL, BO_DIV, BO_AND, BO_OR };
	enum TCJump { EQ, NE, LT, GT, LE, GE };
}