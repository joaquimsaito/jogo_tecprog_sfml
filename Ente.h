#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace Gerenciadores {
    class Gerenciador_Grafico;
}

class Ente {
private:
    static int contadorId;

    //ponteiro pra figura da classe derivada (declarada e n definida)
    Ente(const Ente&);
    Ente& operator=(const Ente&);

protected:
    int id;
    static Gerenciadores::Gerenciador_Grafico* pGG;
    sf::Drawable* pFig;

public:
    Ente();
    virtual ~Ente();

    void desenhar();
    static void setGG(Gerenciadores::Gerenciador_Grafico* pG);

    sf::Drawable* getFigura() const; //utilitario
    int getId() const;

    virtual void executar() = 0;
};
