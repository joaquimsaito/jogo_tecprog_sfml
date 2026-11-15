#include "Gerenciador_Grafico.h"
#include "../Ente.h"
#include<optional>

using namespace Gerenciadores;

Gerenciador_Grafico::Gerenciador_Grafico() :
	pJanela(new sf::RenderWindow(sf::VideoMode({ 800u, 600u }), "Jogo++")),
	relogio(),
	dt(0.f) {
	pJanela->setFramerateLimit(60);
}

Gerenciador_Grafico::~Gerenciador_Grafico() {
	if (pJanela) {
		if (pJanela->isOpen())
			pJanela->close();
		delete pJanela;
		pJanela = nullptr;
	}
}

void Gerenciador_Grafico::desenharEnte(Ente* pE) {
	if (pE && pJanela) {
		sf::Drawable* pFig = pE->getFigura();
		if (pFig)
			pJanela->draw(*pFig);
	}
}

const bool Gerenciador_Grafico::janelaAberta() const {
	return pJanela && pJanela->isOpen();
}

void Gerenciador_Grafico::tratarEventos() {
	while (const std::optional<sf::Event> evento = pJanela->pollEvent()) {
		if (evento->is<sf::Event::Closed>())
			pJanela->close();
	}
}

void Gerenciador_Grafico::limpar() {
	pJanela->clear(sf::Color(30, 30, 45));
}

void Gerenciador_Grafico::mostrar() {
	pJanela->display();
}

void Gerenciador_Grafico::atualizarTempo() {
	dt = relogio.restart().asSeconds();
	if (dt > 0.05f)
		dt = 0.05f;
}

const sf::Vector2u Gerenciador_Grafico::getTamanhoJanela() const {
	return pJanela->getSize();
}
