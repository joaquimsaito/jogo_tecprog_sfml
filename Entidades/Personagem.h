#pragma once

#include "Entidade.h"

namespace Entidades {
    namespace Personagens {
        class Personagem : public Entidade {
        protected:
            sf::Vector2f velocidade;
            sf::Vector2f aceleracao;
            sf::Vector2f velocidadeMaxima;
            float gravidade;
            bool noChao;

            void aplicaGravidade();

        public:
            Personagem();
            virtual ~Personagem() = default;

            const sf::Vector2f getVelocidade() const { return velocidade; }
            const sf::Vector2f getVelocidadeMaxima() const { return velocidadeMaxima; }
            const float getGravidade() const { return gravidade; }
            const bool getNoChao() const { return noChao; }

            void setVelocidade(const sf::Vector2f& v) { velocidade = v; }
            void setAceleracao(const sf::Vector2f& a) { aceleracao = a; }
            void setVelocidadeMaxima(const sf::Vector2f& vm) { velocidadeMaxima = vm; }
            void setGravidade(float g) { gravidade = g; }
            void setNoChao(bool c) { noChao = c; }

            virtual void executar() = 0;
            virtual void mover() = 0;
        };
    }
}
