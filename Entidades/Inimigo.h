#pragma once

#include "Personagem.h"

namespace Entidades {
    namespace Personagens {
        class Jogador;

        class Inimigo : public Personagem {
        protected:
            int nivel_maldade;

        public:
            Inimigo(const int nivelMaldade = 1, const int vidas = 1);
            virtual ~Inimigo();

            virtual void executar() = 0;
            virtual void mover() = 0;
            virtual void danificar(Jogador* pJ) = 0;
            void neutralizar();

            const int getNivelMaldade() const { return nivel_maldade; }
        };
    }
}
