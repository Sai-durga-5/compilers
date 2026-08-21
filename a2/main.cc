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


FILE *fp = NULL;
int print_tokens = 0;

SymbolTable symtab;
Ast* ast_root = nullptr;

int main(int argc, char *argv[]) {

    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: scLp [OPTION...] [FILE]\n";
        return 1;
    }

    if (argc == 3 && strcmp(argv[1], "--show-tokens") == 0) {
        print_tokens = 1;
        yyin = fopen(argv[2], "r");
        if (!yyin) {
            perror("Error opening input file");
            return 1;
        }

        std::string out_file = std::string(argv[2]) + ".toks";
        fp = fopen(out_file.c_str(), "w");
        if (!fp) {
            perror("Error opening token output file");
            return 1;
        }
    }
    else if (argc == 2) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Error opening input file");
            return 1;
        }
    }
    else {
        std::cerr << "Usage: scLp [OPTION...] [FILE]\n";
        return 1;
    }

    yyparse();

    if (ast_root && !ast_root->check_ast()) {
        std::cerr << "Semantic errors detected.\n";
        return 1;
    }

    if (ast_root)
        ast_root->print(std::cout);

    if (yyin) fclose(yyin);
    if (fp) fclose(fp);

    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Parse Error: %s at line %d\n", s, yylineno);
    return 1;
}
