#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <limits>
#include "acervo/filme.hpp"
#include "acervo/serie.hpp"
#include "acervo/exibivel.hpp"
#include "avaliacao/avaliacao.hpp"
#include "avaliacao/lista_avaliacoes.hpp"
#include "usuario/usuario.hpp"

// ===================
// Funções de entrada
// ===================

void limpar_entrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int ler_inteiro(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limpar_entrada();
            return valor;
        }
        std::cout << "Entrada invalida. Digite um numero inteiro.\n";
        limpar_entrada();
    }
}

std::string ler_string(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);
    return valor;
}

// ============================================================
// Função livre — retorna o item com maior nota do acervo
// ============================================================

const ItemAcervo* maior_nota(const std::vector<std::unique_ptr<ItemAcervo>>& itens) {
    const ItemAcervo* maior = nullptr;
    float maior_valor = -1.0f;

    for (const auto& item : itens) {
        float nota = item->calcular_nota();
        if (nota > maior_valor) {
            maior_valor = nota;
            maior = item.get();
        }
    }
    return maior;
}

// ============================================================
// Função livre — exibe um objeto via interface exibivel
// ============================================================

void exibir_formatado(const Exibivel& obj) {
    std::cout << "  -> " << obj.formatar() << "\n";
}

// =========
// Submenus
// =========

void menu_acervo(std::vector<std::unique_ptr<ItemAcervo>>& acervo) {
    while (true) {
        std::cout << "\n--- Acervo ---\n";
        std::cout << "1. Adicionar Filme\n";
        std::cout << "2. Adicionar Serie\n";
        std::cout << "3. Listar todo o acervo\n";
        std::cout << "4. Ver item com maior nota\n";
        std::cout << "0. Voltar\n";

        int opcao = ler_inteiro("Opcao: ");

        switch (opcao) {
            case 1: {
                std::string nome = ler_string("Nome do filme: ");
                int ano = ler_inteiro("Ano: ");
                std::string genero = ler_string("Genero: ");
                int duracao = ler_inteiro("Duracao (minutos): ");
                acervo.push_back(std::make_unique<Filme>(nome, ano, genero, duracao));
                std::cout << "Filme adicionado com sucesso!\n";
                break;
            }
            case 2: {
                std::string nome = ler_string("Nome da serie: ");
                int ano = ler_inteiro("Ano: ");
                std::string genero = ler_string("Genero: ");
                int temporadas = ler_inteiro("Numero de temporadas: ");
                int eps = ler_inteiro("Episodios por temporada: ");
                acervo.push_back(std::make_unique<Serie>(nome, ano, genero, temporadas, eps));
                std::cout << "Serie adicionada com sucesso!\n";
                break;
            }
            case 3: {
                if (acervo.empty()) {
                    std::cout << "O acervo esta vazio. Adicione filmes ou series primeiro.\n";
                } else {
                    std::cout << "\n--- Acervo (" << acervo.size() << " itens) ---\n";
                    for (size_t i = 0; i < acervo.size(); ++i) {
                        std::cout << "[" << i + 1 << "] ";
                        acervo[i]->exibir_info();

                        // Se implementa Exibivel, mostra a versão formatada
                        const Exibivel* exib = dynamic_cast<const Exibivel*>(acervo[i].get());
                        if (exib) {
                            exibir_formatado(*exib);
                        }
                    }
                }
                break;
            }
            case 4: {
                if (acervo.empty()) {
                    std::cout << "O acervo esta vazio.\n";
                } else {
                    const ItemAcervo* melhor = maior_nota(acervo);
                    if (melhor) {
                        std::cout << "Melhor avaliado: " << melhor->get_nome()
                                  << " (nota: " << melhor->calcular_nota() << ")\n";
                    }
                }
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}

void menu_avaliacoes(ListaAvaliacoes& lista) {
    while (true) {
        std::cout << "\n--- Avaliacoes ---\n";
        std::cout << "1. Adicionar avaliacao\n";
        std::cout << "2. Exibir todas as avaliacoes\n";
        std::cout << "3. Ver media das notas\n";
        std::cout << "0. Voltar\n";

        int opcao = ler_inteiro("Opcao: ");

        switch (opcao) {
            case 1: {
                std::string nome_filme = ler_string("Nome do filme/serie: ");
                int nota;
                while (true) {
                    nota = ler_inteiro("Nota (1 a 5): ");
                    if (nota >= 1 && nota <= 5) break;
                    std::cout << "A nota deve ser entre 1 e 5.\n";
                }
                std::string comentario = ler_string("Comentario: ");
                lista.adicionar_avaliacao(nome_filme, nota, comentario);
                std::cout << "Avaliacao registrada!\n";
                break;
            }
            case 2:
                lista.exibir_todas();
                break;
            case 3: {
                float media = lista.calcular_media();
                if (media == 0.0f) {
                    std::cout << "Nenhuma avaliacao registrada ainda.\n";
                } else {
                    std::cout << "Media das notas: " << media << "/5\n";
                }
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}

void menu_usuario(std::vector<std::unique_ptr<ItemAcervo>>& acervo) {
    std::string nome = ler_string("Seu nome: ");
    std::string nome_usuario = ler_string("Seu username: ");
    Usuario usuario(nome, nome_usuario);

    while (true) {
        std::cout << "\n--- @" << usuario.get_nome_usuario() << " ---\n";
        std::cout << "1. Adicionar filme a watchlist\n";
        std::cout << "2. Exibir watchlist\n";
        std::cout << "3. Exibir perfil\n";
        std::cout << "0. Voltar\n";

        int opcao = ler_inteiro("Opcao: ");

        switch (opcao) {
            case 1: {
                std::vector<Filme*> filmes_disponiveis;
                for (const auto& item : acervo) {
                    Filme* f = dynamic_cast<Filme*>(item.get());
                    if (f) {
                        filmes_disponiveis.push_back(f);
                    }
                }

                if (filmes_disponiveis.empty()) {
                    std::cout << "Nenhum filme no acervo. Adicione filmes primeiro.\n";
                    break;
                }

                std::cout << "\nFilmes disponiveis:\n";
                for (size_t i = 0; i < filmes_disponiveis.size(); ++i) {
                    std::cout << "  [" << i + 1 << "] " << filmes_disponiveis[i]->formatar_info() << "\n";
                }

                int escolha = ler_inteiro("Escolha o numero do filme (0 para cancelar): ");
                if (escolha >= 1 && escolha <= static_cast<int>(filmes_disponiveis.size())) {
                    usuario.adicionar_watchlist(*filmes_disponiveis[escolha - 1]);
                } else if (escolha != 0) {
                    std::cout << "Opcao invalida.\n";
                }
                break;
            }
            case 2:
                usuario.exibir_watchlist();
                break;
            case 3:
                usuario.exibir_perfil();
                break;
            case 0:
                return;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}

// ======
//  main
// ======

int main() {
    std::cout << "========================================\n";
    std::cout << "             Letterboxd C++!       \n";
    std::cout << "========================================\n";

    std::vector<std::unique_ptr<ItemAcervo>> acervo;
    ListaAvaliacoes avaliacoes;

    while (true) {
        std::cout << "\n========== MENU PRINCIPAL ==========\n";
        std::cout << "1. Acervo (filmes e series)\n";
        std::cout << "2. Avaliacoes\n";
        std::cout << "3. Meu perfil e watchlist\n";
        std::cout << "0. Sair\n";
        std::cout << "====================================\n";

        int opcao = ler_inteiro("Opcao: ");

        switch (opcao) {
            case 1:
                menu_acervo(acervo);
                break;
            case 2:
                menu_avaliacoes(avaliacoes);
                break;
            case 3:
                menu_usuario(acervo);
                break;
            case 0:
                std::cout << "\nAte a proxima! :)\n";
                return 0;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}
