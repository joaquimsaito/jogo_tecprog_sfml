#include "Entidade.h"

using namespace Entidades;

Entidade::Entidade() :
	Ente(),
	corpo(),
	posicao(0.f, 0.f)
{
	pFig = &corpo;
}

Entidade::~Entidade() {
	pFig = nullptr;
}


void Entidade::setCorpo(const sf::RectangleShape& c) {
	corpo = c;
	setPosicao(c.getPosition());
}

void Entidade::setPosicao(const sf::Vector2f& p) {
	posicao = p;
	corpo.setPosition(posicao); //o corpo precisa acompanhar a posicao, senao a entidade eh desenhada sempre em (0,0)
}

const sf::RectangleShape& Entidade::getCorpo() const {
	return corpo;
}

const sf::Vector2f Entidade::getPosicao() const {
	return posicao;
}

const sf::Vector2f Entidade::getTamanho() const {
	return corpo.getSize();
}
