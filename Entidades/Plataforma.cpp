#include "Plataforma.h"
#include "Jogador.h"

using namespace Entidades::Obstaculos;

Plataforma::Plataforma(const sf::Vector2f& pos, const sf::Vector2f& tam) :
	Obstaculo(false)
{
	corpo.setSize(tam);
	corpo.setFillColor(sf::Color(120, 120, 120));
	setPosicao(pos);
}

Plataforma::~Plataforma() {}


void Plataforma::executar() {
	// a definir na etapa 4 (piscar, sumir e reaparecer)
}

void Plataforma::obstaculizar(Personagens::Jogador* pJ) {
	//a plataforma deve impedir que o jogador atravesse ela
	if (!pJ || !ativo) return;
	bloquear(pJ);
}
