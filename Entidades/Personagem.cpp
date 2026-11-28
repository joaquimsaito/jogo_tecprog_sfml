#include "Personagem.h"

using namespace Entidades::Personagens;

const float Personagem::GRAVIDADE(980.f);

Personagem::Personagem(const int vidas) :
	Entidade(),
	num_vidas(vidas),
	velocidade(0.f, 0.f),
	aceleracao(0.f, 0.f),
	velocidadeMaxima(0.f, 0.f),
	noChao(false),
	fatorAtrito(1.f)
{
}

Personagem::~Personagem() {}


void Personagem::setAceleracao(const sf::Vector2f& a) {
	aceleracao = a;
}

void Personagem::setVelocidadeMaxima(const sf::Vector2f& vm) {
	velocidadeMaxima = vm;
}

void Personagem::setVelocidade(const sf::Vector2f& v) {
	velocidade = v;
}

void Personagem::setNoChao(const bool c) {
	noChao = c;
}

void Personagem::setFatorAtrito(const float f) {
	fatorAtrito = f;
}

const int Personagem::getNumVidas() const {
	return num_vidas;
}

const sf::Vector2f Personagem::getVelocidade() const {
	return velocidade;
}

const sf::Vector2f Personagem::getVelocidadeMaxima() const {
	return velocidadeMaxima;
}

const bool Personagem::getNoChao() const {
	return noChao;
}

const bool Personagem::estaVivo() const {
	return num_vidas > 0;
}

void Personagem::integrar() {
	const float dt = getDt();

	velocidade.x += aceleracao.x * dt;
	velocidade.y += (aceleracao.y + GRAVIDADE) * dt;
	velocidade.x *= fatorAtrito;

	//velocidadeMaxima com componente 0 significa "sem limite" naquele eixo
	if (velocidadeMaxima.x > 0.f) {
		if (velocidade.x > velocidadeMaxima.x)  velocidade.x = velocidadeMaxima.x;
		if (velocidade.x < -velocidadeMaxima.x) velocidade.x = -velocidadeMaxima.x;
	}
	if (velocidadeMaxima.y > 0.f) {
		if (velocidade.y > velocidadeMaxima.y)  velocidade.y = velocidadeMaxima.y;
		if (velocidade.y < -velocidadeMaxima.y) velocidade.y = -velocidadeMaxima.y;
	}

	setPosicao(posicao + velocidade * dt);
	noChao = false; // quem confirma o apoio eh o GC
	fatorAtrito = 1.f;
}
