#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace Gerenciadores { class Gerenciador_Grafico; }

class Ente {
private:
	static int contadorId;

protected:
	int id;
	static Gerenciadores::Gerenciador_Grafico* pGG;
	sf::Drawable* pFig;

	// NOVO: dt fica no Gerenciador_Grafico (decisao 1, opcao A); Ente repassa a leitura sem exigir parametro em executar() (UML).
	const float getDt() const;
public:
	Ente();
	virtual ~Ente();

	static void setGG(Gerenciadores::Gerenciador_Grafico* pG);

	sf::Drawable* getFigura() const;
	int getId() const;

	void desenhar();
	virtual void executar() = 0;
};
