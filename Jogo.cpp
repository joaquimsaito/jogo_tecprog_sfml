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
}

Jogo::~Jogo() {
    delete pJogador1;
    pJogador1 = nullptr;

    delete pChao;
    pChao = nullptr;

    Ente::setGerenciadorGrafico(nullptr);
}

void Jogo::executar() {
    while (GG.janelaAberta()) {
        GG.tratarEventos();
        GG.atualizarTempo();

        pJogador1->executar();
        pChao->executar();

        GC.executar();

        GG.limpar();
        pChao->desenhar();
        pJogador1->desenhar();
        GG.mostrar();
    }
}
