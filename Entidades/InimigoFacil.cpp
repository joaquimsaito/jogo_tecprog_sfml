#include "InimigoFacil.h"
#include "Jogador.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"

namespace Entidades {
    namespace Personagens {

        InimigoFacil::InimigoFacil() :
            Inimigo(1, 3) {
            corpo.setSize(sf::Vector2f(40.f, 40.f));
            corpo.setFillColor(sf::Color(220, 30, 30));
            setVelocidadeMaxima(sf::Vector2f(150.f, 900.f));
        }

        InimigoFacil::~InimigoFacil() {
        }

        void InimigoFacil::executar() {
            mover();
        }

        void InimigoFacil::mover() {

            if (noChao && pGG) {

                float limiteDireito = (float)pGG->getTamanhoJanela().x;

                // inverte a direcao nas extremidades
                if (posicao.x <= 0.f)
                    velocidade.x = velocidadeMaxima.x;

                else if (posicao.x + getTamanho().x >= limiteDireito)
                    velocidade.x = -velocidadeMaxima.x;

                else if (velocidade.x == 0.f)
                    velocidade.x = velocidadeMaxima.x;
            }
            else {
                velocidade.x = 0.f;
            }

            integrar();
        }

        void InimigoFacil::danificar(Jogador* pJ) {
            if (pJ)
                pJ->sofrerDano();
        }

    }
}
