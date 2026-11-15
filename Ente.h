#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"

class Ente {
protected:
    static Gerenciadores::Gerenciador_Grafico* pGerenciadorGrafico;
	sf::Drawable* pFig;//
public:
	Ente() : pFig(nullptr) {};
	virtual ~Ente() { pFig = nullptr; };

	void desenhar() {
		if(pGerenciadorGrafico)
			pGerenciadorGrafico->desenharEnte(this);
	}
	static void setGerenciadorGrafico(Gerenciadores::Gerenciador_Grafico* pGG) {
		pGerenciadorGrafico = pGG;
	}
	sf::Drawable* getFigura() const { return pFig; }//
	virtual void executar() = 0;
};