#include "Plataforma.h"

namespace Entidades {
    namespace Obstaculos {

        Plataforma::Plataforma(const sf::Vector2f& pos, const sf::Vector2f& tam) :
            Obstaculo(false) {
            corpo.setSize(tam);
            corpo.setFillColor(sf::Color(120, 120, 120));
            setPosicao(pos);
        }

        Plataforma::~Plataforma() {
        }

        void Plataforma::executar() {
        }

        void Plataforma::obstaculizar(Personagens::Jogador* pJ) {
            // a definir
        }

    }
}
