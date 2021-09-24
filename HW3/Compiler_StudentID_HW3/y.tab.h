/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VAR = 258,
    INT = 259,
    FLOAT = 260,
    BOOL = 261,
    STRING = 262,
    INC = 263,
    DEC = 264,
    GEQ = 265,
    LEQ = 266,
    EQL = 267,
    NEQ = 268,
    ADD_ASSIGN = 269,
    SUB_ASSIGN = 270,
    MUL_ASSIGN = 271,
    QUO_ASSIGN = 272,
    REM_ASSIGN = 273,
    OR = 274,
    AND = 275,
    NEWLINE = 276,
    PRINT = 277,
    PRINTLN = 278,
    IF = 279,
    ELSE = 280,
    FOR = 281,
    WHILE = 282,
    TRUE = 283,
    FALSE = 284,
    INT_LIT = 285,
    FLOAT_LIT = 286,
    STRING_LIT = 287,
    ID = 288
  };
#endif
/* Tokens.  */
#define VAR 258
#define INT 259
#define FLOAT 260
#define BOOL 261
#define STRING 262
#define INC 263
#define DEC 264
#define GEQ 265
#define LEQ 266
#define EQL 267
#define NEQ 268
#define ADD_ASSIGN 269
#define SUB_ASSIGN 270
#define MUL_ASSIGN 271
#define QUO_ASSIGN 272
#define REM_ASSIGN 273
#define OR 274
#define AND 275
#define NEWLINE 276
#define PRINT 277
#define PRINTLN 278
#define IF 279
#define ELSE 280
#define FOR 281
#define WHILE 282
#define TRUE 283
#define FALSE 284
#define INT_LIT 285
#define FLOAT_LIT 286
#define STRING_LIT 287
#define ID 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 130 "compiler_hw3.y"

    int i_val;
    float f_val;
    char *s_val;
    /* ... */

#line 130 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
