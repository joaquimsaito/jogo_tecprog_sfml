#pragma once

#include"Jogador.h"

namespace Entidades {
	namespace Obstaculos {
		class Obstaculo : public Entidade {
		protected:

		public:
			Obstaculo() : Entidade() {};
			virtual ~Obstaculo() {};
			virtual void executar() = 0;
			virtual void obstacularizar(Personagens::Jogador* pJ) = 0;
		};
	}
}
