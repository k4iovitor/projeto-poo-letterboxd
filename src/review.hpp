#ifndef REVIEW_HPP
#define REVIEW_HPP

#include <string>

class Review {
private:
    std::string movie_name_;
    int rating_; // 1 a 5 estrelas
    std::string comment_;

public:
    Review(std::string movie_name, int rating, std::string comment);
    ~Review();

    std::string get_movie_name() const;
    int get_rating() const;
    std::string get_comment() const;

    // Métodos com lógica real
    bool validate_rating() const;
    std::string format_review() const;
};

#endif // REVIEW_HPP
