#include "movie.hpp"
#include <iostream>

Movie::Movie(std::string name, int year, std::string genre, int duration)
    : name_(name), year_(year), genre_(genre), duration_minutes_(duration) {
    std::cout << "Movie(" << name_ << ") criado\n";
}

Movie::~Movie() {
    std::cout << "~Movie(" << name_ << ") destruido\n";
}

std::string Movie::get_name() const { return name_; }
int Movie::get_year() const { return year_; }
std::string Movie::get_genre() const { return genre_; }
int Movie::get_duration_minutes() const { return duration_minutes_; }

std::string Movie::format_info() const {
    // Lógica real: formata horas e minutos
    int hours = duration_minutes_ / 60;
    int minutes = duration_minutes_ % 60;
    
    std::string time_str = std::to_string(hours) + "h ";
    if (minutes > 0) {
        time_str += std::to_string(minutes) + "m";
    }
    
    return name_ + " (" + std::to_string(year_) + ") - " + genre_ + " - " + time_str;
}
