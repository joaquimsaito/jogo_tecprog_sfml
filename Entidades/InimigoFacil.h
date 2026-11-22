#pragma once

#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
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
