#include "usuario.hpp"
#include <iostream>

Usuario::Usuario(std::string nome, std::string nome_usuario)
    : nome_(nome), nome_usuario_(nome_usuario) {
    std::cout << "Usuario(" << nome_usuario_ << ") criado\n";
}

Usuario::~Usuario() {
    std::cout << "~Usuario(" << nome_usuario_ << ") destruido.\n";
}

std::string Usuario::get_nome() const { return nome_; }
std::string Usuario::get_nome_usuario() const { return nome_usuario_; }

void Usuario::adicionar_watchlist(const Filme& filme) {
    // Guarda o ponteiro (agregando)
    watchlist_.push_back(&filme);
    std::cout << "Filme '" << filme.get_nome() << "' adicionado a watchlist de "
              << nome_usuario_ << "\n";
}

void Usuario::exibir_watchlist() const {
    std::cout << "Watchlist de " << nome_usuario_ << " (" << watchlist_.size() << " filmes):\n";
    for (const Filme* filme : watchlist_) {
        std::cout << " - " << filme->formatar_info() << "\n";
    }
}

void Usuario::exibir_perfil() const {
    std::cout << "=== Perfil: " << nome_ << " (@" << nome_usuario_ << ") ===\n";
    exibir_watchlist();
    std::cout << "==========================\n";
}
