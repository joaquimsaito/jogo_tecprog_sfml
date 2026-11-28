#pragma once

#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
        class Bog : public Inimigo {
        public:
            Bog(const int nivelMaldade = 1);
            ~Bog();

            void executar();
            void mover();
            void danificar(Jogador* pJ);
        };
    }
}
