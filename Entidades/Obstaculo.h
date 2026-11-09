#pragma once

#include "Entidade.h"

namespace Entidades {
    namespace Personagens {
        class Jogador;
    }

    namespace Obstaculos {
        class Obstaculo : public Entidade {
        public:
            Obstaculo() : Entidade() {}
            ~Obstaculo() override = default;

            void executar() override = 0;
            virtual void obstacularizar(Personagens::Jogador* pJ) = 0;
        };
    }
}
