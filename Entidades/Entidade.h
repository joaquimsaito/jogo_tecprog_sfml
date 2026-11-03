#pragma once

#include "../Ente.h"

namespace Entidades {
	class Entidade : public Ente {
	protected:
		sf::RectangleShape corpo;
		sf::Vector2f posicao;
		sf::Vector2f velocidade;
		sf::Vector2f aceleracao;
		sf::Vector2f velocidadeMaxima;
		float gravidade; //mudar pra static const
		bool estatico;
		bool noChao;
		void aplicaGravidade();
	public:
		Entidade();
		virtual ~Entidade() { pFig = nullptr; };

		void setCorpo(const sf::RectangleShape& c) { corpo = c; };
		void setPosicao(const sf::Vector2f& p) { posicao = p; corpo.setPosition(posicao); };
		void setVelocidade(const sf::Vector2f& v) { velocidade = v; };
		void setAceleracao(const sf::Vector2f& a) { aceleracao = a; };
		void setVelocidadeMaxima(const sf::Vector2f& vm) { velocidadeMaxima = vm; };
		void setGravidade(const float g) { gravidade = g; };
		void setEstatico(const bool e) { estatico = e; };
		void setNoChao(const bool c) { noChao = c; };

		const sf::RectangleShape& getCorpo() const { return corpo; };
		const sf::Vector2f getPosicao() const { return posicao; };
		const sf::Vector2f getVelocidade() const { return velocidade; };
		const sf::Vector2f getVelocidadeMaxima() const { return velocidadeMaxima; };
		const float getGravidade() const { return gravidade; };
		const bool getEstatico() const { return estatico; };
		const bool getNoChao() const { return noChao; }

		virtual void executar() = 0;
	};
}
