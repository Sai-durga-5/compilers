#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

enum class SymbolKind {
    VARIABLE,
    FUNCTION,
    PARAMETER,
};

using namespace std;
struct Symbol {
    string name;
    string type;
    SymbolKind kind;
    int line;

    Symbol() = default;
    Symbol(const string &n, const string &t, SymbolKind k, int l) {
        this->name = n;
        this->type = t;
        this->kind = k;
        this->line = l;
    }
};

class SymbolTable{
private :
    vector<unordered_map<string, Symbol>> scopes;
public:
    SymbolTable();
    void enter_scope();
    void exit_scope();
    bool insert(const string& name,const string& type,SymbolKind kind,int line);
    Symbol* lookup(const string& name);
    void print();
};