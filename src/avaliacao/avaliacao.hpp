#ifndef AVALIACAO_HPP
#define AVALIACAO_HPP

#include <string>

class Avaliacao {
private:
    std::string nome_filme_;
    int nota_; // 1 a 5 estrelas
    std::string comentario_;

public:
    Avaliacao(std::string nome_filme, int nota, std::string comentario);
    ~Avaliacao();

    std::string get_nome_filme() const;
    int get_nota() const;
    std::string get_comentario() const;

    // Métodos com lógica real
    bool validar_nota() const;
    std::string formatar_avaliacao() const;
};

#endif // AVALIACAO_HPP
