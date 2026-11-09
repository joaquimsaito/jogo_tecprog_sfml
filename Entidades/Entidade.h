#pragma once

#include "../Ente.h"

namespace Entidades {
    class Entidade : public Ente {
    protected:
        sf::RectangleShape corpo;
        sf::Vector2f posicao;

    public:
        Entidade();
        virtual ~Entidade() = default;

        void setCorpo(const sf::RectangleShape& c) {
            corpo = c;
            setPosicao(c.getPosition());
        }

        void setPosicao(const sf::Vector2f& p) {
            posicao = p;
            corpo.setPosition(posicao);
        }

        const sf::RectangleShape& getCorpo() const { return corpo; }
        const sf::Vector2f getPosicao() const { return posicao; }

        virtual void executar() = 0;
    };
}
