#include "Inimigo.h"

#include <cstdlib>

using namespace Entidades::Personagens;

Inimigo::Inimigo(const int nivelMaldade, const int vidas) :
	Personagem(vidas),
	nivel_maldade(nivelMaldade),
	direcao(1),
	neutralizado(false)
{
	if (rand() % 2 == 0) direcao = -1;
}

Inimigo::~Inimigo() {}


void Inimigo::setDirecao(const int d) {
	if (d < 0) direcao = -1;
	else direcao = 1;
}

const int Inimigo::getNivelMaldade() const {
	return nivel_maldade;
}

const bool Inimigo::getNeutralizado() const {
	return neutralizado;
}

void Inimigo::inverterDirecao() {
	direcao = -direcao;
}

const bool Inimigo::neutralizar() {
	if (neutralizado) return false;

	num_vidas--;
	if (num_vidas <= 0) {
		num_vidas = 0;
		neutralizado = true;
		velocidade.x = 0.f;
		corpo.setFillColor(sf::Color(120, 120, 120));
	}
	return neutralizado;
}
