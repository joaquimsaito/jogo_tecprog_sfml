#include "Plataforma.h"
#include "Jogador.h"

namespace Entidades {
    namespace Obstaculos {

        Plataforma::Plataforma(const sf::Vector2f& pos, const sf::Vector2f& tam) :
            Obstaculo(),
            altura(static_cast<int>(tam.y)) {
            corpo.setSize(tam);
            corpo.setFillColor(sf::Color(120, 120, 120));
            setPosicao(pos);
        }

        void Plataforma::executar() {
            // Plataforma e estatica: nao precisa atualizar sua posicao.
        }

        void Plataforma::obstacularizar(Personagens::Jogador* pJ) {
            if (!pJ) return;

            const sf::Vector2f posJogador = pJ->getPosicao();
            const sf::Vector2f tamJogador = pJ->getCorpo().getSize();
            const sf::Vector2f velJogador = pJ->getVelocidade();
            const sf::Vector2f posPlataforma = getPosicao();
            const sf::Vector2f tamPlataforma = getCorpo().getSize();

            const float baseJogador = posJogador.y + tamJogador.y;
            const float topoPlataforma = posPlataforma.y;
            const bool sobrepoeHorizontal =
                posJogador.x < posPlataforma.x + tamPlataforma.x &&
                posJogador.x + tamJogador.x > posPlataforma.x;
            const bool sobrepoeVertical =
                baseJogador > topoPlataforma &&
                posJogador.y < topoPlataforma + static_cast<float>(altura);

            // A plataforma sustenta o jogador quando ele cai sobre ela.
            if (sobrepoeHorizontal && sobrepoeVertical && velJogador.y >= 0.f) {
                sf::Vector2f novaPosicao = posJogador;
                novaPosicao.y = topoPlataforma - tamJogador.y;
                pJ->setPosicao(novaPosicao);

                sf::Vector2f novaVelocidade = velJogador;
                novaVelocidade.y = 0.f;
                pJ->setVelocidade(novaVelocidade);
                pJ->setNoChao(true);
            }
        }

    }
}

