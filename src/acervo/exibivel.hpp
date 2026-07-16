#ifndef EXIBIVEL_HPP
#define EXIBIVEL_HPP

#include <string>

// Interface pura: modela a CAPACIDADE de ser exibido formatado.
// Sem estado (nenhum atributo), todos os métodos são puros virtuais.
// Qualquer classe pode implementar este contrato independentemente da hierarquia.
class Exibivel {
public:
    // Método puro — retorna representação formatada do objeto
    virtual std::string formatar() const = 0;

    // Destrutor virtual
    virtual ~Exibivel() = default;
};

#endif
