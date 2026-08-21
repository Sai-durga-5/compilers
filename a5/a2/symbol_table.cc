#include "symbol_table.hh"

// Constructor: start with global scope
SymbolTable::SymbolTable() {
    enter_scope();
}

void SymbolTable::enter_scope() {
    unordered_map<string, Symbol> new_scope;
    scopes.push_back(new_scope);
}

void SymbolTable::exit_scope() {
    if (!scopes.empty()) {
        scopes.pop_back();
    }
}

bool SymbolTable::insert(const string& name,
                         const string& type,
                         SymbolKind kind,
                         int line) {
    if (scopes.empty()) return false;

    auto& current_scope = scopes.back();

    // Redeclaration in SAME scope → error
    if (current_scope.find(name) != current_scope.end()) {
        return false;
    }

    current_scope[name] = Symbol(name, type, kind, line);
    return true;
}

Symbol* SymbolTable::lookup( const string& name) {
    // Search from innermost scope outward
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return &found->second;
        }
    }
    return nullptr;
}

void SymbolTable::print() {
    std::cout << "\n========== SYMBOL TABLE ==========\n";

    int scope_level = 0;
    for (const auto& scope : scopes) {
        std::cout << "Scope " << scope_level++ << ":\n";
        for (const auto& [name, sym] : scope) {
            std::cout << "  " << sym.name
                      << " : " << sym.type;

            switch (sym.kind) {
                case SymbolKind::VARIABLE:
                    std::cout << " (var)";
                    break;
                case SymbolKind::FUNCTION:
                    std::cout << " (func)";
                    break;
                case SymbolKind::PARAMETER:
                    std::cout << " (param)";
                    break;
            }

            std::cout << " [line " << sym.line << "]\n";
        }
    }

    std::cout << "=================================\n";
}
