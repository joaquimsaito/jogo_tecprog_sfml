#include "InimigoFacil.h"
#include "Jogador.h"

namespace Entidades {
    namespace Personagens {

        InimigoFacil::InimigoFacil() :
            Inimigo(1) {
            corpo.setSize(sf::Vector2f(40.f, 40.f));
            corpo.setFillColor(sf::Color(220, 30, 30));
            setVelocidadeMaxima(sf::Vector2f(0.f, 900.f));
        }

        InimigoFacil::~InimigoFacil() {
        }

        void InimigoFacil::executar() {
            mover();
        }

        void InimigoFacil::mover() {
            // Parado por enquanto
            velocidade.x = 0.f;
            integrar();
        }

        void InimigoFacil::danificar(Jogador* pJ) {
            if (pJ)
                pJ->sofrerDano();
        }

    }
}
