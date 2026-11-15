#pragma once

#include "Lista.h"
#include "../Entidades/Entidade.h"

namespace Listas {

    // a ListaEntidades POSSUI as entidades incluidas
    class ListaEntidades {
    private:
        Lista<Entidades::Entidade*> LEs;

        ListaEntidades(const ListaEntidades&);
        ListaEntidades& operator=(const ListaEntidades&);

    public:
        ListaEntidades();
        ~ListaEntidades();

        void incluir(Entidades::Entidade* pE);
        void remover(Entidades::Entidade* pE); // retira da lista SEM deletar
        void executar();
        void desenhar();
        void limpar(); // retira e DELETA todas
    };
}
