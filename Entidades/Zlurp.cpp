#include "Zlurp.h"
#include "Jogador.h"

using namespace Entidades::Personagens;

Zlurp::Zlurp(const int nivelMaldade) :
	Inimigo(nivelMaldade, 6),
	tamanho(70),
	tempoParado(0.f),
	intervaloPulo(3.f - 0.4f * nivelMaldade) //maior maldade = pula com mais frequencia
{
	corpo.setSize(sf::Vector2f(50.f, static_cast<float>(tamanho)));
	corpo.setFillColor(sf::Color::Yellow);
	setVelocidadeMaxima(sf::Vector2f(0.f, 900.f)); //0 em x = sem limite horizontal
}

Zlurp::~Zlurp() {}


void Zlurp::executar() {
	if (neutralizado) {
		integrar(); //neutralizado: so cai (decisao 5)
	}
	else {
		tempoParado += getDt(); //tempo desde o ultimo pulo
		mover();
	}
}

void Zlurp::mover() {
	velocidade.x = direcao * 80.f;

	if (noChao && tempoParado >= intervaloPulo) {
		velocidade.y = -(350.f + 60.f * nivel_maldade); //maior maldade = pulo mais alto
		tempoParado = 0.f;
		noChao = false;
	}
	integrar();
}

void Zlurp::danificar(Jogador* pJ) {
	// Zlurp tira duas vidas e empurra pra tras o jogador
	if (!pJ) return;

	const float centroJogador = pJ->getPosicao().x + pJ->getTamanho().x / 2.f;
	const float centroZlurp = posicao.x + getTamanho().x / 2.f;
	float empurrao = 300.f;
	if (centroJogador < centroZlurp) empurrao = -300.f;
	pJ->sofrerDano(2, empurrao);
}
