/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_AUTO_JIVE_TAB_H_INCLUDED
# define YY_YY_AUTO_JIVE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/jive.y" /* yacc.c:1909  */

	#include <cstdio>
	#include <cstring>
	#include "CProgram.h"

	#define YYERROR_VERBOSE 1 

#line 52 "auto/jive.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    ID = 259,
    STRING = 260,
    VOID = 261,
    INT = 262,
    BOOL = 263,
    CLASS = 264,
    PUBLIC = 265,
    STATIC = 266,
    EXTENDS = 267,
    THIS = 268,
    MAIN = 269,
    IF = 270,
    ELSE = 271,
    WHILE = 272,
    FOR = 273,
    RETURN = 274,
    NIL = 275,
    LPAREN = 276,
    RPAREN = 277,
    LBRACE = 278,
    RBRACE = 279,
    LBRACKET = 280,
    RBRACKET = 281,
    ASSIGN = 282,
    EQU = 283,
    ADD = 284,
    SUB = 285,
    MUL = 286,
    DIV = 287,
    MOD = 288,
    LESS = 289,
    GREATER = 290,
    TRUE = 291,
    FALSE = 292,
    AND = 293,
    OR = 294,
    NOT = 295,
    COMMA = 296,
    DOT = 297,
    SEMI = 298,
    AMPERSAND = 299,
    PRINT = 300,
    ERROR = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "src/jive.y" /* yacc.c:1909  */

	char *string;
	CProgram *Program;
	IVisitorTarget *Tmp;
	CType* Type;
	CField* VarDeclaration;
	CIdExpression *Identifier;

	IEntity *Entity;
	IStatement *Statement;
	IExpression *Expression;

#line 124 "auto/jive.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (CProgram **program);

#endif /* !YY_YY_AUTO_JIVE_TAB_H_INCLUDED  */
