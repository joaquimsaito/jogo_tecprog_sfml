#include "ListaEntidades.h"

using namespace Listas;
using namespace Entidades;

ListaEntidades::ListaEntidades() {
}

ListaEntidades::~ListaEntidades() {
}

void ListaEntidades::executar() {
    Lista<Entidades::Entidade*>::Elemento* pAux = LEs.getPrimeiro();
    while (pAux) {
        pAux->getInfo()->executar();
        pAux = pAux->getProx();
    }
}

void ListaEntidades::desenhar() {
    auto pAux = LEs.getPrimeiro();

    while (pAux != nullptr) {
        Entidade* pEnt = pAux->getInfo();
        if (pEnt) {
            pEnt->desenhar();
        }
        pAux = pAux->getProx();
    }
}

void ListaEntidades::limpar() {
    Lista<Entidades::Entidade*>::Elemento* pAux = LEs.getPrimeiro();
    while (pAux) {
        Entidades::Entidade* pE = pAux->getInfo();
        delete pE;
        pAux = pAux->getProx();
    }
    LEs.limpar();
}