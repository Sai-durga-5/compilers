%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

#include "symbol_table.hh"
#include "ast.hh"

using namespace std;

extern int yylineno;
extern FILE *yyin;

int yylex(void);
int yyparse(void);
int yyerror(const char *s);

extern FILE *fp;
extern int print_tokens;

SymbolTable symtab;
Ast* ast_root = nullptr;
%}

/* ===================== */
/* Semantic value union  */
/* ===================== */
%union {
    int int_val;
    float float_val;
    char* string_val;
    std::vector<char*>* id_list;
    Ast *ast;
    std::vector<Ast*>* ast_list;
}

/* ========= */
/* Tokens   */
/* ========= */
%token INTEGER FLOAT STRING VOID BOOL
%token READ PRINT
%token PLUS MINUS MULT DIV
%token LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET
%token LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET
%token ASSIGN_OP SEMICOLON COMMA
%token LT LE GT GE EQ NE
%token NOT AND OR
%token QUESTION_MARK COLON

%token <int_val>    INT_VAL
%token <float_val>  FLOAT_VAL
%token <string_val> STR_CONST
%token <string_val> NAME

/* ================= */
/* Nonterminal types */
/* ================= */
%type <string_val> named_type
%type <id_list>    var_decl_item_list
%type <ast_list> statement_list
%type <ast> statement
%type <ast> assignment_statement
%type <ast> print_statement
%type <ast> read_statement
%type <ast> expression
%type <ast> rel_expression
/* ================= */
/* Operator precedence */
/* ================= */
%right QUESTION_MARK COLON
%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left MULT DIV
%right NOT
%right UMINUS

%%

/* ================= */
/* Program structure */
/* ================= */

program
    : global_decl_statement_list main_function
    | main_function
    ;

global_decl_statement_list
    : global_decl_statement_list var_decl_stmt
    | global_decl_statement_list func_decl
    | var_decl_stmt
    | func_decl
    ;



/* ================= */
/* Function handling */
/* ================= */

func_decl
    : named_type NAME LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET SEMICOLON
      {
          if (!symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     $2, yylineno);
          }
      }
    | named_type NAME LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET SEMICOLON
      {
          if (!symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     $2, yylineno);
          }
      }
    ;

main_function
    : named_type NAME LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET
      LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET
      {
          if (!symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     $2, yylineno);
          }

          if (strcmp($2, "main") == 0) {
              ast_root = new Sequence_Ast(*$8);
          }
      }
    | named_type NAME LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET
      LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET
      {
          if (!symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     $2, yylineno);
          }

          if (strcmp($2, "main") == 0) {
              ast_root = new Sequence_Ast(*$7);
          }
      }
    ;

/* ================= */
/* Parameters        */
/* ================= */

formal_param_list
    : formal_param_list COMMA formal_param
    | formal_param
    ;

formal_param
    : named_type NAME
      {
          if (!symtab.insert($2, $1, SymbolKind::PARAMETER, yylineno)) {
              printf("Semantic Error: redeclaration of parameter '%s' at line %d\n",
                     $2, yylineno);
          }
      }
    ;

/* ================= */
/* Variable handling */
/* ================= */

optional_local_var_decl_stmt_list
    : var_decl_stmt_list
    | /* empty */
    ;

var_decl_stmt_list
    : var_decl_stmt_list var_decl_stmt
    | var_decl_stmt
    ;

var_decl_stmt
    : named_type var_decl_item_list SEMICOLON
      {
          for (auto name : *$2) {
              if (!symtab.insert(name, $1, SymbolKind::VARIABLE, yylineno)) {
                  printf("Semantic Error: redeclaration of variable '%s' at line %d\n",
                         name, yylineno);
              }
          }
          delete $2;
      }
    ;

var_decl_item_list
    : var_decl_item_list COMMA NAME
      {
          $1->push_back($3);
          $$ = $1;
      }
    | NAME
      {
          $$ = new vector<char*>();
          $$->push_back($1);
      }
    ;

/* ================= */
/* Types             */
/* ================= */

named_type
    : INTEGER { $$ = strdup("int"); }
    | FLOAT   { $$ = strdup("float"); }
    | BOOL    { $$ = strdup("bool"); }
    | STRING  { $$ = strdup("string"); }
    | VOID    { $$ = strdup("void"); }
    ;

/* ================= */
/* Statements        */
/* ================= */

statement_list
    : statement_list statement {$1->push_back($2); $$ = $1;}
    | /* empty */              {$$ = new vector<Ast*>();}
    ;

statement
    : assignment_statement { $$ = $1; }
    | print_statement      { $$ = $1; }
    | read_statement       { $$ = $1; }
    ;

assignment_statement
    : NAME ASSIGN_OP expression SEMICOLON
    {
        Symbol* sym = symtab.lookup($1);
        if (!sym) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",
                    $1, yylineno);
            $$ = nullptr;
        } else {
            Ast* lhs = new Name_Ast(string($1), *sym, yylineno);
            $$ = new Assignment_Ast(lhs, $3, yylineno);
        }
    }
    ;

print_statement
    : PRINT expression SEMICOLON
      {
          $$ = new Print_Ast($2, yylineno);
      }
    ;

read_statement
    : READ NAME SEMICOLON
      {
          Symbol* sym = symtab.lookup($2);
          if (!sym) {
              printf("Semantic Error: undeclared variable '%s' at line %d\n",
                     $2, yylineno);
              $$ = nullptr;
          } else {
              $$ = new Read_Ast(new Name_Ast(string($2), *sym, yylineno), yylineno);
          }
      }
    ;

/* ================= */
/* Expressions       */
/* ================= */

expression
    : expression PLUS expression                             {$$ = new Expression_Ast($1, $3, OP_PLUS, yylineno);}
    | expression MINUS expression                            {$$ = new Expression_Ast($1, $3, OP_MINUS, yylineno);}
    | expression MULT expression                             {$$ = new Expression_Ast($1, $3, OP_MULT, yylineno);}
    | expression DIV expression                              {$$ = new Expression_Ast($1, $3, OP_DIV, yylineno);}
    | MINUS expression %prec UMINUS                          {$$ = new Uminus_Ast($2, yylineno);}
    | LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET      {$$ = $2;}
    | expression QUESTION_MARK expression COLON expression   {$$ = new Ternary_Ast($1, $3, $5, yylineno);}
    | expression AND expression                              {$$ = new Logical_Ast($1, $3, OP_AND, yylineno);}
    | expression OR expression                               {$$ = new Logical_Ast($1, $3, OP_OR, yylineno);}
    | NOT expression                                         {$$ = new Logical_Not_Ast($2, yylineno);}
    | rel_expression
    | NAME {
        const Symbol* sym = symtab.lookup($1);
        if (!sym) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",
                    $1, yylineno);
            $$ = nullptr;
        } else {
            $$ = new Name_Ast(string($1), *sym, yylineno);
        }
    }
    | INT_VAL { $$ = new Int_Ast($1, yylineno);}
    | FLOAT_VAL {$$ = new Float_Ast($1, yylineno);}
    | STR_CONST {$$ = new String_Ast(std::string($1), yylineno);}
    ;

rel_expression
    : expression LT expression {$$ = new Relational_Ast($1, $3, OP_LT, yylineno);}
    | expression LE expression {$$ = new Relational_Ast($1, $3, OP_LE, yylineno);}
    | expression GT expression {$$ = new Relational_Ast($1, $3, OP_GT, yylineno);}
    | expression GE expression {$$ = new Relational_Ast($1, $3, OP_GE, yylineno);}
    | expression EQ expression {$$ = new Relational_Ast($1, $3, OP_EQ, yylineno);}
    | expression NE expression {$$ = new Relational_Ast($1, $3, OP_NE, yylineno);}
    ;

%%

/* ================= */
/* Driver & errors   */
/* ================= */

