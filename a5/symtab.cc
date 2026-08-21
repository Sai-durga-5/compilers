#include "symtab.hh"
#include <cstdio>
#include <cstdlib>

static bool sameParam(const std::vector<Type>& a, const std::vector<Type>& b){
    if(a.size() != b.size()) return false;
    for(size_t i = 0; i < a.size(); i++)
        if(a[i] != b[i]) return false;
    return true;
}

void SymbolTable::declarefunc(const std::string& name, Type type, const std::vector<Type>& params){
    int idx = lookupLocal(name);
    if(idx == -1){
        Symbol s;
        s.name         = name;
        s.type         = type;
        s.kind         = SYM_FUNC;
        s.is_declared  = true;
        s.is_defined   = false;
        s.params       = params;
        table.push_back(s);
        return;
    }
    Symbol& sym = table[idx];
    if(sym.is_declared){
        fprintf(stderr, "Semantic error: multiple declarations of '%s'\n", name.c_str());
        exit(1);
    }
    if(sym.is_defined){
        if(!sameParam(sym.params, params)){
            fprintf(stderr, "Semantic error: declaration of '%s' does not match its definition\n", name.c_str());
            exit(1);
        }
    }
    sym.is_declared = true;
}

void SymbolTable::definefunc(const std::string& name, Type type, const std::vector<Type>& params){
    int idx = lookupLocal(name);
    if(idx == -1){
        Symbol s;
        s.name        = name;
        s.type        = type;
        s.kind        = SYM_FUNC;
        s.is_declared = false;
        s.is_defined  = true;
        s.params      = params;
        table.push_back(s);
        return;
    }
    Symbol& sym = table[idx];
    if(sym.is_defined){
        fprintf(stderr, "Semantic error: '%s' already defined\n", name.c_str());
        exit(1);
    }
    if(sym.is_declared){
        if(!sameParam(sym.params, params)){
            fprintf(stderr, "Semantic error: definition of '%s' does not match its declaration\n", name.c_str());
            exit(1);
        }
    }
    sym.is_defined = true;
}

Symbol* SymbolTable::lookupFunc(const std::string& name){
    for(auto& s : table)
        if(s.name == name && s.kind == SYM_FUNC) return &s;
    if(parent) return parent->lookupFunc(name);
    return nullptr;
}

bool SymbolTable::insert(const std::string& name, Type type){
    for(auto& s : table)
        if(s.name == name) return false;
    Symbol sym;
    sym.name = name;
    sym.type = type;
    sym.kind = SYM_VAR;
    table.push_back(sym);
    return true;
}

int SymbolTable::lookup(const std::string& name) const {
    for(int i = 0; i < (int)table.size(); i++)
        if(table[i].name == name) return i;
    if(parent) return parent->lookup(name);
    return -1;
}

int SymbolTable::lookupLocal(const std::string& name) const {
    for(int i = 0; i < (int)table.size(); i++)
        if(table[i].name == name) return i;
    return -1;
}

Type SymbolTable::lookupType(const std::string& name) const {
    for(const auto& s : table)
        if(s.name == name) return s.type;
    if(parent) return parent->lookupType(name);
    return TYPE_ERROR;
}

int SymbolTable::lookupOffset(const std::string& name) const {
    for(const auto& s : table)
        if(s.name == name) return s.offset;
    if(parent) return parent->lookupOffset(name);
    return 0;
}

int SymbolTable::assign_offsets(int start_offset){
    int off = start_offset;
    for(auto& s : table){
        if(s.kind != SYM_VAR) continue;
        int sz = (s.type == TYPE_FLOAT) ? 8 : 4;
        s.offset     = off;
        s.offset_set = true;
        off -= sz;
    }
    return -(off - start_offset);
}
