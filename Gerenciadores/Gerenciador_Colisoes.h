#pragma once

#include "../Entidades/Personagem.h"
#include "../Entidades/Entidade.h"
#include <vector>

namespace Gerenciadores {

    struct DadosColisao {
        bool houveColisao;
        float sobreposicaoX;
        float sobreposicaoY;

        DadosColisao() :
            houveColisao(false),
            sobreposicaoX(0.f),
            sobreposicaoY(0.f) {
        }
    };

    class Gerenciador_Colisoes {
    private:
        Entidades::Personagens::Personagem* pPersonagemPrincipal;
        std::vector<Entidades::Entidade*> obstaculos;

        DadosColisao calcularColisaoAABB(
            const Entidades::Entidade* pE1,
            const Entidades::Entidade* pE2
        ) const;

        void resolverColisaoPersonagemObstaculo(
            Entidades::Personagens::Personagem* pPer,
            Entidades::Entidade* pObs,
            const DadosColisao& colisao
        );

        void verificarColisoesVertical(
            Entidades::Personagens::Personagem* pPer,
            Entidades::Entidade* pObs,
            const DadosColisao& colisao
        );

        void verificarColisoesHorizontal(
            Entidades::Personagens::Personagem* pPer,
            Entidades::Entidade* pObs,
            const DadosColisao& colisao
        );

    public:
        Gerenciador_Colisoes();
        ~Gerenciador_Colisoes();

        void setPersonagemPrincipal(Entidades::Personagens::Personagem* pP) {
            pPersonagemPrincipal = pP;
        }

        void adicionarObstaculo(Entidades::Entidade* pObs) {
            if (pObs) obstaculos.push_back(pObs);
        }

        void limparObstaculos() { obstaculos.clear(); }

        bool verificaColisaoAABB(
            const Entidades::Entidade* pE1,
            const Entidades::Entidade* pE2
        ) const;

        void executar();
    };
}
