/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INTEGER = 258,                 /* INTEGER  */
    FLOAT = 259,                   /* FLOAT  */
    STRING = 260,                  /* STRING  */
    VOID = 261,                    /* VOID  */
    BOOL = 262,                    /* BOOL  */
    READ = 263,                    /* READ  */
    PRINT = 264,                   /* PRINT  */
    PLUS = 265,                    /* PLUS  */
    MINUS = 266,                   /* MINUS  */
    MULT = 267,                    /* MULT  */
    DIV = 268,                     /* DIV  */
    LEFT_ROUND_BRACKET = 269,      /* LEFT_ROUND_BRACKET  */
    RIGHT_ROUND_BRACKET = 270,     /* RIGHT_ROUND_BRACKET  */
    LEFT_CURLY_BRACKET = 271,      /* LEFT_CURLY_BRACKET  */
    RIGHT_CURLY_BRACKET = 272,     /* RIGHT_CURLY_BRACKET  */
    ASSIGN_OP = 273,               /* ASSIGN_OP  */
    SEMICOLON = 274,               /* SEMICOLON  */
    COMMA = 275,                   /* COMMA  */
    LT = 276,                      /* LT  */
    LE = 277,                      /* LE  */
    GT = 278,                      /* GT  */
    GE = 279,                      /* GE  */
    EQ = 280,                      /* EQ  */
    NE = 281,                      /* NE  */
    NOT = 282,                     /* NOT  */
    AND = 283,                     /* AND  */
    OR = 284,                      /* OR  */
    QUESTION_MARK = 285,           /* QUESTION_MARK  */
    COLON = 286,                   /* COLON  */
    INT_VAL = 287,                 /* INT_VAL  */
    FLOAT_VAL = 288,               /* FLOAT_VAL  */
    STR_CONST = 289,               /* STR_CONST  */
    NAME = 290,                    /* NAME  */
    UMINUS = 291                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INTEGER 258
#define FLOAT 259
#define STRING 260
#define VOID 261
#define BOOL 262
#define READ 263
#define PRINT 264
#define PLUS 265
#define MINUS 266
#define MULT 267
#define DIV 268
#define LEFT_ROUND_BRACKET 269
#define RIGHT_ROUND_BRACKET 270
#define LEFT_CURLY_BRACKET 271
#define RIGHT_CURLY_BRACKET 272
#define ASSIGN_OP 273
#define SEMICOLON 274
#define COMMA 275
#define LT 276
#define LE 277
#define GT 278
#define GE 279
#define EQ 280
#define NE 281
#define NOT 282
#define AND 283
#define OR 284
#define QUESTION_MARK 285
#define COLON 286
#define INT_VAL 287
#define FLOAT_VAL 288
#define STR_CONST 289
#define NAME 290
#define UMINUS 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "a2.y"

    int int_val;
    float float_val;
    char* string_val;
    std::vector<char*>* id_list;
    Ast *ast;
    std::vector<Ast*>* ast_list;

#line 148 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
