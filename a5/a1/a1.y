%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>   //  needed for malloc

extern int yylineno;
extern FILE *yyin;
int yylex(void);
int yyparse(void);
int yyerror(const char *s);
extern FILE *fp;
extern int print_tokens;
%}

%union {
    int int_val;
    float float_val;
    char* string_val;
}

%token INTEGER FLOAT STRING VOID READ PRINT BOOL
%token PLUS MINUS MULT DIV
%token LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET
%token LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET
%token ASSIGN_OP SEMICOLON COMMA

%token <float_val> FLOAT_VAL
%token <int_val> INT_VAL
%token <string_val> STR_CONST
%token <string_val> NAME

%start program

%%

program
    : global_decl_list main_function
    | main_function
    ;

global_decl_list
    : global_decl_list var_decl_stmt
    | var_decl_stmt
    ;

main_function
    : VOID NAME LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET compound_statement
    ;

compound_statement
    : LEFT_CURLY_BRACKET local_decl_list statement_list RIGHT_CURLY_BRACKET
    ;

local_decl_list
    : /* empty */                 /*  professional style */
    | local_decl_list var_decl_stmt
    ;

var_decl_stmt
    : type var_decl_item_list SEMICOLON
    ;

var_decl_item_list
    : var_decl_item_list COMMA NAME
    | NAME
    ;

type
    : INTEGER
    | FLOAT
    | STRING
    | BOOL
    ;

statement_list
    : /* empty */                 /*  professional style */
    | statement_list statement
    ;

statement
    : assignment_statement
    | print_statement
    | read_statement
    ;

assignment_statement
    : NAME ASSIGN_OP expression SEMICOLON
    ;

expression
    : expression PLUS term
    | expression MINUS term
    | term
    ;

term
    : term MULT unary
    | term DIV unary
    | unary
    ;

unary
    : MINUS unary
    | factor
    ;

factor
    : NAME
    | constant
    | LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET
    ;

print_statement
    : PRINT expression SEMICOLON
    ;

read_statement
    : READ NAME SEMICOLON
    ;

constant
    : INT_VAL
    | FLOAT_VAL
    | STR_CONST
    ;

%%

/* FIXED: FILE not File */
FILE *fp = NULL;
int print_tokens = 0;

int main(int argc, char *argv[]) {

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: scLp [OPTION...] [FILE]\n");
        return 1;
    }

    if (argc == 3) {

        if (strcmp(argv[1], "--show-tokens") == 0) {

            print_tokens = 1;

            yyin = fopen(argv[2], "r");
            if (!yyin) {
                perror("Error opening input file");
                return 1;
            }

            char *out_file = malloc(strlen(argv[2]) + 6);
            strcpy(out_file, argv[2]);
            strcat(out_file, ".toks");

            fp = fopen(out_file, "w");
            if (!fp) {
                perror("Error opening token output file");
                free(out_file);
                return 1;
            }

            free(out_file);

            yyparse();

            fclose(yyin);
            fclose(fp);
        }
        else {
            fprintf(stderr, "Usage: scLp [OPTION...] [FILE]\n");
            return 1;
        }
    }

    else if (argc == 2) {

        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Error opening input file");
            return 1;
        }

        yyparse();
        fclose(yyin);
    }

    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Parse Error: %s, Line Number: %d\n", s, yylineno);
    return 1;
}
