#pragma once

#include "Personagem.h"

namespace Entidades {
    namespace Personagens {
        class Inimigo;

        class Jogador : public Personagem {
        private:
            float invulneravel; // segundos restantes apos tomar dano

            int pontos; // decidimos divergir do diagrama e colocar pontos como PRIVATE ao invés de PROTECTED
            // NOVO: impulso horizontal do empurrao de Zlurp::danificar ("empurra pra tras"); processarEntrada() zera velocidade.x todo quadro e anularia o empurrao
            float impulsoX;

            void processarEntrada();

        public:
            Jogador();
            ~Jogador();

            const int getPontos() const;

            void executar();
            void mover();

            // NOVO: decide pisao (neutraliza/pontua) ou dano; o Gerenciador_Colisoes so detecta e delega (colisao dividida entre colidir, danificar e obstaculizar).
            void colidir(Inimigo* pIn);
            // NOVO: dano e empurrao parametrizados (Bog tira 1 vida; Zlurp tira 2 e empurra) em vez de atributos extras.
            void sofrerDano(const int dano = 1, const float empurrao = 0.f);

            void reiniciar(const sf::Vector2f& pos);
            // NOVO: pontos por operadores (+1 ao neutralizar, -1 ao tomar dano); substitui somarPontos().
            void operator++() { pontos++; };
            void operator--() { pontos--; };
        };
    }
}
