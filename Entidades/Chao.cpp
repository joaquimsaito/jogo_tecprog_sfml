#include "Chao.h"

using namespace Entidades;

Chao::Chao(const sf::Vector2f& pos, const sf::Vector2f& tam) : 
	Entidade() {
	estatico = true;
	corpo.setSize(tam);
	corpo.setFillColor(sf::Color(110, 80, 50));
	setPosicao(pos);
}

void Chao::executar() {
}
