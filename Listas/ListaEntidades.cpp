#include "ListaEntidades.h"

namespace Listas {

    ListaEntidades::ListaEntidades() :
        LEs() {
    }

    ListaEntidades::~ListaEntidades() {
        limpar();
    }

    void ListaEntidades::incluir(Entidades::Entidade* pE) {
        if (pE)
            LEs.incluir(pE);
    }

    void ListaEntidades::remover(Entidades::Entidade* pE) {
        if (pE)
            LEs.remover(pE);
    }

    void ListaEntidades::executar() {
        Lista<Entidades::Entidade*>::Elemento* pAux = LEs.getPrimeiro();
        while (pAux) {
            Entidades::Entidade* pE = pAux->getInfo();
            if (pE)
                pE->executar();
            pAux = pAux->getProx();
        }
    }

    void ListaEntidades::desenhar() {
        Lista<Entidades::Entidade*>::Elemento* pAux = LEs.getPrimeiro();
        while (pAux) {
            Entidades::Entidade* pE = pAux->getInfo();
            if (pE)
                pE->desenhar();
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

}
