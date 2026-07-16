#ifndef FILME_HPP
#define FILME_HPP

#include "item_acervo.hpp"
#include "exibivel.hpp"
#include <string>

// Filme herda de ItemAcervo (base abstrata) e Exibivel (interface pura)
// Demonstra herança múltipla segura
class Filme : public ItemAcervo, public Exibivel {
private:
    int duracao_minutos_;

public:
    Filme(std::string nome, int ano, std::string genero, int duracao);
    ~Filme() override;

    // Override do método virtual puro de ItemAcervo
    float calcular_nota() const override;

    // Override do método virtual não-puro de ItemAcervo
    // Chama ItemAcervo::exibir_info() e complementa 
    void exibir_info() const override;

    // Override do método puro de Exibivel (interface)
    std::string formatar() const override;

    // Getters
    int get_duracao_minutos() const;

    // Método de formatação para compatibilidade
    std::string formatar_info() const;
};

#endif
