#pragma once

#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
        // Inimigo 1 - Facil: por enquanto fica PARADO (so sofre gravidade).
        class InimigoFacil : public Inimigo {
        public:
            InimigoFacil();
            ~InimigoFacil();

            void executar();
            void mover();
            void danificar(Jogador* pJ);
        };
    }
}
