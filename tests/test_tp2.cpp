#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

#include "acervo/item_acervo.hpp"
#include "acervo/filme.hpp"
#include "acervo/serie.hpp"
#include "acervo/exibivel.hpp"

// ============================================================
// TEST_CASE 1: Destruição em cadeia
// Verifica que a cadeia destrutor-derivada → destrutor-base
// é executada na ordem correta.
// ============================================================
TEST_CASE("Cadeia de destruicao derivada -> base", "[hierarquia]") {
    // Redireciona cout para capturar a saída dos destrutores
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    SECTION("Filme: ~Filme antes de ~ItemAcervo") {
        {
            ItemAcervo* item = new Filme("TesteFilme", 2020, "Acao", 120);
            delete item;
        }

        std::cout.rdbuf(old);
        std::string saida = buffer.str();

        // Verifica que o destrutor da derivada aparece ANTES do da base
        size_t pos_filme = saida.find("~Filme(TesteFilme)");
        size_t pos_base  = saida.find("~ItemAcervo(TesteFilme)");

        REQUIRE(pos_filme != std::string::npos);
        REQUIRE(pos_base  != std::string::npos);
        REQUIRE(pos_filme < pos_base);
    }

    SECTION("Serie: ~Serie antes de ~ItemAcervo") {
        {
            ItemAcervo* item = new Serie("TesteSerie", 2021, "Drama", 3, 10);
            delete item;
        }

        std::cout.rdbuf(old);
        std::string saida = buffer.str();

        size_t pos_serie = saida.find("~Serie(TesteSerie)");
        size_t pos_base  = saida.find("~ItemAcervo(TesteSerie)");

        REQUIRE(pos_serie != std::string::npos);
        REQUIRE(pos_base  != std::string::npos);
        REQUIRE(pos_serie < pos_base);
    }
}

// ============================================================
// TEST_CASE 2: Polimorfismo dinâmico
// Cria derivadas via unique_ptr<Base>, chama calcular_nota()
// e verifica que cada derivada retorna o valor correto.
// ============================================================
TEST_CASE("Polimorfismo dinamico com calcular_nota()", "[polimorfismo]") {
    // Silencia construtores/destrutores
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    std::vector<std::unique_ptr<ItemAcervo>> acervo;

    // Filme com 120min (entre 90-150 → nota = 8.0 + (120-90)/60 = 8.5)
    acervo.push_back(std::make_unique<Filme>("Filme1", 2020, "Acao", 120));
    // Filme com 60min (fora da faixa → nota = 6.0)
    acervo.push_back(std::make_unique<Filme>("Filme2", 2019, "Curta", 60));
    // Serie com 5 temporadas (nota = 5.0 + 5*0.5 = 7.5)
    acervo.push_back(std::make_unique<Serie>("Serie1", 2018, "Drama", 5, 10));
    // Serie com 1 temporada (nota = 5.0 + 1*0.5 = 5.5)
    acervo.push_back(std::make_unique<Serie>("Serie2", 2021, "Suspense", 1, 8));

    std::cout.rdbuf(old);

    // Verificações polimórficas — cada tipo calcula nota de forma diferente
    REQUIRE(acervo[0]->calcular_nota() == Catch::Approx(8.5f));
    REQUIRE(acervo[1]->calcular_nota() == Catch::Approx(6.0f));
    REQUIRE(acervo[2]->calcular_nota() == Catch::Approx(7.5f));
    REQUIRE(acervo[3]->calcular_nota() == Catch::Approx(5.5f));

    // Verifica que tipos diferentes retornam valores diferentes
    REQUIRE(acervo[0]->calcular_nota() != acervo[1]->calcular_nota());
    REQUIRE(acervo[2]->calcular_nota() != acervo[3]->calcular_nota());

    // Silencia destrutores
    old = std::cout.rdbuf(buffer.rdbuf());
    acervo.clear();
    std::cout.rdbuf(old);
}

// ============================================================
// TEST_CASE 3: Interface pura Exibivel
// Cria objeto que implementa a interface, passa por referência
// de interface, verifica o resultado de formatar().
// ============================================================
TEST_CASE("Q3: Interface pura Exibivel via referencia", "[interface]") {
    // Silencia construtores
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    Filme filme("TesteInterface", 2023, "Ficcao", 140);

    std::cout.rdbuf(old);

    // Função lambda que recebe a interface pura por referência
    // — não sabe o tipo concreto, apenas que é Exibivel
    auto usar_exibivel = [](const Exibivel& obj) -> std::string {
        return obj.formatar();
    };

    // Chama via interface
    std::string resultado = usar_exibivel(filme);

    // Verifica que o resultado não é vazio e contém informações do filme
    REQUIRE(!resultado.empty());
    REQUIRE(resultado.find("TesteInterface") != std::string::npos);
    REQUIRE(resultado.find("2023") != std::string::npos);
    REQUIRE(resultado.find("Ficcao") != std::string::npos);
    REQUIRE(resultado.find("Filme") != std::string::npos);

    // Silencia destrutores
    old = std::cout.rdbuf(buffer.rdbuf());
}
