#include "Personagem.h"
#include <algorithm>

namespace Entidades {
    namespace Personagens {

        Personagem::Personagem() :
            Entidade(),
            velocidade(0.f, 0.f),
            aceleracao(0.f, 0.f),
            velocidadeMaxima(0.f, 0.f),
            gravidade(980.f),
            noChao(false) {
        }

        void Personagem::aplicaGravidade() {
            const float dt = pGerenciadorGrafico
                ? pGerenciadorGrafico->getDeltaTime()
                : 0.f;

            velocidade.x += aceleracao.x * dt;
            velocidade.y += (aceleracao.y + gravidade) * dt;

            if (velocidadeMaxima.x > 0.f) {
                velocidade.x = std::clamp(velocidade.x,
                    -velocidadeMaxima.x,
                    velocidadeMaxima.x);
            }
            if (velocidadeMaxima.y > 0.f) {
                velocidade.y = std::clamp(velocidade.y,
                    -velocidadeMaxima.y,
                    velocidadeMaxima.y);
            }

            setPosicao(posicao + velocidade * dt);
            noChao = false;
        }

    }
}
