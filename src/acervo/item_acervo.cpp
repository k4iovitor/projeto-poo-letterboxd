#include "item_acervo.hpp"
#include <iostream>

ItemAcervo::ItemAcervo(std::string nome, int ano, std::string genero)
    : nome_(nome), ano_(ano), genero_(genero) {
    std::cout << "ItemAcervo(" << nome_ << ") criado\n";
}

ItemAcervo::~ItemAcervo() {
    std::cout << "~ItemAcervo(" << nome_ << ") destruido\n";
}

// Implementação padrão do método virtual não-puro
void ItemAcervo::exibir_info() const {
    std::cout << "[Acervo] " << nome_ << " (" << ano_ << ") - " << genero_;
}

std::string ItemAcervo::get_nome() const { return nome_; }
int ItemAcervo::get_ano() const { return ano_; }
std::string ItemAcervo::get_genero() const { return genero_; }
