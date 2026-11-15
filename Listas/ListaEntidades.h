#pragma once
#include "Lista.h"
#include "../Entidades/Entidade.h"

namespace Entidades {
    class Entidade;
}

namespace Listas {

    class ListaEntidades {
    private:
        Lista<Entidades::Entidade*> LEs;
    public:
        ListaEntidades();
        ~ListaEntidades();
        void incluir(Entidades::Entidade* pE) { if (pE) LEs.incluir(pE); };
        void remover(Entidades::Entidade* pE) { if (pE) LEs.remover(pE); };
        void executar();
        void desenhar();
        void limpar();
    };
}

