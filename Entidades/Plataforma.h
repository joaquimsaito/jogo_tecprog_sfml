#pragma once

#include "Obstaculo.h"

namespace Entidades {
    namespace Obstaculos {
        class Plataforma : public Obstaculo {
        private:
            int altura;

        public:
            Plataforma(
                const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f),
                const sf::Vector2f& tam = sf::Vector2f(100.f, 20.f)
            );
            ~Plataforma() override = default;

            void executar() override;
            void obstacularizar(Personagens::Jogador* pJ) override;
        };
    }
}