#include "Jogador.h"
#include "Inimigo.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"
#include <SFML/Window/Keyboard.hpp>

namespace Entidades {
    namespace Personagens {

        const int   Jogador::VIDAS_INICIAIS = 3;
        const float Jogador::VELOCIDADE = 250.f;
        const float Jogador::FORCA_PULO = 600.f;
        const float Jogador::TEMPO_INVULNERAVEL = 1.5f;

        Jogador::Jogador() :
            Personagem(VIDAS_INICIAIS),
            invulneravel(0.f) {
            corpo.setSize(sf::Vector2f(40.f, 60.f));
            corpo.setFillColor(sf::Color::Green);
            setVelocidadeMaxima(sf::Vector2f(300.f, 900.f));
        }

        Jogador::~Jogador() {
        }

        void Jogador::processarEntrada() {
            velocidade.x = 0.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                velocidade.x = -VELOCIDADE;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                velocidade.x = VELOCIDADE;
            }

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && noChao) {
                velocidade.y = -FORCA_PULO;
                noChao = false;
            }
        }

        void Jogador::mover() {
            processarEntrada();
            integrar();
        }

        void Jogador::executar() {
            mover();

            if (invulneravel > 0.f) {
                const float dt = pGG ? pGG->getDeltaTime() : 0.f;
                invulneravel -= dt;
                if (invulneravel < 0.f)
                    invulneravel = 0.f;

                const bool claro = (invulneravel > 0.f) && (static_cast<int>(invulneravel * 10.f) % 2 == 0);
                corpo.setFillColor(claro ? sf::Color(170, 255, 170) : sf::Color::Green);
            }
        }

        void Jogador::colidir(Inimigo* pIn) {
            if (pIn)
                pIn->danificar(this);
        }

        void Jogador::sofrerDano() {
            if (invulneravel > 0.f)
                return;

            --num_vidas;
            invulneravel = TEMPO_INVULNERAVEL;
            velocidade.y = -300.f; //impulso
        }

        const bool Jogador::estaVivo() const {
            return num_vidas > 0;
        }

        void Jogador::reiniciar(const sf::Vector2f& pos) {
            setPosicao(pos);
            num_vidas = VIDAS_INICIAIS;
            velocidade = sf::Vector2f(0.f, 0.f);
            invulneravel = 0.f;
            corpo.setFillColor(sf::Color::Green);
        }

    }
}
