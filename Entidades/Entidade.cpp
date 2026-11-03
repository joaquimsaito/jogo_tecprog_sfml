#include "Entidade.h"

using namespace Entidades;
using namespace sf;

Entidade::Entidade() :
	Ente(),
	corpo(),
	posicao(0.f, 0.f),
	velocidade(0.f, 0.f),
	aceleracao(0.f, 0.f),
	velocidadeMaxima(0.f, 0.f),
	gravidade(500.f),
	estatico(false),
	noChao(false) {
	pFig = &corpo; // o que o Gerenciador_Grafico vai desenhar
}

void Entidade::aplicaGravidade() {
	if (estatico)
		return;

	const float dt = pGerenciadorGrafico ? pGerenciadorGrafico->getDeltaTime() : 0.f;

	velocidade.x += aceleracao.x * dt;
	velocidade.y += (aceleracao.y + gravidade) * dt;

	if (velocidadeMaxima.x > 0.f) {
		if (velocidade.x > velocidadeMaxima.x)  velocidade.x = velocidadeMaxima.x;
		if (velocidade.x < -velocidadeMaxima.x) velocidade.x = -velocidadeMaxima.x;
	}
	if (velocidadeMaxima.y > 0.f) {
		if (velocidade.y > velocidadeMaxima.y)  velocidade.y = velocidadeMaxima.y;
		if (velocidade.y < -velocidadeMaxima.y) velocidade.y = -velocidadeMaxima.y;
	}

	setPosicao(posicao + velocidade * dt);

	noChao = false;
}