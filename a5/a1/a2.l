%option yylineno
%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <string.h>
    extern int print_tokens;
    extern FILE *fp;
    void print_tok(const char *token_name, char *lexeme, int lineno);
%}
digit    [0-9]
letter    [a-zA-Z_]
whitespace  [ \t\r\n]

%%

"//".*  ;
{whitespace}+  ;

int     { print_tok("INTEGER", yytext, yylineno); return INTEGER; }
float   { print_tok("FLOAT", yytext, yylineno); return FLOAT; }
void    { print_tok("VOID", yytext, yylineno); return VOID; }
string  { print_tok("STRING", yytext, yylineno); return STRING; }
bool    { print_tok("BOOL", yytext, yylineno); return BOOL; }
read    { print_tok("READ", yytext, yylineno); return READ; }
print   { print_tok("WRITE", yytext, yylineno); return PRINT; }

";"     { print_tok("SEMICOLON", yytext, yylineno); return SEMICOLON; }
"("     { print_tok("LEFT ROUND BRACKET", yytext, yylineno); return LEFT_ROUND_BRACKET; }
"{"     { print_tok("LEFT CURLY BRACKET", yytext, yylineno); return LEFT_CURLY_BRACKET; }
")"     { print_tok("RIGHT ROUND BRACKET", yytext, yylineno); return RIGHT_ROUND_BRACKET; }
"}"     { print_tok("RIGHT CURLY BRACKET", yytext, yylineno); return RIGHT_CURLY_BRACKET; }
"="     { print_tok("ASSIGN OP", yytext, yylineno); return ASSIGN_OP; }
","     { print_tok("COMMA", yytext, yylineno); return COMMA; }
"+"     { print_tok("PLUS", yytext, yylineno); return PLUS; }
"-"     { print_tok("MINUS", yytext, yylineno); return MINUS; }
"*"     { print_tok("MULT", yytext, yylineno); return MULT; }
"/"     { print_tok("DIV", yytext, yylineno); return DIV; }
"<"     { print_tok("LT", yytext, yylineno); return LT; }
"<="     { print_tok("LE", yytext, yylineno); return LE; }
">"     { print_tok("GT", yytext, yylineno); return GT; }
">="     { print_tok("GE", yytext, yylineno); return GE; }
"!="     { print_tok("NE", yytext, yylineno); return NE; }
"=="     { print_tok("EQ", yytext, yylineno); return EQ; }
"and"     { print_tok("AND", yytext, yylineno); return AND; }
"or"     { print_tok("OR", yytext, yylineno); return OR; }
":"     { print_tok("COLON", yytext, yylineno); return COLON; }
"?"     { print_tok("QUESTION_MARK", yytext, yylineno); return QUESTION_MARK; }

{digit}+\.{digit}+    { print_tok("FLOAT NUM", yytext, yylineno); yylval.float_val = atof(yytext); return FLOAT_VAL; }
{digit}+              { print_tok("INT NUM", yytext, yylineno); yylval.int_val = atoi(yytext); return INT_VAL; }
\"[^\"\n]*\"          { print_tok("STR_CONST", yytext, yylineno); yylval.string_val = strdup(yytext); return STR_CONST; }
{letter}({letter}|{digit})*  { print_tok("NAME", yytext, yylineno); yylval.string_val = strdup(yytext); return NAME; }

.       { printf("Illegal Character : %s\n", yytext); }

%%

void print_tok(const char *token_name, char *lexeme, int lineno) {
    if (print_tokens) {
        fprintf(fp, "Token Name: %s Lexeme: %s Lineno: %d\n", token_name, lexeme, lineno);
    }
}