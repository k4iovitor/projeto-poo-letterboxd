#ifndef SERIE_HPP
#define SERIE_HPP

#include "item_acervo.hpp"

// Classe concreta final — ninguém pode herdar de Serie.
// Isso garante que a implementação de Serie não será alterada
// por subclasses, preservando a integridade do cálculo de nota
// e exibição específicos para séries de TV.
class Serie final : public ItemAcervo {
private:
    int temporadas_;
    int episodios_por_temporada_;

public:
    Serie(std::string nome, int ano, std::string genero,
          int temporadas, int episodios_por_temporada);
    ~Serie() override;

    // Override do método puro da base
    float calcular_nota() const override;

    // Override do método não-puro — chama ItemAcervo::exibir_info() e complementa
    void exibir_info() const override;

    // Getters
    int get_temporadas() const;
    int get_episodios_por_temporada() const;
    int get_total_episodios() const;
};

#endif
