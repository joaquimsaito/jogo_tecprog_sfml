#include "Obstaculo.h"
#include "Personagem.h"

#include <algorithm>

using namespace Entidades::Obstaculos;

Obstaculo::Obstaculo(const bool pDanoso) :
	Entidade(),
	danoso(pDanoso),
	ativo(true)
{
}

Obstaculo::~Obstaculo() {}


const bool Obstaculo::getDanoso() const {
	return danoso;
}

const bool Obstaculo::getAtivo() const {
	return ativo;
}

const bool Obstaculo::bloquear(Personagens::Personagem* pPer, const bool habilitaPulo) {
	if (!pPer || !ativo) return false;

	const sf::Vector2f tamObs = getTamanho();
	sf::Vector2f pos = pPer->getPosicao();
	const sf::Vector2f tam = pPer->getTamanho();

	//penetracao em cada eixo; resolve pelo eixo de menor penetracao
	const float sobreX = std::min(pos.x + tam.x, posicao.x + tamObs.x) - std::max(pos.x, posicao.x);
	const float sobreY = std::min(pos.y + tam.y, posicao.y + tamObs.y) - std::max(pos.y, posicao.y);
	if (sobreX <= 0.f || sobreY <= 0.f) return false;

	sf::Vector2f vel = pPer->getVelocidade();
	bool lateral = false;

	if (sobreY < sobreX) {
		if (pos.y + tam.y / 2.f < posicao.y + tamObs.y / 2.f) { //por cima do obstaculo
			pos.y -= sobreY;
			if (vel.y > 0.f) vel.y = 0.f;
			if (habilitaPulo) pPer->setNoChao(true);
		}
		else { //batendo a cabeca por baixo
			pos.y += sobreY;
			if (vel.y < 0.f) vel.y = 0.f;
		}
	}
	else {
		lateral = true;
		if (pos.x + tam.x / 2.f < posicao.x + tamObs.x / 2.f) pos.x -= sobreX;
		else pos.x += sobreX;
	}

	pPer->setPosicao(pos);
	pPer->setVelocidade(vel);
	return lateral;
}
