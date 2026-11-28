#pragma once

#include <SFML/Graphics.hpp>
class Ente;

namespace Gerenciadores {
	class Gerenciador_Grafico {
	private:
		sf::RenderWindow* pJanela;
		sf::Clock relogio;
		float dt;

	public:
		Gerenciador_Grafico();
		~Gerenciador_Grafico();

		void desenharEnte(Ente* pE);

		const bool janelaAberta() const;
		void tratarEventos();
		void limpar();
		void mostrar();
		void atualizarTempo();
		const float getDeltaTime() const { return dt; }
		const sf::Vector2u getTamanhoJanela() const;
	};
}
