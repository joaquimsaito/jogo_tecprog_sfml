#pragma once

#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
        class Zlurp : public Inimigo {
        private:
            int tamanho;
            float tempoParado;
            // NOVO: comentario do Zlurp - "nivel maldade influencia no intervalo de pulos"; substitui INTERVALO_PULO estatico.
            float intervaloPulo;

        public:
            Zlurp(const int nivelMaldade = 1);
            ~Zlurp();

            void executar();
            void mover();
            void danificar(Jogador* pJ);
        };
    }
}
