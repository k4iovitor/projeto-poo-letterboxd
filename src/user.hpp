#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "movie.hpp"

// User tem uma Watchlist (Agregação de Movie)
class User {
private:
    std::string name_;
    std::string username_;
    // Armazena ponteiros para os filmes (observador). Não é dono deles.
    std::vector<const Movie*> watchlist_;

public:
    User(std::string name, std::string username);
    ~User();

    std::string get_name() const;
    std::string get_username() const;

    // Recebe referência para const, garantindo a agregação
    void add_to_watchlist(const Movie& movie);
    
    // Métodos com lógica real
    void display_watchlist() const;
    void display_profile() const;
};

#endif // USER_HPP
