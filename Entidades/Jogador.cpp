#include "Jogador.h"

using namespace Entidades::Personagens;

Jogador::Jogador() :
	Personagem(),
	forcaPulo(300.f) {
	corpo.setSize(sf::Vector2f(40.f, 60.f));
	corpo.setFillColor(sf::Color::Green);
	setVelocidadeMaxima(sf::Vector2f(300.f, 900.f)); // x: velocidade de caminhada; y: velocidade terminal de queda
	setPosicao(sf::Vector2f(100.f, 100.f));
}

void Jogador::executar() {
	mover();
}

void Jogador::mover() {
	// Horizontal: obedece as setinhas
	float vx = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		vx -= velocidadeMaxima.x;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		vx += velocidadeMaxima.x;
	velocidade.x = vx;

	// Pulo: so se estiver apoiado (noChao foi atualizado pelo Gerenciador_Colisoes no quadro anterior)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && noChao)
		velocidade.y = -forcaPulo;

	// Gravidade + integracao da posicao
	aplicaGravidade();

	// Nao deixa sair da janela pelas laterais
	if (pGerenciadorGrafico) {
		const float largJanela = static_cast<float>(pGerenciadorGrafico->getTamanhoJanela().x);
		const float largCorpo = corpo.getSize().x;
		sf::Vector2f p = posicao;
		if (p.x < 0.f)                      p.x = 0.f;
		if (p.x > largJanela - largCorpo)   p.x = largJanela - largCorpo;
		setPosicao(p);
	}
}
