%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

%token    INTEGER
%token    FLOAT
%token    STRING
%token    VOID
%token    READ
%token    PRINT
%token    BOOL
%token    PLUS
%token    MINUS
%token    MULT
%token    DIV
%token    LEFT_ROUND_BRACKET
%token    RIGHT_ROUND_BRACKET
%token    LEFT_CURLY_BRACKET
%token    RIGHT_CURLY_BRACKET
%token    ASSIGN_OP
%token    SEMICOLON
%token    COMMA
%token    LE
%token    LT
%token    GE
%token    GT
%token    NE
%token    EQ
%token    NOT
%token    COLON
%token    QUESTION_MARK
%token    AND
%token    OR
%token <float_val>    FLOAT_VAL
%token <int_val>    INT_VAL
%token <string_val>    STR_CONST
%token <string_val>    NAME

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

program
    : global_decl_statement_list main_function
    | main_function
    ;

global_decl_statement_list  
    : global_decl_statement_list func_decl
    | global_decl_statement_list var_decl_stmt
    | var_decl_stmt
    | func_decl
    ;

func_decl
    : func_header LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET SEMICOLON
    | func_header LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET SEMICOLON; 

func_header
    : named_type NAME
    ;

main_function
    : func_header LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET
    | func_header LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET  LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET
    ;

formal_param_list
    : formal_param_list COMMA formal_param
    | formal_param

formal_param 
    : param_type NAME

param_type 
    : INTEGER
    | FLOAT
    | BOOL
    | STRING
    ;


statement_list
    : statement_list statement
    | 
    ;

statement
    : assignment_statement
    | print_statement
    | read_statement
    ;

optional_local_var_decl_stmt_list
    : var_decl_stmt_list
    |
    ;

var_decl_stmt_list
    : var_decl_stmt_list var_decl_stmt
    | var_decl_stmt
    ;

var_decl_stmt
    : named_type var_decl_item_list SEMICOLON
    ;

var_decl_item_list
    : var_decl_item_list COMMA var_decl_item
    | var_decl_item
    ;

var_decl_item 
    : NAME
    ;

named_type
    : INTEGER
    | FLOAT
    | VOID
    | STRING
    | BOOL
    ;

assignment_statement
    : variable_as_operand ASSIGN_OP expression SEMICOLON
    ;

print_statement
    : PRINT expression SEMICOLON
    ;

read_statement
    : READ variable_name SEMICOLON
    ;

expression
    : expression PLUS expression
    | expression MINUS expression
    | expression MULT expression
    | expression DIV expression
    | MINUS expression %prec UMINUS
    | LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET
    | expression QUESTION_MARK expression COLON  expression
    | expression AND expression
    | expression OR expression
    | NOT expression
    | rel_expression
    | variable_as_operand
    | constant_as_operand
    ;

rel_expression
    : expression LT expression
    | expression LE expression
    | expression GT expression
    | expression GE expression
    | expression NE expression
    | expression EQ expression
    ;

variable_as_operand
    : variable_name
    ;

variable_name 
    : NAME
    ;

constant_as_operand
    : INT_VAL
    | FLOAT_VAL
    | STR_CONST
    ;

%%

FILE *fp = NULL;
int print_tokens = 0;

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: scLp [OPTION...] [FILE]\n");
        return 1;
    }
    else if (argc == 3) {
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
