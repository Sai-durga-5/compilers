#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "ast.hh"
#include "symtab.hh"

extern int yylex(void);
extern FILE *yyin;
extern programnode *prog_root;
extern Ast *root;

int yyparse();

// ── globals ───────────────────────────────────────────────────────────────────
int   last_token   = 0;
char *last_lexeme  = nullptr;
int   stop_parse   = 0;

FILE *tok_file  = NULL;
FILE *astfile   = NULL;
FILE *tacfile   = NULL;
FILE *rtlfile   = NULL;
FILE *asmfile   = NULL;

const char *input_filename = NULL;
int show_tokens = 0;
int show_ast    = 0;
int sa_scan     = 0;
int sa_parse    = 0;
int sa_ast      = 0;
int show_tac    = 0;
int sa_tac      = 0;
int show_rtl    = 0;
int sa_rtl      = 0;
int show_asm    = 0;
int sa_asm      = 0;

// ── file helpers ──────────────────────────────────────────────────────────────

void open_tok_file(){
    if(tok_file == NULL && show_tokens){
        char fname[256];
        snprintf(fname, sizeof(fname), "%s.toks", input_filename);
        tok_file = fopen(fname, "w");
        if(!tok_file) perror("fopen tok_file");
    }
}
void clear_tok_file(){
    if(tok_file){ fflush(tok_file); ftruncate(fileno(tok_file), 0); rewind(tok_file); }
}
void open_ast_file(){
    if(astfile == NULL){
        char fname[256];
        snprintf(fname, sizeof(fname), "%s.ast", input_filename);
        astfile = fopen(fname, "w");
        if(!astfile) perror("fopen ast_file");
    }
}
void clear_ast_file(){
    if(astfile && astfile != stderr){ fflush(astfile); ftruncate(fileno(astfile), 0); rewind(astfile); }
}
void open_tac_file(){
    if(tacfile == NULL){
        char fname[256];
        snprintf(fname, sizeof(fname), "%s.tac", input_filename);
        tacfile = fopen(fname, "w");
        if(!tacfile) perror("fopen tac_file");
    }
}
void clear_tac_file(){
    if(tacfile && tacfile != stderr){ fflush(tacfile); ftruncate(fileno(tacfile), 0); rewind(tacfile); }
}
void open_rtl_file(){
    if(rtlfile == NULL){
        char fname[256];
        snprintf(fname, sizeof(fname), "%s.rtl", input_filename);
        rtlfile = fopen(fname, "w");
        if(!rtlfile) perror("fopen rtl_file");
    }
}
void open_asm_file(){
    if(asmfile == NULL){
        char fname[256];
        snprintf(fname, sizeof(fname), "%s.spim", input_filename);
        asmfile = fopen(fname, "w");
        if(!asmfile) perror("fopen asm_file");
    }
}

// ── main ──────────────────────────────────────────────────────────────────────

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr,
            "Usage: sclp [--show-tokens] [--sa-scan] [--show-ast] [--sa-parse]\n"
            "            [--sa-ast] [--show-tac] [--sa-tac] [--show-rtl] [--sa-rtl] <file>\n");
        return 1;
    }

    for(int i = 1; i < argc; i++){
        if     (strcmp(argv[i], "--sa-scan")     == 0) sa_scan     = 1;
        else if(strcmp(argv[i], "--show-tokens") == 0) show_tokens = 1;
        else if(strcmp(argv[i], "--show-ast")    == 0) show_ast    = 1;
        else if(strcmp(argv[i], "--sa-parse")    == 0) { sa_parse = 1; stop_parse = 1; }
        else if(strcmp(argv[i], "--sa-ast")      == 0) sa_ast      = 1;
        else if(strcmp(argv[i], "--show-tac")    == 0) show_tac    = 1;
        else if(strcmp(argv[i], "--sa-tac")      == 0) sa_tac      = 1;
        else if(strcmp(argv[i], "--show-rtl")    == 0) show_rtl    = 1;
        else if(strcmp(argv[i], "--sa-rtl")      == 0) sa_rtl      = 1;
        else if(strcmp(argv[i], "--show-asm")    == 0) show_asm    = 1;
        else if(strcmp(argv[i], "--sa-asm")      == 0) sa_asm      = 1;
        else input_filename = argv[i];
    }

    if(!input_filename){
        fprintf(stderr, "sclp: no input file specified\n");
        return 1;
    }

    yyin = fopen(input_filename, "r");
    if(!yyin){
        fprintf(stderr, "sclp: cannot open file '%s'\n", input_filename);
        return 1;
    }

    int will_ast = !sa_parse;
    int will_tac = will_ast && !sa_ast;
    int will_rtl = will_tac && !sa_tac;
    int will_asm = will_rtl && !sa_rtl;

    if(show_ast && will_ast){
        open_ast_file();
        if(!astfile){ fclose(yyin); return 1; }
    } else {
        astfile = stderr;
    }

    if(show_tac && will_tac){
        open_tac_file();
        if(!tacfile){ fclose(yyin); return 1; }
    } else {
        tacfile = fopen("/dev/null", "w");
        if(!tacfile) tacfile = stderr;
    }

    if(show_rtl && will_rtl){
        open_rtl_file();
        if(!rtlfile){ fclose(yyin); return 1; }
    } else {
        rtlfile = fopen("/dev/null", "w");
        if(!rtlfile) rtlfile = stderr;
    }

    if(show_asm && will_asm){
        open_asm_file();
        if(!asmfile){ fclose(yyin); return 1; }
    } else {
        asmfile = fopen("/dev/null", "w");
        if(!asmfile) asmfile = stderr;
    }

    if(sa_scan){
        int tok; while((tok = yylex()) != 0);
        if(tok_file) fclose(tok_file);
        fclose(yyin); return 0;
    }

    // ── parse ─────────────────────────────────────────────────────────────────
    int status = yyparse();
    if(status != 0) goto cleanup;

    // ── AST ───────────────────────────────────────────────────────────────────
    if(will_ast && show_ast && prog_root){
        prog_root->print(0);
    }

    if(!will_tac) goto cleanup;

    // ── TAC + RTL ─────────────────────────────────────────────────────────────
    if(prog_root){
        if(show_tac)
            prog_root->print_tac();

        if(will_rtl && show_rtl)
            prog_root->print_rtl();

        if(will_asm && show_asm)
            prog_root->print_asm();
    }

cleanup:
    if(tok_file){ fclose(tok_file); tok_file = NULL; }
    if(astfile && astfile != stderr){ fclose(astfile); astfile = NULL; }
    if(tacfile && tacfile != stderr){ fclose(tacfile); tacfile = NULL; }
    if(rtlfile && rtlfile != stderr){ fclose(rtlfile); rtlfile = NULL; }
    if(asmfile && asmfile != stderr){ fclose(asmfile); asmfile = NULL; }
    fclose(yyin);
    return status;
}
