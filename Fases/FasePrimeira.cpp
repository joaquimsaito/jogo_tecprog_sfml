#include "FasePrimeira.h"

namespace Fases {

    FasePrimeira::FasePrimeira() :
        Fase() {
        criarCenario();
    }

    FasePrimeira::~FasePrimeira() {
    }

    void FasePrimeira::criarInimigos() {
        criarInimFaceis();
    }

    void FasePrimeira::criarObstaculos() {
        criarPlataformas();
    }

}
