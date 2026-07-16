#include "serie.hpp"
#include <iostream>

Serie::Serie(std::string nome, int ano, std::string genero,
             int temporadas, int episodios_por_temporada)
    : ItemAcervo(nome, ano, genero),
      temporadas_(temporadas), episodios_por_temporada_(episodios_por_temporada) {
    std::cout << "Serie(" << nome_ << ") criada - "
              << temporadas_ << " temporadas\n";
}

Serie::~Serie() {
    std::cout << "~Serie(" << nome_ << ") destruida\n";
}

float Serie::calcular_nota() const {
    // Lógica: séries com mais temporadas tendem a ter nota base mais alta,
    // indicando que foram renovadas por sucesso. Teto em 10.0.
    float nota = 5.0f + (temporadas_ * 0.5f);
    if (nota > 10.0f) nota = 10.0f;
    return nota;
}

void Serie::exibir_info() const {
    // Chama a versão base primeiro
    ItemAcervo::exibir_info();
    // Complementa com informações específicas de séries
    std::cout << " | " << temporadas_ << " temporadas, "
              << episodios_por_temporada_ << " eps/temporada ("
              << get_total_episodios() << " episodios total)"
              << " | Nota: " << calcular_nota() << "\n";
}

int Serie::get_temporadas() const { return temporadas_; }
int Serie::get_episodios_por_temporada() const { return episodios_por_temporada_; }
int Serie::get_total_episodios() const { return temporadas_ * episodios_por_temporada_; }
