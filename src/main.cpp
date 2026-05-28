#include <iostream>
#include "movie.hpp"
#include "review.hpp"
#include "review_list.hpp"
#include "user.hpp"

void test_composition() {
    std::cout << "\n--- Teste 5: Composicao (Ciclo de Vida) ---\n";
    {
        ReviewList list;
        list.add_review("O Auto da Compadecida", 5, "Obra prima do cinema nacional.");
        list.add_review("Tropa de Elite", 4, "Filme de acao muito bom.");
        
        std::cout << "A media das avaliacoes e: " << list.calculate_average() << "\n";
        list.display_all();
        std::cout << "Saindo do escopo do ReviewList...\n";
    } // Aqui a lista e destruida, invocando o destrutor de cada review internamente.
    std::cout << "Fora do bloco.\n";
}

void test_aggregation() {
    std::cout << "\n--- Teste 6: Agregacao (Independencia) ---\n";
    // Filmes existem independentemente do usuário.
    Movie m1("Cidade de Deus", 2002, "Drama/Crime", 130);
    Movie m2("Central do Brasil", 1998, "Drama", 113);
    
    {
        User u1("Kaio", "k4iovitor");
        u1.add_to_watchlist(m1);
        u1.add_to_watchlist(m2);
        u1.display_profile();
        std::cout << "Saindo do escopo do User...\n";
    } // O User é destruído, mas os filmes permanecem.
    
    std::cout << "Fora do bloco do User. Filmes ainda existem:\n";
    std::cout << m1.format_info() << "\n";
    std::cout << m2.format_info() << "\n";
}

int main() {
    std::cout << "Iniciando sistema Letterboxd...\n";
    
    test_composition();
    test_aggregation();
    
    std::cout << "\nFim da execucao.\n";
    return 0;
}
