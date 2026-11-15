#pragma once

#include "Entidade.h"

namespace Entidades {
    namespace Personagens {
        class Jogador;
    }

    namespace Obstaculos {
        class Obstaculo : public Entidade {
        protected:
            bool danoso;

        public:
            Obstaculo(const bool pDanoso = false);
            virtual ~Obstaculo();

            virtual void executar() = 0;

            virtual void obstaculizar(Personagens::Jogador* pJ) = 0;

            const bool getDanoso() const { return danoso; }
        };
    }
}
