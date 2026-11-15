#include "Jogo.h"
#include "Ente.h"

Jogo::Jogo() :
    GG(),
    GC(),
    pJogador1(nullptr),
    pChao(nullptr) {
    Ente::setGerenciadorGrafico(&GG);

    pJogador1 = new Entidades::Personagens::Jogador();

    const sf::Vector2u janela = GG.getTamanhoJanela();
    pChao = new Entidades::Chao(
        sf::Vector2f(0.f, static_cast<float>(janela.y) - 60.f),
        sf::Vector2f(static_cast<float>(janela.x), 60.f));

    GC.setPersonagemPrincipal(pJogador1);
    GC.adicionarObstaculo(pChao);
    pPlataforma = new Entidades::Obstaculos::Plataforma(
        sf::Vector2f(
            static_cast<float>(janela.x) * 0.55f,
            static_cast<float>(janela.y) - 200.f
        ),
        sf::Vector2f(180.f, 20.f)
    );
    GC.adicionarObstaculo(pPlataforma);
}

Jogo::~Jogo() {
    delete pJogador1;
    pJogador1 = nullptr;

    delete pChao;
    pChao = nullptr;

    delete pPlataforma;
    pPlataforma = nullptr;

    Ente::setGerenciadorGrafico(nullptr);
}

void Jogo::executar() {
    while (GG.janelaAberta()) {
        GG.tratarEventos();
        GG.atualizarTempo();

        pJogador1->executar();
        pChao->executar();
        pPlataforma->executar();

        GC.executar();

        GG.limpar();
        pChao->desenhar();
        pPlataforma->desenhar();
        pJogador1->desenhar();
        GG.mostrar();
    }
}
