#include "FasePrimeira.h"
#include <cstdlib>
#include "../Entidades/Zlurp.h"

namespace Fases {

    FasePrimeira::FasePrimeira() :
        Fase(),
        maxZlurps(4) {
        criarCenario();
    }

    FasePrimeira::~FasePrimeira() {
    }

    void FasePrimeira::criarInimMedios() {
        const int minimo = 3;
        const int quantidade = rand() % (maxZlurps - minimo + 1) + minimo;

        for (int i = 0; i < quantidade; i++) {
            Entidades::Personagens::Zlurp* pInim =
                new Entidades::Personagens::Zlurp(rand() % 5 + 1);

            if (rand() % 2 == 0)
                pInim->setDirecao(-1);
            else
                pInim->setDirecao(1);

            const float x = tamanhoMundo.x * (i + 0.5f) / quantidade;
            pInim->setPosicao(sf::Vector2f(x, 300.f)); // cai ate o chao

            lista_ents.incluir(pInim);
            GC.incluirInimigo(pInim);
        }
    }

    void FasePrimeira::criarInimigos() {
        criarInimFaceis();
        criarInimMedios();
    }

    void FasePrimeira::criarObstaculos() {
        criarPlataformas();
    }

}
