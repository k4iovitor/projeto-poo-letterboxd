#include "avaliacao.hpp"
#include <iostream>

Avaliacao::Avaliacao(std::string nome_filme, int nota, std::string comentario)
    : nome_filme_(nome_filme), nota_(nota), comentario_(comentario) {
    std::cout << "Avaliacao do filme '" << nome_filme_ << "' criada com nota " << nota_ << "\n";
}

Avaliacao::~Avaliacao() {
    std::cout << "~Avaliacao do filme '" << nome_filme_ << "' destruida\n";
}

std::string Avaliacao::get_nome_filme() const { return nome_filme_; }
int Avaliacao::get_nota() const { return nota_; }
std::string Avaliacao::get_comentario() const { return comentario_; }

bool Avaliacao::validar_nota() const {
    return nota_ >= 1 && nota_ <= 5;
}

std::string Avaliacao::formatar_avaliacao() const {
    std::string estrelas(nota_, '*');
    std::string vazias(5 - nota_, '-');
    return nome_filme_ + " [" + estrelas + vazias + "] : " + comentario_;
}
