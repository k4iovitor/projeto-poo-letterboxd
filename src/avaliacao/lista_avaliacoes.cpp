#include "lista_avaliacoes.hpp"
#include <iostream>

ListaAvaliacoes::ListaAvaliacoes() {
    std::cout << "ListaAvaliacoes criada\n";
}

ListaAvaliacoes::~ListaAvaliacoes() {
    std::cout << "~ListaAvaliacoes destruida. Invocando destruicao de suas "
              << avaliacoes_.size() << " avaliacoes internas:\n";
    // unique_ptr destruirá automaticamente as Avaliacoes aqui.
}

void ListaAvaliacoes::adicionar_avaliacao(std::string nome_filme, int nota, std::string comentario) {
    // Uso de unique_ptr para garantir a composição e gerenciamento automático
    avaliacoes_.push_back(std::make_unique<Avaliacao>(nome_filme, nota, comentario));
}

float ListaAvaliacoes::calcular_media() const {
    if (avaliacoes_.empty()) {
        return 0.0f;
    }

    int soma = 0;
    for (const auto& avaliacao : avaliacoes_) {
        soma += avaliacao->get_nota();
    }

    return static_cast<float>(soma) / avaliacoes_.size();
}

void ListaAvaliacoes::exibir_todas() const {
    std::cout << "--- Lista de Avaliacoes ---\n";
    for (const auto& avaliacao : avaliacoes_) {
        std::cout << avaliacao->formatar_avaliacao() << "\n";
    }
    std::cout << "---------------------------\n";
}
