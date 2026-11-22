#pragma once

#include "Entidade.h"

namespace Entidades {
    namespace Personagens {
        class Personagem : public Entidade {
        public:
            static const float GRAVIDADE; //gravidade unica

        protected:
            int num_vidas;
            sf::Vector2f velocidade;
            sf::Vector2f aceleracao;
            sf::Vector2f velocidadeMaxima;
            bool noChao;

            // soma aceleracao + gravidade a velocidade e integra a posicao (usa o dt do jogo)
            void integrar();
            void setAceleracao(const sf::Vector2f& a) { aceleracao = a; }
            void setVelocidadeMaxima(const sf::Vector2f& vm) { velocidadeMaxima = vm; }

        public:
            Personagem(const int vidas = 1);
            virtual ~Personagem();

            const sf::Vector2f getVelocidade() const { return velocidade; }
            const sf::Vector2f getVelocidadeMaxima() const { return velocidadeMaxima; }
            const bool getNoChao() const { return noChao; }
            const int getNumVidas() const { return num_vidas; }
            const bool estaVivo() const { return num_vidas > 0; }

            void setVelocidade(const sf::Vector2f& v) { velocidade = v; }
            void setNoChao(const bool c) { noChao = c; }

            virtual void executar() = 0;
            virtual void mover() = 0;
        };
    }
}