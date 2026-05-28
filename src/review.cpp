#include "review.hpp"
#include <iostream>

Review::Review(std::string movie_name, int rating, std::string comment)
    : movie_name_(movie_name), rating_(rating), comment_(comment) {
    std::cout << "Review do filme '" << movie_name_ << "' criado com nota " << rating_ << "\n";
}

Review::~Review() {
    std::cout << "~Review do filme '" << movie_name_ << "' destruido\n";
}

std::string Review::get_movie_name() const { return movie_name_; }
int Review::get_rating() const { return rating_; }
std::string Review::get_comment() const { return comment_; }

bool Review::validate_rating() const {
    return rating_ >= 1 && rating_ <= 5;
}

std::string Review::format_review() const {
    std::string stars(rating_, '*');
    std::string empty_stars(5 - rating_, '-');
    return movie_name_ + " [" + stars + empty_stars + "] : " + comment_;
}
