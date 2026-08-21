#ifndef SYMTAB_HH
#define SYMTAB_HH

#include <string>
#include <vector>
#include "types.hh"

enum SymbolKind {
    SYM_VAR,
    SYM_FUNC
};

struct Symbol {
    std::string name;
    Type type;
    SymbolKind kind;

    bool is_declared = false;
    bool is_defined  = false;
    std::vector<Type> params;

    int  offset      = 0;
    bool offset_set  = false;
};

class SymbolTable {
    SymbolTable *parent;
    std::vector<Symbol> table;

public:
    SymbolTable(SymbolTable *p = nullptr) : parent(p) {}

    void declarefunc(const std::string&, Type, const std::vector<Type>&);
    void definefunc (const std::string&, Type, const std::vector<Type>&);
    Symbol* lookupFunc(const std::string&);

    bool insert(const std::string& name, Type type);
    int  lookup      (const std::string& name) const;
    int  lookupLocal (const std::string& name) const;
    Type lookupType  (const std::string& name) const;
    int  lookupOffset(const std::string& name) const;
    int  assign_offsets(int start_offset = -4);

    SymbolTable *getParent() const { return parent; }
    const std::vector<Symbol>& get_table() const { return table; }
};

#endif // SYMTAB_HH
