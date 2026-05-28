#include "user.hpp"
#include <iostream>

User::User(std::string name, std::string username)
    : name_(name), username_(username) {
    std::cout << "User(" << username_ << ") criado\n";
}

User::~User() {
    std::cout << "~User(" << username_ << ") destruido. (Note que os filmes em sua watchlist não serão destruídos pelo usuário!)\n";
}

std::string User::get_name() const { return name_; }
std::string User::get_username() const { return username_; }

void User::add_to_watchlist(const Movie& movie) {
    // Guarda o ponteiro (agregando)
    watchlist_.push_back(&movie);
    std::cout << "Filme '" << movie.get_name() << "' adicionado a watchlist de " << username_ << "\n";
}

void User::display_watchlist() const {
    std::cout << "Watchlist de " << username_ << " (" << watchlist_.size() << " filmes):\n";
    for (const Movie* movie : watchlist_) {
        std::cout << " - " << movie->format_info() << "\n";
    }
}

void User::display_profile() const {
    std::cout << "=== Perfil: " << name_ << " (@" << username_ << ") ===\n";
    display_watchlist();
    std::cout << "==========================\n";
}
