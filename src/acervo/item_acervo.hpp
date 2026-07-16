#ifndef ITEM_ACERVO_HPP
#define ITEM_ACERVO_HPP

#include <string>

// Classe base abstrata: representa qualquer item do acervo (filme, série, etc.)
// Contém pelo menos um método virtual puro e um método virtual não-puro.
class ItemAcervo {
protected:
    std::string nome_;
    int ano_;
    std::string genero_;

public:
    ItemAcervo(std::string nome, int ano, std::string genero);

    // Destrutor virtual — garante destruição correta via ponteiro base
    virtual ~ItemAcervo();

    // Método virtual puro (= 0) — obriga todas as derivadas a implementar
    virtual float calcular_nota() const = 0;

    // Método virtual não-puro — tem implementação padrão na base
    virtual void exibir_info() const;

    // Getters
    std::string get_nome() const;
    int get_ano() const;
    std::string get_genero() const;
};

#endif
