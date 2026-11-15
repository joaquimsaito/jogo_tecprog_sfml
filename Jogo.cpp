#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Jogador.h"
#include "Fases/FasePrimeira.h"

Jogo::Jogo() :
    GG(),
    pJog1(nullptr),
    pFase(nullptr) {
    Ente::setGG(&GG);

    pJog1 = new Entidades::Personagens::Jogador();
    pFase = new Fases::FasePrimeira();
    pFase->setJogador(pJog1);
}

Jogo::~Jogo() {
    delete pFase;
    pFase = nullptr;

    delete pJog1;
    pJog1 = nullptr;

    Ente::setGG(nullptr);
}

void Jogo::executar() {
    while (GG.janelaAberta()) {
        GG.tratarEventos();
        GG.atualizarTempo();

        GG.limpar();
        pFase->executar(); // executa, resolve colisoes e desenha
        GG.mostrar();
    }
}
