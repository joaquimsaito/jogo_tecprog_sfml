#include "Gerenciador_Colisoes.h"
#include <algorithm>

namespace Gerenciadores {

    Gerenciador_Colisoes::Gerenciador_Colisoes() :
        pPersonagemPrincipal(nullptr) {
    }

    Gerenciador_Colisoes::~Gerenciador_Colisoes() {
        pPersonagemPrincipal = nullptr;
        limparObstaculos();
    }

    DadosColisao Gerenciador_Colisoes::calcularColisaoAABB(
        const Entidades::Entidade* pE1,
        const Entidades::Entidade* pE2
    ) const {
        DadosColisao resultado;
        if (!pE1 || !pE2) return resultado;

        const sf::Vector2f p1 = pE1->getPosicao();
        const sf::Vector2f t1 = pE1->getCorpo().getSize();
        const sf::Vector2f p2 = pE2->getPosicao();
        const sf::Vector2f t2 = pE2->getCorpo().getSize();

        const bool colisao =
            p1.x < p2.x + t2.x && p1.x + t1.x > p2.x &&
            p1.y < p2.y + t2.y && p1.y + t1.y > p2.y;

        if (!colisao) return resultado;

        resultado.houveColisao = true;
        resultado.sobreposicaoX =
            std::min(p1.x + t1.x, p2.x + t2.x) - std::max(p1.x, p2.x);
        resultado.sobreposicaoY =
            std::min(p1.y + t1.y, p2.y + t2.y) - std::max(p1.y, p2.y);

        return resultado;
    }

    bool Gerenciador_Colisoes::verificaColisaoAABB(
        const Entidades::Entidade* pE1,
        const Entidades::Entidade* pE2
    ) const {
        return calcularColisaoAABB(pE1, pE2).houveColisao;
    }

    void Gerenciador_Colisoes::verificarColisoesVertical(
        Entidades::Personagens::Personagem* pPer,
        Entidades::Entidade* pObs,
        const DadosColisao& colisao
    ) {
        sf::Vector2f novaPos = pPer->getPosicao();
        sf::Vector2f vel = pPer->getVelocidade();

        const float centroPersonagem =
            novaPos.y + pPer->getCorpo().getSize().y / 2.f;
        const float centroObstaculo =
            pObs->getPosicao().y + pObs->getCorpo().getSize().y / 2.f;

        if (centroPersonagem < centroObstaculo) {
            // O personagem atingiu o obstaculo por cima.
            novaPos.y -= colisao.sobreposicaoY;
            if (vel.y > 0.f) vel.y = 0.f;
            pPer->setNoChao(true);
        }
        else {
            // O personagem atingiu o obstaculo por baixo.
            novaPos.y += colisao.sobreposicaoY;
            if (vel.y < 0.f) vel.y = 0.f;
        }

        pPer->setPosicao(novaPos);
        pPer->setVelocidade(vel);
    }

    void Gerenciador_Colisoes::verificarColisoesHorizontal(
        Entidades::Personagens::Personagem* pPer,
        Entidades::Entidade* pObs,
        const DadosColisao& colisao
    ) {
        sf::Vector2f novaPos = pPer->getPosicao();
        sf::Vector2f vel = pPer->getVelocidade();

        const float centroPersonagem =
            novaPos.x + pPer->getCorpo().getSize().x / 2.f;
        const float centroObstaculo =
            pObs->getPosicao().x + pObs->getCorpo().getSize().x / 2.f;

        if (centroPersonagem < centroObstaculo)
            novaPos.x -= colisao.sobreposicaoX;
        else
            novaPos.x += colisao.sobreposicaoX;

        vel.x = 0.f;
        pPer->setPosicao(novaPos);
        pPer->setVelocidade(vel);
    }

    void Gerenciador_Colisoes::resolverColisaoPersonagemObstaculo(
        Entidades::Personagens::Personagem* pPer,
        Entidades::Entidade* pObs,
        const DadosColisao& colisao
    ) {
        if (!colisao.houveColisao) return;

        if (colisao.sobreposicaoX < colisao.sobreposicaoY)
            verificarColisoesHorizontal(pPer, pObs, colisao);
        else
            verificarColisoesVertical(pPer, pObs, colisao);
    }

    void Gerenciador_Colisoes::executar() {
        if (!pPersonagemPrincipal) return;

        // O vetor contem entidades que atuam como obstaculos na fase.
        for (Entidades::Entidade* pObs : obstaculos) {
            if (!pObs) continue;

            const DadosColisao colisao =
                calcularColisaoAABB(pPersonagemPrincipal, pObs);
            resolverColisaoPersonagemObstaculo(
                pPersonagemPrincipal, pObs, colisao);
        }
    }

}
