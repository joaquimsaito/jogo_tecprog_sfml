#pragma once

#include "Fase.h"

namespace Fases {

    class FasePrimeira : public Fase {
    private:
        const int maxZlurps;

    protected:
        void criarInimMedios();
        void criarInimigos();
        void criarObstaculos();

    public:
        FasePrimeira();
        ~FasePrimeira();
    };
}
