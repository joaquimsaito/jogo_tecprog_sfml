#pragma once

#include "Entidade.h"

namespace Entidades {
    class Chao : public Entidade {
    public:
        Chao(const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f), const sf::Vector2f& tam = sf::Vector2f(100.f, 20.f));
        ~Chao();
        void executar();
    };
}
