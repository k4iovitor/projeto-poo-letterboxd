#include "filme.hpp"
#include <iostream>

Filme::Filme(std::string nome, int ano, std::string genero, int duracao)
    : ItemAcervo(nome, ano, genero), duracao_minutos_(duracao) {
    std::cout << "Filme(" << nome_ << ") criado\n";
}

Filme::~Filme() {
    std::cout << "~Filme(" << nome_ << ") destruido\n";
}

float Filme::calcular_nota() const {
    // Lógica: filmes com duração entre 90-150min recebem nota mais alta
    // (duração "ideal"). Fora dessa faixa, a nota diminui.
    if (duracao_minutos_ >= 90 && duracao_minutos_ <= 150) {
        return 8.0f + (static_cast<float>(duracao_minutos_ - 90) / 60.0f);
    }
    return 6.0f;
}

void Filme::exibir_info() const {
    // Chama a versão base primeiro
    ItemAcervo::exibir_info();

    // Complementa com informações específicas de filme
    int horas = duracao_minutos_ / 60;
    int minutos = duracao_minutos_ % 60;
    std::cout << " | " << horas << "h";
    if (minutos > 0) {
        std::cout << " " << minutos << "m";
    }
    std::cout << " | Nota: " << calcular_nota() << "\n";
}

std::string Filme::formatar() const {
    // Implementação da interface Exibivel
    int horas = duracao_minutos_ / 60;
    int minutos = duracao_minutos_ % 60;
    std::string tempo_str = std::to_string(horas) + "h";
    if (minutos > 0) {
        tempo_str += " " + std::to_string(minutos) + "m";
    }
    return "[ Filme ] " + nome_ + " (" + std::to_string(ano_) + ") - "
           + genero_ + " - " + tempo_str
           + " - Nota: " + std::to_string(calcular_nota()).substr(0, 4);
}

int Filme::get_duracao_minutos() const { return duracao_minutos_; }

std::string Filme::formatar_info() const {
    int horas = duracao_minutos_ / 60;
    int minutos = duracao_minutos_ % 60;

    std::string tempo_str = std::to_string(horas) + "h ";
    if (minutos > 0) {
        tempo_str += std::to_string(minutos) + "m";
    }

    return nome_ + " (" + std::to_string(ano_) + ") - " + genero_ + " - " + tempo_str;
}
