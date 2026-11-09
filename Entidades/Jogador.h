#pragma once

#include "Personagem.h"

namespace Entidades {
    namespace Personagens {
        class Jogador : public Personagem {
        private:
            float forcaPulo;

        public:
            Jogador();
            ~Jogador() override = default;

            void executar() override;
            void mover() override;
            void procesarEntrada();
        };
    }
}
