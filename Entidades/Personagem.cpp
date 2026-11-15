#include "Personagem.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"

namespace Entidades {
    namespace Personagens {

        const float Personagem::GRAVIDADE = 980.f;

        Personagem::Personagem(const int vidas) :
            Entidade(),
            num_vidas(vidas),
            velocidade(0.f, 0.f),
            aceleracao(0.f, 0.f),
            velocidadeMaxima(0.f, 0.f),
            noChao(false) {
        }

        Personagem::~Personagem() {
        }

        void Personagem::integrar() {
            const float dt = pGG ? pGG->getDeltaTime() : 0.f;

            velocidade.x += aceleracao.x * dt;
            velocidade.y += (aceleracao.y + GRAVIDADE) * dt;

            if (velocidadeMaxima.x > 0.f) {
                if (velocidade.x > velocidadeMaxima.x)  velocidade.x = velocidadeMaxima.x;
                if (velocidade.x < -velocidadeMaxima.x) velocidade.x = -velocidadeMaxima.x;
            }
            if (velocidadeMaxima.y > 0.f) {
                if (velocidade.y > velocidadeMaxima.y)  velocidade.y = velocidadeMaxima.y;
                if (velocidade.y < -velocidadeMaxima.y) velocidade.y = -velocidadeMaxima.y;
            }

            setPosicao(posicao + velocidade * dt);
            noChao = false; // quem confirma o apoio eh o GC
        }

    }
}