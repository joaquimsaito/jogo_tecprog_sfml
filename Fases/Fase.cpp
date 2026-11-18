#include "Fase.h"
#include "../Entidades/Jogador.h"
#include "../Entidades/Chao.h"
#include "../Entidades/Plataforma.h"
#include "../Entidades/InimigoFacil.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"

namespace Fases {

    const float Fase::ALTURA_CHAO = 60.f;

    Fase::Fase() :
        Ente(),
        lista_ents(),
        GC(),
        pJog1(nullptr),
        tamanhoMundo(800.f, 600.f),
        posInicialJogador(100.f, 100.f) {
        if (pGG) {
            const sf::Vector2u janela = pGG->getTamanhoJanela();
            tamanhoMundo = sf::Vector2f(static_cast<float>(janela.x), static_cast<float>(janela.y));
        }
        GC.setLarguraMundo(tamanhoMundo.x);
    }

    Fase::~Fase() {
        pJog1 = nullptr;
    }

    void Fase::setJogador(Entidades::Personagens::Jogador* pJ) {
        pJog1 = pJ;
        GC.setJogador(pJ);
        if (pJ)
            pJ->setPosicao(posInicialJogador);
    }

    void Fase::criarChao() {
        Entidades::Chao* pChao = new Entidades::Chao(
            sf::Vector2f(0.f, tamanhoMundo.y - ALTURA_CHAO),
            sf::Vector2f(tamanhoMundo.x, ALTURA_CHAO));

        lista_ents.incluir(pChao);
        GC.setChao(pChao);
    }

    void Fase::criarPlataformas() {
        const sf::Vector2f tamanho(180.f, 20.f);

        const sf::Vector2f posicoes[4] = {
            sf::Vector2f(tamanhoMundo.x * 0.05f,  tamanhoMundo.y - 170.f),
            sf::Vector2f(tamanhoMundo.x * 0.275f, tamanhoMundo.y - 250.f),
            sf::Vector2f(tamanhoMundo.x * 0.50f,  tamanhoMundo.y - 330.f),
            sf::Vector2f(tamanhoMundo.x * 0.725f, tamanhoMundo.y - 410.f)
        };

        int quantidade = rand() % 4 + 3;

        for (int i = 0; i < quantidade; i++) {
            Entidades::Obstaculos::Plataforma* pPlat =
                new Entidades::Obstaculos::Plataforma(posicoes[i], tamanho);

            lista_ents.incluir(pPlat);
            GC.incluirObstaculo(pPlat);
        }
    }

    void Fase::criarInimFaceis() {

        const sf::Vector2f posicoes[4] = {
            sf::Vector2f(250.f, 400.f),
            sf::Vector2f(250.f, 500.f),
            sf::Vector2f(300.f, 400.f),
            sf::Vector2f(350.f, 500.f)
        };
        int quantidade = rand() % 4 + 3;

            for (int i = 0; i < quantidade; i++) {
                Entidades::Personagens::InimigoFacil* pInim =
                    new Entidades::Personagens::InimigoFacil(posicoes[i]);
                lista_ents.incluir(pInim);
                GC.incluirInimigo(pInim);
            };
    }

    /*void Fase::criarInimFaceis() {
        // um inimigo em posicao fixa por enquanto; cai ate o chao
        Entidades::Personagens::InimigoFacil* pInim = new Entidades::Personagens::InimigoFacil();
        pInim->setPosicao(sf::Vector2f(250.f, 400.f));

        lista_ents.incluir(pInim);
        GC.incluirInimigo(pInim);
    }*/

    void Fase::criarCenario() {
        criarChao();
        criarObstaculos(); // virtual: depende da fase concreta
        criarInimigos(); // virtual: depende da fase concreta
    }

    void Fase::executar() {
        lista_ents.executar();
        if (pJog1)
            pJog1->executar();

        GC.executar();

        // provisorio: ao morrer o jogador renasce no ponto inicial.
        if (pJog1 && !pJog1->estaVivo())
            pJog1->reiniciar(posInicialJogador);

        lista_ents.desenhar();
        if (pJog1)
            pJog1->desenhar(); // por ultimo: fica por cima
    }

}
