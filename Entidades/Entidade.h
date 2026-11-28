#pragma once

#include <SFML/Graphics.hpp>
#include "../Ente.h"

namespace Entidades {
    class Entidade : public Ente {
    protected:
        sf::RectangleShape corpo; // provisorio: sera substituido por sprite
        sf::Vector2f posicao;

        void setCorpo(const sf::RectangleShape& c);
    public:
        Entidade();
        virtual ~Entidade();

        void setPosicao(const sf::Vector2f& p);

        const sf::RectangleShape& getCorpo() const;
        const sf::Vector2f getPosicao() const;
        const sf::Vector2f getTamanho() const;

        virtual void executar() = 0;
    };
}
