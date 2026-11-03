#pragma once

#include "../Entidades/Jogador.h"
#include "../Entidades/Chao.h"

namespace Gerenciadores {
	class Gerenciador_Colisoes {
	private:
		Entidades::Personagens::Jogador* pJogador1;
		Entidades::Chao* pChao;
	public:
		Gerenciador_Colisoes();
		~Gerenciador_Colisoes();
		void setJogador(Entidades::Personagens::Jogador* pJ) { if(pJ) pJogador1 = pJ; }
		void setChao(Entidades::Chao* pC) { if(pC) pChao = pC; }
		const bool verificaColisao(Entidades::Entidade* pE1, Entidades::Entidade* pE2) const;
		void tratarColisoesJogsChao();
		void executar();
	};
}