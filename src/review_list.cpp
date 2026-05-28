#include "review_list.hpp"
#include <iostream>

ReviewList::ReviewList() {
    std::cout << "ReviewList criada\n";
}

ReviewList::~ReviewList() {
    std::cout << "~ReviewList destruida. Invocando destruicao de suas " << reviews_.size() << " reviews internas:\n";
    // unique_ptr destruirá automaticamente os Reviews aqui.
}

void ReviewList::add_review(std::string movie_name, int rating, std::string comment) {
    // Uso de unique_ptr (Q4) para garantir a composição e gerenciamento automático
    reviews_.push_back(std::make_unique<Review>(movie_name, rating, comment));
}

float ReviewList::calculate_average() const {
    if (reviews_.empty()) {
        return 0.0f;
    }
    
    int sum = 0;
    for (const auto& review : reviews_) {
        sum += review->get_rating();
    }
    
    return static_cast<float>(sum) / reviews_.size();
}

void ReviewList::display_all() const {
    std::cout << "--- Lista de Avaliacoes ---\n";
    for (const auto& review : reviews_) {
        std::cout << review->format_review() << "\n";
    }
    std::cout << "---------------------------\n";
}
