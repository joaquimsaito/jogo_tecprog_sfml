#include "Gerenciador_Colisoes.h"
#include "../Entidades/Chao.h"
#include "../Entidades/Jogador.h"
#include "../Entidades/Inimigo.h"
#include "../Entidades/Obstaculo.h"

#include <algorithm>

using namespace Gerenciadores;

Gerenciador_Colisoes::Gerenciador_Colisoes() :
	LIs(),
	LOs(),
	pJog1(nullptr),
	pChao(nullptr),
	limitesMundo(0.f, 0.f)
{
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
	LIs.clear();
	LOs.clear();
	pJog1 = nullptr;
	pChao = nullptr;
}


void Gerenciador_Colisoes::setJogador(Entidades::Personagens::Jogador* pJ) {
	if (pJ) pJog1 = pJ;
}

void Gerenciador_Colisoes::setChao(Entidades::Chao* pC) {
	if (pC) pChao = pC;
}

void Gerenciador_Colisoes::setLimitesMundo(const sf::Vector2f& limites) {
	limitesMundo = limites;
}

DadosColisao Gerenciador_Colisoes::calcularColisaoAABB(
	const Entidades::Entidade* pE1,
	const Entidades::Entidade* pE2
) const {
	DadosColisao resultado;
	if (!pE1 || !pE2) return resultado;

	const sf::Vector2f p1 = pE1->getPosicao();
	const sf::Vector2f t1 = pE1->getTamanho();
	const sf::Vector2f p2 = pE2->getPosicao();
	const sf::Vector2f t2 = pE2->getTamanho();

	const bool colisao =
		p1.x < p2.x + t2.x && p1.x + t1.x > p2.x &&
		p1.y < p2.y + t2.y && p1.y + t1.y > p2.y;

	if (!colisao) return resultado;

	resultado.houveColisao = true;
	resultado.sobreposicaoX = std::min(p1.x + t1.x, p2.x + t2.x) - std::max(p1.x, p2.x);
	resultado.sobreposicaoY = std::min(p1.y + t1.y, p2.y + t2.y) - std::max(p1.y, p2.y);
	return resultado;
}

void Gerenciador_Colisoes::pousarNoChao(Entidades::Personagens::Personagem* pPer) {
	if (!pChao || !pPer) return;
	if (!calcularColisaoAABB(pPer, pChao).houveColisao) return;

	sf::Vector2f pos = pPer->getPosicao();
	pos.y = pChao->getPosicao().y - pPer->getTamanho().y;
	pPer->setPosicao(pos);

	sf::Vector2f vel = pPer->getVelocidade();
	if (vel.y > 0.f) vel.y = 0.f;
	pPer->setVelocidade(vel);
	pPer->setNoChao(true);
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
	//...a colisao deve ser tratada em obstacularizar!
	if (!pJog1) return;

	for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
		Entidades::Obstaculos::Obstaculo* pObs = *it;
		if (pObs && pObs->getAtivo() && calcularColisaoAABB(pJog1, pObs).houveColisao)
			pObs->obstaculizar(pJog1);
	}
}

void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
	//...a colisao deve ser tratada em colidir (pisao) e em danificar (dano)!
	if (!pJog1) return;

	for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); ++it) {
		Entidades::Personagens::Inimigo* pInim = *it;
		if (!pInim || pInim->getNeutralizado()) continue;
		if (calcularColisaoAABB(pJog1, pInim).houveColisao)
			pJog1->colidir(pInim);
	}
}

void Gerenciador_Colisoes::tratarColisoesInimgsObstacs() {
	for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); ++it) {
		Entidades::Personagens::Inimigo* pInim = *it;
		if (!pInim || pInim->getNeutralizado()) continue;

		for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator ito = LOs.begin(); ito != LOs.end(); ++ito) {
			Entidades::Obstaculos::Obstaculo* pObs = *ito;
			if (pObs && pObs->getAtivo() && calcularColisaoAABB(pInim, pObs).houveColisao) {
				if (pObs->bloquear(pInim)) pInim->inverterDirecao(); //so a colisao lateral inverte o sentido
			}
		}
	}
}

void Gerenciador_Colisoes::tratarLimitesDoMundo() {
	if (limitesMundo.x <= 0.f) return;

	if (pJog1) {
		sf::Vector2f pos = pJog1->getPosicao();
		const float larg = pJog1->getTamanho().x;
		if (pos.x < 0.f) pos.x = 0.f;
		else if (pos.x + larg > limitesMundo.x) pos.x = limitesMundo.x - larg;
		pJog1->setPosicao(pos);
	}

	for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); ++it) {
		Entidades::Personagens::Inimigo* pInim = *it;
		if (!pInim || pInim->getNeutralizado()) continue;

		sf::Vector2f pos = pInim->getPosicao();
		const float larg = pInim->getTamanho().x;
		if (pos.x < 0.f) {
			pos.x = 0.f;
			if (pInim->getVelocidade().x < 0.f) pInim->inverterDirecao();
		}
		else if (pos.x + larg > limitesMundo.x) {
			pos.x = limitesMundo.x - larg;
			if (pInim->getVelocidade().x > 0.f) pInim->inverterDirecao();
		}
		pInim->setPosicao(pos);
	}
}

void Gerenciador_Colisoes::descartarInimigosCaidos() {
	std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin();
	while (it != LIs.end()) {
		if ((*it)->getNeutralizado() && (*it)->getPosicao().y > limitesMundo.y)
			it = LIs.erase(it);
		else
			++it;
	}
}

void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi) {
	if (pi) LIs.push_back(pi);
}

void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* po) {
	if (po) LOs.push_back(po);
}

void Gerenciador_Colisoes::executar() {
	pousarNoChao(pJog1);
	for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); ++it) {
		if (*it && !(*it)->getNeutralizado()) pousarNoChao(*it);
	}

	tratarColisoesJogsObstacs();
	tratarColisoesInimgsObstacs();
	tratarColisoesJogsInimgs();
	tratarLimitesDoMundo();
	descartarInimigosCaidos();
}
