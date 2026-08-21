%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"

extern int show_tokens;
extern int sa_scan;
extern const char *input_filename;
extern FILE *tok_file;
extern void open_tok_file();

extern char* last_lexeme;
extern const char* token_name(int tok);
extern int last_token;
extern void clear_tok_file();

void print_tokens(int tok){
    last_token = tok;
    if(last_lexeme) free(last_lexeme);
    last_lexeme = strdup(yytext);
    if(show_tokens && tok_file)
        fprintf(tok_file, "\tToken Name: %s \tLexeme: %s \tLineno: %d\n",
                token_name(tok), yytext, yylineno);
}
%}

digit [0-9]
alpha [a-zA-Z_]
%option noyywrap
%option nounput
%option yylineno
%%

int     { open_tok_file(); print_tokens(INTEGER); return INTEGER; }
float   { open_tok_file(); print_tokens(FLOAT);   return FLOAT; }
string  { open_tok_file(); print_tokens(STRING);  return STRING; }
bool    { open_tok_file(); print_tokens(BOOL);    return BOOL; }
void    { open_tok_file(); print_tokens(VOID);    return VOID; }
if      { open_tok_file(); print_tokens(IF);      return IF; }
else    { open_tok_file(); print_tokens(ELSE);    return ELSE; }
while   { open_tok_file(); print_tokens(WHILE);   return WHILE; }
do      { open_tok_file(); print_tokens(DO);      return DO; }
return  { open_tok_file(); print_tokens(RETURN);  return RETURN; }
main    { open_tok_file(); print_tokens(NAME); yylval.name = new std::string(yytext); return NAME; }
print   { open_tok_file(); print_tokens(WRITE);   return WRITE; }
read    { open_tok_file(); print_tokens(READ);    return READ; }

{digit}+\.{digit}+ {
    open_tok_file();
    print_tokens(FLOAT_NUMBER);
    yylval.fvalue = atof(yytext);
    return FLOAT_NUMBER;
}
{digit}+ {
    open_tok_file();
    print_tokens(INTEGER_NUMBER);
    yylval.value = atoi(yytext);
    return INTEGER_NUMBER;
}
{alpha}({alpha}|{digit})* {
    open_tok_file();
    print_tokens(NAME);
    yylval.name = new std::string(yytext);
    return NAME;
}
\"([^\"\n])*\" {
    open_tok_file();
    print_tokens(STRING_LITERAL);
    yylval.name = new std::string(yytext);
    return STRING_LITERAL;
}

"="  { open_tok_file(); print_tokens(ASSIGN); return ASSIGN; }
"+"  { open_tok_file(); print_tokens(PLUS);   return PLUS; }
"-"  { open_tok_file(); print_tokens(MINUS);  return MINUS; }
"/"  { open_tok_file(); print_tokens(DIV);    return DIV; }
"*"  { open_tok_file(); print_tokens(MULT);   return MULT; }

";"  { open_tok_file(); print_tokens(SEMICOLON); return SEMICOLON; }
":"  { open_tok_file(); print_tokens(COLON);     return COLON; }
"("  { open_tok_file(); print_tokens(LPAREN);    return LPAREN; }
")"  { open_tok_file(); print_tokens(RPAREN);    return RPAREN; }
"{"  { open_tok_file(); print_tokens(LBRACE);    return LBRACE; }
"}"  { open_tok_file(); print_tokens(RBRACE);    return RBRACE; }
","  { open_tok_file(); print_tokens(COMMA);     return COMMA; }

"<=" { open_tok_file(); print_tokens(LE); return LE; }
">=" { open_tok_file(); print_tokens(GE); return GE; }
"==" { open_tok_file(); print_tokens(EQ); return EQ; }
"!=" { open_tok_file(); print_tokens(NE); return NE; }
"<"  { open_tok_file(); print_tokens(LT); return LT; }
">"  { open_tok_file(); print_tokens(GT); return GT; }

"&&" { open_tok_file(); print_tokens(AND);     return AND; }
"||" { open_tok_file(); print_tokens(OR);      return OR; }
"!"  { open_tok_file(); print_tokens(NOT);     return NOT; }
"?"  { open_tok_file(); print_tokens(TERINARY); return TERINARY; }

[ \t\n\r]+ ;

"//".*  { /* ignore line comments */ }

. {
    fprintf(stderr, "sclp error: File: %s, Line: %d, Unknown character: '%s'\n",
            input_filename, yylineno, yytext);
    clear_tok_file();
    exit(1);
}

<<EOF>> { return 0; }

%%
