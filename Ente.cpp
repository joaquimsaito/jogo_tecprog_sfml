#include "Ente.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

int Ente::contadorId = 0;
Gerenciadores::Gerenciador_Grafico* Ente::pGG = nullptr;

Ente::Ente() :
    id(contadorId++),
    pFig(nullptr) {
}

Ente::~Ente() {
    pFig = nullptr;
}

void Ente::desenhar() {
    if (pGG)
        pGG->desenharEnte(this);
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG) {
    pGG = pG;
}

sf::Drawable* Ente::getFigura() const {
    return pFig;
}

int Ente::getId() const {
    return id;
}
