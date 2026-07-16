# Letterboxd em C++

**Nome:** Kaio Vitor
**Matrícula:** 20250019634

## Domínio Escolhido
Este projeto é uma versão simplificada do Letterboxd, uma rede social focada em cinema. O sistema permite representar filmes, séries, avaliações dadas a esses itens, coleções de avaliações, e usuários que podem manter uma lista de filmes que desejam assistir (Watchlist).

## Estrutura do Projeto

```
src/
├── main.cpp                          # Ponto de entrada com demonstrações
├── acervo/                           # Hierarquia de herança (filmes, séries)
│   ├── item_acervo.hpp / .cpp        # Classe base abstrata
│   ├── exibivel.hpp                  # Interface pura
│   ├── filme.hpp / .cpp              # Classe concreta (herda ItemAcervo + Exibivel)
│   └── serie.hpp / .cpp              # Classe concreta final (herda ItemAcervo)
├── avaliacao/                        # Sistema de avaliações
│   ├── avaliacao.hpp / .cpp          # Avaliação individual
│   └── lista_avaliacoes.hpp / .cpp   # Composição de avaliações
└── usuario/                          # Gestão de usuários
    └── usuario.hpp / .cpp            # Usuário com watchlist
```

## Diagrama UML

```mermaid
classDiagram
    class ItemAcervo {
        <<abstract>>
        #string nome_
        #int ano_
        #string genero_
        +ItemAcervo(string nome, int ano, string genero)
        +~ItemAcervo()* virtual
        +calcular_nota()* float
        +exibir_info() void
        +get_nome() string
        +get_ano() int
        +get_genero() string
    }

    class Exibivel {
        <<interface>>
        +formatar()* string
        +~Exibivel()* virtual
    }

    class Filme {
        -int duracao_minutos_
        +Filme(string nome, int ano, string genero, int duracao)
        +~Filme()
        +calcular_nota() float
        +exibir_info() void
        +formatar() string
        +formatar_info() string
        +get_duracao_minutos() int
    }

    class Serie {
        <<final>>
        -int temporadas_
        -int episodios_por_temporada_
        +Serie(string nome, int ano, string genero, int temporadas, int eps)
        +~Serie()
        +calcular_nota() float
        +exibir_info() void
        +get_temporadas() int
        +get_episodios_por_temporada() int
        +get_total_episodios() int
    }

    class Avaliacao {
        -string nome_filme_
        -int nota_
        -string comentario_
        +Avaliacao(string nome_filme, int nota, string comentario)
        +~Avaliacao()
        +get_nome_filme() string
        +get_nota() int
        +get_comentario() string
        +validar_nota() bool
        +formatar_avaliacao() string
    }

    class ListaAvaliacoes {
        -vector~unique_ptr~Avaliacao~~ avaliacoes_
        +ListaAvaliacoes()
        +~ListaAvaliacoes()
        +adicionar_avaliacao(string nome_filme, int nota, string comentario) void
        +calcular_media() float
        +exibir_todas() void
    }

    class Usuario {
        -string nome_
        -string nome_usuario_
        -vector~const Filme*~ watchlist_
        +Usuario(string nome, string nome_usuario)
        +~Usuario()
        +get_nome() string
        +get_nome_usuario() string
        +adicionar_watchlist(const Filme& filme) void
        +exibir_watchlist() void
        +exibir_perfil() void
    }

    ItemAcervo <|-- Filme : herança (▷)
    ItemAcervo <|-- Serie : herança (▷)
    Exibivel <|.. Filme : implementa
    ListaAvaliacoes "1" *-- "0..*" Avaliacao : Composição (◆)
    Usuario "0..*" o-- "0..*" Filme : Agregação (◇)
```

## Relações de Composição e Agregação

*   **Composição (◆)**: `ListaAvaliacoes` *-- `Avaliacao`. A `ListaAvaliacoes` cria e possui as `Avaliacao`s. Quando uma `ListaAvaliacoes` é destruída, todas as suas avaliações internas também são destruídas junto com ela. Uma avaliação não faz sentido neste sistema sem estar vinculada à lista que a armazena.
*   **Agregação (◇)**: `Usuario` o-- `Filme`. O `Usuario` mantém uma lista de ponteiros para objetos `Filme` (sua watchlist). Os filmes existem independentemente do usuário e continuarão a existir no sistema caso o usuário seja excluído. Portanto, a destruição de um `Usuario` não causa a destruição dos `Filme`s que ele referenciou.

## Smart Pointers

*   **`unique_ptr<Avaliacao>` (Composição `ListaAvaliacoes` -> `Avaliacao`)**: Usado na classe `ListaAvaliacoes` para gerenciar as instâncias de `Avaliacao`. Como é uma composição de posse estrita (ownership único), o `unique_ptr` é perfeito para garantir que as avaliações sejam destruídas automaticamente quando a lista for destruída.
*   **`const Filme*` / `const Filme&` (Agregação `Usuario` -> `Filme`)**: Empregamos raw pointers não-proprietários (observadores) para representar a associação de agregação, indicando que o usuário apenas referencia o filme e não gerencia seu tempo de vida (ele é "emprestado"). *(Nota: o uso de referências ou ponteiros raw não-donos é idiomático em C++ moderno para relações de não-posse em oposição a shared_ptr desnecessários).*

## Hierarquia de Herança

O projeto utiliza a hierarquia:

```
ItemAcervo (abstrata) ──▷── Filme (concreta)
                       ──▷── Serie (concreta, final)
```

*   **`ItemAcervo`** — Classe base abstrata que representa qualquer item do acervo cinematográfico. Possui:
    *   `calcular_nota()` — método **virtual puro** (`= 0`), obrigando cada derivada a implementar seu próprio cálculo de nota.
    *   `exibir_info()` — método **virtual não-puro** com implementação padrão que exibe nome, ano e gênero.
    *   `~ItemAcervo()` — **destrutor virtual** que garante a destruição correta da cadeia derivada → base.
*   **`Filme`** — Classe concreta que herda de `ItemAcervo`. Sobrescreve `calcular_nota()` (nota baseada na duração) e `exibir_info()` (chamando `ItemAcervo::exibir_info()` antes de complementar).
*   **`Serie`** — Classe concreta `final` que herda de `ItemAcervo`. Sobrescreve `calcular_nota()` (nota baseada em temporadas) e `exibir_info()` (chamando `ItemAcervo::exibir_info()` antes de complementar).

## Herança Avançada

### Interface Pura: `Exibivel`

A interface `Exibivel` modela a **capacidade** de um objeto ser exibido em formato textual. Ela não possui nenhum atributo de dados (sem estado) e todos os seus métodos são virtuais puros:
*   `formatar() const = 0` — retorna uma representação formatada do objeto como `std::string`.

A classe `Filme` implementa `Exibivel` através de **herança múltipla de interfaces** (`Filme : public ItemAcervo, public Exibivel`). Isso é seguro pois `Exibivel` não possui estado, evitando o problema do diamante.

### Uso de `final`

A classe `Serie` é marcada como `final`, o que significa que **ninguém pode herdar dela**. Essa decisão de design garante que:
1.  A implementação de `calcular_nota()` específica de séries de TV não será alterada por subclasses inesperadas.
2.  O compilador pode otimizar chamadas virtuais em `Serie` pois sabe que não há derivadas.
3.  Preserva a integridade do modelo: no domínio Letterboxd, uma "Série" é um conceito final — não faz sentido ter subtipos de séries.
