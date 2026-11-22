#pragma once

#include <SFML/Graphics.hpp>
#include "../Ente.h"

namespace Entidades {
    class Entidade : public Ente {
    protected:
        sf::RectangleShape corpo; // provisorio: sera substituido por sprite
        sf::Vector2f posicao;

        void setCorpo(const sf::RectangleShape& c) {
            corpo = c;
            setPosicao(c.getPosition());
        }
    public:
        Entidade();
        virtual ~Entidade();

        void setPosicao(const sf::Vector2f& p) {
            posicao = p;
            corpo.setPosition(posicao);
        }

        const sf::RectangleShape& getCorpo() const { return corpo; }
        const sf::Vector2f getPosicao() const { return posicao; }
        const sf::Vector2f getTamanho() const { return corpo.getSize(); }

        virtual void executar() = 0;
    };
}
