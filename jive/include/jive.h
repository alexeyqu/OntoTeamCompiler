#pragma once

#include <vector>
#include <string>

namespace jive
{
enum TArithmeticOperation { ADD, SUB, MUL, DIV, MOD };
enum TBooleanOperation { AND, OR, LESS, GREATER };
enum TType { INTEGER, INTEGERARRAY, BOOLEAN, STRING, STRINGARRAY, CLASS, IDENTIFIER, UNKNOWNTYPE, USERTYPE, VOID };

static std::vector<std::string> keywords = { "class", "public", "private", "static", "void", "extends",   
	"if", "while", "return",
	"true", "false", "this", "new" };
}