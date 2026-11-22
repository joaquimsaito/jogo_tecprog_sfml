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

            int pontos; // decidimos divergir do diagrama e colocar pontos como PRIVATE ao invés de PROTECTED

            void processarEntrada();

        public:
            Jogador();
            ~Jogador();

            void executar();
            void mover();

            void colidir(Inimigo* pIn);
            void sofrerDano();

            int getPontos() const { return pontos; }
            void somarPontos(const int valor) { pontos += valor; }

            void reiniciar(const sf::Vector2f& pos);
        };
    }
}
