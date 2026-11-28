#include "Bog.h"
#include "Jogador.h"

using namespace Entidades::Personagens;

Bog::Bog(const int nivelMaldade) :
	Inimigo(nivelMaldade, 4)
{
	corpo.setSize(sf::Vector2f(30.f, 50.f));
	corpo.setFillColor(sf::Color::Red);
	//velocidade = base (100) + nivelMaldade * passo (15): o nivel de maldade varia a velocidade do inimigo
	setVelocidadeMaxima(sf::Vector2f(100.f + nivelMaldade * 15.f, 900.f));
}

Bog::~Bog() {}


void Bog::executar() {
	if (neutralizado) integrar(); //neutralizado: so cai (decisao 5)
	else mover();
}

void Bog::mover() {
	if (noChao)
		velocidade.x = direcao * velocidadeMaxima.x;
	else
		velocidade.x = 0.f;

	integrar();
}

void Bog::danificar(Jogador* pJ) {
	if (pJ) pJ->sofrerDano(1);
}
