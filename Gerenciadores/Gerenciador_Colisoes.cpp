#include "Gerenciador_Colisoes.h"
#include "../Entidades/Entidade.h"
#include "../Entidades/Chao.h"
#include "../Entidades/Jogador.h"
#include "../Entidades/Inimigo.h"
#include "../Entidades/Obstaculo.h"
#include <algorithm>

namespace Gerenciadores {

    Gerenciador_Colisoes::Gerenciador_Colisoes() :
        LIs(),
        LOs(),
        pJog1(nullptr),
        pChao(nullptr),
        larguraMundo(0.f) {
    }

    Gerenciador_Colisoes::~Gerenciador_Colisoes() {
        LIs.clear();
        LOs.clear();
        pJog1 = nullptr;
        pChao = nullptr;
    }

    void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi) {
        if (pi)
            LIs.push_back(pi);
    }

    void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* po) {
        if (po)
            LOs.push_back(po);
    }

    std::vector<Entidades::Personagens::Inimigo*> Gerenciador_Colisoes::retirarInimigosMortos() {
        std::vector<Entidades::Personagens::Inimigo*> mortos;
        for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end();) {
            if (!(*it)->estaVivo()) {
                mortos.push_back(*it);
                it = LIs.erase(it);
            }
            else
                ++it;
        }
        return mortos;
    }

    int Gerenciador_Colisoes::getQuantidadeInimigos() const {
        int quantidade = 0;
        for (std::size_t i = 0; i < LIs.size(); ++i)
            if (LIs[i]->estaVivo())
                ++quantidade;
        return quantidade;
    }

    DadosColisao Gerenciador_Colisoes::calcularColisaoAABB(
        const Entidades::Entidade* pE1,
        const Entidades::Entidade* pE2
    ) const {
        DadosColisao resultado;
        if (!pE1 || !pE2)
            return resultado;

        const sf::Vector2f p1 = pE1->getPosicao();
        const sf::Vector2f t1 = pE1->getTamanho();
        const sf::Vector2f p2 = pE2->getPosicao();
        const sf::Vector2f t2 = pE2->getTamanho();

        const bool colisao =
            p1.x < p2.x + t2.x && p1.x + t1.x > p2.x &&
            p1.y < p2.y + t2.y && p1.y + t1.y > p2.y;

        if (!colisao)
            return resultado;

        resultado.houveColisao = true;
        resultado.sobreposicaoX = std::min(p1.x + t1.x, p2.x + t2.x) - std::max(p1.x, p2.x);
        resultado.sobreposicaoY = std::min(p1.y + t1.y, p2.y + t2.y) - std::max(p1.y, p2.y);
        return resultado;
    }

    std::vector<Entidades::Personagens::Personagem*> Gerenciador_Colisoes::coletarPersonagens() const {
        std::vector<Entidades::Personagens::Personagem*> todos;

        if (pJog1)
            todos.push_back(pJog1);

        for (std::size_t i = 0; i < LIs.size(); i++)
            todos.push_back(LIs[i]);

        return todos;
    }

    void Gerenciador_Colisoes::resolverColisaoVertical(
        Entidades::Personagens::Personagem* pPer,
        const Entidades::Entidade* pSolido,
        const DadosColisao& colisao
    ) {
        sf::Vector2f novaPos = pPer->getPosicao();
        sf::Vector2f vel = pPer->getVelocidade();

        const float centroPersonagem = novaPos.y + pPer->getTamanho().y / 2.f;
        const float centroSolido = pSolido->getPosicao().y + pSolido->getTamanho().y / 2.f;

        if (centroPersonagem < centroSolido) {
            //pousou
            novaPos.y -= colisao.sobreposicaoY;
            if (vel.y > 0.f) vel.y = 0.f;
            pPer->setNoChao(true);
        }
        else {
            // atingiu o solido por baixo
            novaPos.y += colisao.sobreposicaoY;
            if (vel.y < 0.f) vel.y = 0.f;
        }

        pPer->setPosicao(novaPos);
        pPer->setVelocidade(vel);
    }

    void Gerenciador_Colisoes::resolverColisaoHorizontal(
        Entidades::Personagens::Personagem* pPer,
        const Entidades::Entidade* pSolido,
        const DadosColisao& colisao
    ) {
        sf::Vector2f novaPos = pPer->getPosicao();
        sf::Vector2f vel = pPer->getVelocidade();

        const float centroPersonagem = novaPos.x + pPer->getTamanho().x / 2.f;
        const float centroSolido = pSolido->getPosicao().x + pSolido->getTamanho().x / 2.f;

        if (centroPersonagem < centroSolido)
            novaPos.x -= colisao.sobreposicaoX;
        else
            novaPos.x += colisao.sobreposicaoX;

        vel.x = 0.f;
        pPer->setPosicao(novaPos);
        pPer->setVelocidade(vel);
    }

    void Gerenciador_Colisoes::resolverColisaoPersonagemSolido(
        Entidades::Personagens::Personagem* pPer,
        const Entidades::Entidade* pSolido,
        const DadosColisao& colisao
    ) {
        if (!colisao.houveColisao)
            return;

        if (colisao.sobreposicaoX < colisao.sobreposicaoY)
            resolverColisaoHorizontal(pPer, pSolido, colisao);
        else
            resolverColisaoVertical(pPer, pSolido, colisao);
    }

    void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
        if (!pJog1)
            return;

        for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
            const DadosColisao colisao = calcularColisaoAABB(pJog1, *it);
            if (colisao.houveColisao) {
                resolverColisaoPersonagemSolido(pJog1, *it, colisao); // geometria: do gerenciador
                (*it)->obstaculizar(pJog1);                           // efeito: do obstaculo (so quando colide)
            }
        }

        if (pChao) {
            const DadosColisao colisao = calcularColisaoAABB(pJog1, pChao);
            resolverColisaoPersonagemSolido(pJog1, pChao, colisao);
        }
    }

    void Gerenciador_Colisoes::tratarColisoesInimgsObstacs() {
        for (std::size_t i = 0; i < LIs.size(); i++) {
            if (!LIs[i]->estaVivo())
                continue;
            for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
                const DadosColisao colisao = calcularColisaoAABB(LIs[i], *it);
                resolverColisaoPersonagemSolido(LIs[i], *it, colisao);
            }

            if (pChao) {
                const DadosColisao colisao = calcularColisaoAABB(LIs[i], pChao);
                resolverColisaoPersonagemSolido(LIs[i], pChao, colisao);
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
        if (!pJog1)
            return;

        for (std::size_t i = 0; i < LIs.size(); i++) {
            if (LIs[i]->estaVivo() && calcularColisaoAABB(pJog1, LIs[i]).houveColisao)
                pJog1->colidir(LIs[i]);
        }
    }

    void Gerenciador_Colisoes::tratarLimitesDoMundo() {
        if (larguraMundo <= 0.f)
            return;

        std::vector<Entidades::Personagens::Personagem*> todos = coletarPersonagens();

        for (std::size_t i = 0; i < todos.size(); i++) {
            sf::Vector2f pos = todos[i]->getPosicao();
            const float largura = todos[i]->getTamanho().x;
            const sf::Vector2f original = pos;

            if (pos.x < 0.f)
                pos.x = 0.f;
            else if (pos.x + largura > larguraMundo)
                pos.x = larguraMundo - largura;

            if (pos.x != original.x)
                todos[i]->setPosicao(pos);
        }
    }

    void Gerenciador_Colisoes::executar() {
        tratarColisoesJogsObstacs();
        tratarColisoesInimgsObstacs();
        tratarColisoesJogsInimgs();
        tratarLimitesDoMundo();
    }

}
