#pragma once

#include "Lista.h"

namespace Entidades { class Entidade; }

namespace Listas {
    // a ListaEntidades POSSUI as entidades incluidas (a Fase eh dona das entidades, exceto o Jogador, que eh do Jogo)
    class ListaEntidades {
    private:
        Listas::Lista<Entidades::Entidade> LEs;
    public:
        ListaEntidades();
        ~ListaEntidades();

        void incluir(Entidades::Entidade* pE);
        void executar();
        // NOVO: Fase::executar() desenha depois de resolver as colisoes (a entidade nao se desenha dentro de executar()).
        void desenhar();
        void limpar(); // destroi todas as entidades e esvazia a lista
    };
}
