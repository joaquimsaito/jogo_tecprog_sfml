#pragma once

#include "Obstaculo.h"

namespace Entidades {
    namespace Obstaculos {
        class Plataforma : public Obstaculo {
        public:
            Plataforma(
                const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f),
                const sf::Vector2f& tam = sf::Vector2f(100.f, 20.f)
            );
            ~Plataforma();

            void executar();
            void obstaculizar(Personagens::Jogador* pJ);
        };
    }
}
