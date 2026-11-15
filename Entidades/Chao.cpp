#include "Chao.h"

namespace Entidades {
    Chao::Chao(const sf::Vector2f& pos, const sf::Vector2f& tam) :
        Entidade() {
        corpo.setSize(tam);
        corpo.setFillColor(sf::Color(110, 80, 50));
        setPosicao(pos);
    }

    Chao::~Chao() {
    }

    void Chao::executar() {
        // O chao e estatico; nao precisa atualizar sua posicao.
    }
}
