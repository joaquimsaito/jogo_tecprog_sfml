#include "Jogador.h"
#include "Inimigo.h"

#include <SFML/Window/Keyboard.hpp>
#include <cmath>

using namespace Entidades::Personagens;

Jogador::Jogador() :
	Personagem(3),
	invulneravel(0.f),
	pontos(0),
	impulsoX(0.f)
{
	corpo.setSize(sf::Vector2f(40.f, 60.f));
	corpo.setFillColor(sf::Color::Green);
	setVelocidadeMaxima(sf::Vector2f(300.f, 900.f));
}

Jogador::~Jogador() {}


const int Jogador::getPontos() const {
	return pontos;
}

void Jogador::processarEntrada() {
	velocidade.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		velocidade.x = -250.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		velocidade.x = 250.f;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && noChao) {
		velocidade.y = -600.f;
		noChao = false;
	}

	velocidade.x += impulsoX; //empurrao recebido de um inimigo (0 na maior parte do tempo)
}

void Jogador::executar() {
	mover();
	if (invulneravel > 0.f) {
		invulneravel -= getDt();
		if (invulneravel < 0.f)
			invulneravel = 0.f;

		const bool claro = (invulneravel > 0.f) && (static_cast<int>(invulneravel * 10.f) % 2 == 0);
		if (claro) corpo.setFillColor(sf::Color(170, 255, 170));
		else corpo.setFillColor(sf::Color::Green);
	}
}

void Jogador::mover() {
	processarEntrada();
	integrar();

	impulsoX -= impulsoX * 4.f * getDt(); //o empurrao se dissipa em ~0,25 s
	if (std::fabs(impulsoX) < 5.f) impulsoX = 0.f;
}

void Jogador::colidir(Inimigo* pIn) {
	if (!pIn || pIn->getNeutralizado()) return;

	//pisao (decisao 5): jogador caindo e com os pes na metade de cima do inimigo
	const float pes = posicao.y + getTamanho().y;
	const float penetracao = pes - pIn->getPosicao().y;

	if (velocidade.y > 0.f && penetracao <= pIn->getTamanho().y / 2.f) {
		sf::Vector2f pos = posicao;
		pos.y = pIn->getPosicao().y - getTamanho().y; //fica em cima do inimigo, sem sobrepor (evita contar como dano no quadro seguinte)
		setPosicao(pos);
		velocidade.y = -350.f;
		noChao = false;

		if (pIn->neutralizar())
			++(*this);
	}
	else {
		pIn->danificar(this);
	}
}

void Jogador::sofrerDano(const int dano, const float empurrao) {
	if (invulneravel > 0.f) return;

	num_vidas -= dano;
	if (num_vidas < 0) num_vidas = 0;
	if (pontos > 0) --(*this);
	invulneravel = 1.5f;
	velocidade.y = -300.f; //impulso
	impulsoX = empurrao;
}

void Jogador::reiniciar(const sf::Vector2f& pos) {
	setPosicao(pos);
	num_vidas = 3;
	velocidade = sf::Vector2f(0.f, 0.f);
	invulneravel = 0.f;
	impulsoX = 0.f;
	corpo.setFillColor(sf::Color::Green);
}
