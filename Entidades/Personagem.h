#pragma once

#include "Entidade.h"

namespace Entidades {
	namespace Personagens {
		class Personagem : public Entidades::Entidade {
		protected:
		public:
			Personagem() : Entidade() {};
			~Personagem() {};
			virtual void executar() = 0;
			virtual void mover() = 0;
		};
	}
}