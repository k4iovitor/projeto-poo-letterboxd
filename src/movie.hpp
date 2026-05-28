#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>

class Movie {
private:
    std::string name_;
    int year_;
    std::string genre_;
    int duration_minutes_;

public:
    Movie(std::string name, int year, std::string genre, int duration);
    ~Movie();

    // Getters const
    std::string get_name() const;
    int get_year() const;
    std::string get_genre() const;
    int get_duration_minutes() const;

    // Método com lógica real
    std::string format_info() const;
};

#endif // MOVIE_HPP
