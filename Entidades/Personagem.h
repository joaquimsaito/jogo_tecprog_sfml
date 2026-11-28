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
            // NOVO: fator aplicado a velocidade.x so no quadro em que toca a Gelatina (comentario de Gelatina: "atrito que diminui a velocidade"); volta a 1 apos integrar()
            float fatorAtrito;

            void setAceleracao(const sf::Vector2f& a);
            void setVelocidadeMaxima(const sf::Vector2f& vm);

            // soma aceleracao + gravidade a velocidade e integra a posicao (usa o dt do jogo)
            void integrar();

        public:
            Personagem(const int vidas = 1);
            virtual ~Personagem();

            void setVelocidade(const sf::Vector2f& v);
            void setNoChao(const bool c);
            // NOVO: Gelatina::obstaculizar() reduz a velocidade sem acessar atributos protegidos (substitui Jogador::reduzirVelocidade).
            void setFatorAtrito(const float f);

            const int getNumVidas() const;
            const sf::Vector2f getVelocidade() const;
            const sf::Vector2f getVelocidadeMaxima() const;
            const bool getNoChao() const;
            const bool estaVivo() const;

            virtual void executar() = 0;
            virtual void mover() = 0;
        };
    }
}
