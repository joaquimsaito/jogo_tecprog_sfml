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
	pChao = new Entidades::Chao(sf::Vector2f(0.f, janela.y - 60.f), sf::Vector2f(static_cast<float>(janela.x), 60.f));

	GC.setJogador(pJogador1);
	GC.setChao(pChao);
}

Jogo::~Jogo() {
	// Jogo eh dono do que criou com new
	delete pJogador1;
	pJogador1 = nullptr;
	delete pChao;
	pChao = nullptr;

	Ente::setGerenciadorGrafico(nullptr); // GG sera destruido logo apos este destrutor
}

void Jogo::executar() {
	while (GG.janelaAberta()) {
		GG.tratarEventos();
		GG.atualizarTempo();

		// Atualiza o estado das entidades
		pJogador1->executar();
		pChao->executar();

		// Resolve colisoes depois do movimento
		GC.executar();

		// Desenha
		GG.limpar();
		pChao->desenhar();
		pJogador1->desenhar();
		GG.mostrar();
	}
}
