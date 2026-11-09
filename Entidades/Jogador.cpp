#include "Jogador.h"
#include <SFML/Window/Keyboard.hpp>

namespace Entidades {
    namespace Personagens {

        Jogador::Jogador() :
            Personagem(),
            forcaPulo(450.f) {
            corpo.setSize(sf::Vector2f(40.f, 60.f));
            corpo.setFillColor(sf::Color::Green);
            setVelocidadeMaxima(sf::Vector2f(300.f, 900.f));
            setGravidade(980.f);
            setPosicao(sf::Vector2f(100.f, 100.f));
        }

        void Jogador::procesarEntrada() {
            velocidade.x = 0.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                velocidade.x = -250.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                velocidade.x = 250.f;
            }

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && noChao) {
                velocidade.y = -forcaPulo;
                noChao = false;
            }
        }

        void Jogador::mover() {
            procesarEntrada();
            aplicaGravidade();
        }

        void Jogador::executar() {
            mover();
        }

    }
}
