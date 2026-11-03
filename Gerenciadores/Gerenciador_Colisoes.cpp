#include "Gerenciador_Colisoes.h"
#include <algorithm>

using namespace Gerenciadores;

Gerenciador_Colisoes::Gerenciador_Colisoes() :
	pJogador1(nullptr),
	pChao(nullptr) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
	pJogador1 = nullptr;
	pChao = nullptr;
}

const bool Gerenciador_Colisoes::verificaColisao(Entidades::Entidade* pE1, Entidades::Entidade* pE2) const {
	if (!pE1 || !pE2)
		return false;

	const sf::Vector2f p1 = pE1->getPosicao(), t1 = pE1->getCorpo().getSize();
	const sf::Vector2f p2 = pE2->getPosicao(), t2 = pE2->getCorpo().getSize();

	return (p1.x < p2.x + t2.x) && (p1.x + t1.x > p2.x) &&
		(p1.y < p2.y + t2.y) && (p1.y + t1.y > p2.y);
}

void Gerenciador_Colisoes::tratarColisoesJogsChao() {
	if (!verificaColisao(pJogador1, pChao))
		return;

	const sf::Vector2f pj = pJogador1->getPosicao(), tj = pJogador1->getCorpo().getSize();
	const sf::Vector2f pc = pChao->getPosicao(), tc = pChao->getCorpo().getSize();

	const float sobreposX = std::min(pj.x + tj.x, pc.x + tc.x) - std::max(pj.x, pc.x);
	const float sobreposY = std::min(pj.y + tj.y, pc.y + tc.y) - std::max(pj.y, pc.y);

	sf::Vector2f novaPos = pj;
	sf::Vector2f vel = pJogador1->getVelocidade();

	if (sobreposX < sobreposY) {
		if (pj.x + tj.x / 2.f < pc.x + tc.x / 2.f) novaPos.x -= sobreposX; // jogador a esquerda
		else                                       novaPos.x += sobreposX; // jogador a direita
		vel.x = 0.f;
	}
	else {
		if (pj.y + tj.y / 2.f < pc.y + tc.y / 2.f) {   // jogador por cima: pousou
			novaPos.y -= sobreposY;
			if (vel.y > 0.f) vel.y = 0.f;
			pJogador1->setNoChao(true);
		}
		else {                                         // bateu a cabeca por baixo
			novaPos.y += sobreposY;
			if (vel.y < 0.f) vel.y = 0.f;
		}
	}

	pJogador1->setPosicao(novaPos);
	pJogador1->setVelocidade(vel);
}

void Gerenciador_Colisoes::executar() {
	tratarColisoesJogsChao();
}