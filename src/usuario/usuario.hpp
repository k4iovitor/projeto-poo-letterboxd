#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>
#include "acervo/filme.hpp"

// Usuario tem uma Watchlist (Agregação de Filme)
class Usuario {
private:
    std::string nome_;
    std::string nome_usuario_;
    // Armazena ponteiros para os filmes (observador). Não é dono deles.
    std::vector<const Filme*> watchlist_;

public:
    Usuario(std::string nome, std::string nome_usuario);
    ~Usuario();

    std::string get_nome() const;
    std::string get_nome_usuario() const;

    // Recebe referência para const, garantindo a agregação
    void adicionar_watchlist(const Filme& filme);

    // Métodos com lógica real
    void exibir_watchlist() const;
    void exibir_perfil() const;
};

#endif 
