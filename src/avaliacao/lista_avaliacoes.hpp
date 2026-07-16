#ifndef LISTA_AVALIACOES_HPP
#define LISTA_AVALIACOES_HPP

#include <vector>
#include <memory>
#include "avaliacao.hpp"

// ListaAvaliacoes gerencia as instâncias de Avaliacao (Composição)
class ListaAvaliacoes {
private:
    std::vector<std::unique_ptr<Avaliacao>> avaliacoes_;

public:
    ListaAvaliacoes();
    ~ListaAvaliacoes();

    // Cria a avaliação e adiciona internamente (demonstração de composição estrita)
    void adicionar_avaliacao(std::string nome_filme, int nota, std::string comentario);

    // Métodos com lógica real
    float calcular_media() const;
    void exibir_todas() const;
};

#endif 
