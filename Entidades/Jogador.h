#pragma once

#include "Personagem.h"

namespace Entidades {
    namespace Personagens {
        class Inimigo;

        class Jogador : public Personagem {
        private:
            static const int   VIDAS_INICIAIS;
            static const float VELOCIDADE;
            static const float FORCA_PULO;
            static const float TEMPO_INVULNERAVEL; // segundos

            float invulneravel; // segundos restantes apos tomar dano

            void processarEntrada();

        public:
            Jogador();
            ~Jogador();

            void executar();
            void mover();

            void colidir(Inimigo* pIn);
            void sofrerDano();

            const bool estaVivo() const;
            void reiniciar(const sf::Vector2f& pos);
        };
    }
}
