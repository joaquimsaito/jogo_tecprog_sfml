#pragma once

#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
        class InimigoFacil : public Inimigo {
        private:
            static const float VEL_BASE;
            static const float PASSO; //ambos atributos pra velocidade do inimigo variar com base no nivel da maldade
        public:
            InimigoFacil(const int nivelMaldade = 1);
            ~InimigoFacil();

            void executar();
            void mover();
            void danificar(Jogador* pJ);
        };
    }
}