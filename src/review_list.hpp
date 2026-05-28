#ifndef REVIEW_LIST_HPP
#define REVIEW_LIST_HPP

#include <vector>
#include <memory>
#include "review.hpp"

// ReviewList gerencia as instâncias de Review (Composição)
class ReviewList {
private:
    std::vector<std::unique_ptr<Review>> reviews_;

public:
    ReviewList();
    ~ReviewList();

    // Cria a review e adiciona internamente (demonstração de composição estrita)
    void add_review(std::string movie_name, int rating, std::string comment);
    
    // Métodos com lógica real
    float calculate_average() const;
    void display_all() const;
};

#endif // REVIEW_LIST_HPP
