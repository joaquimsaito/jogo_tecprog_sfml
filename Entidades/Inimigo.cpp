#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {

        Inimigo::Inimigo(const int nivelMaldade, const int vidas) :
            Personagem(vidas),
            nivel_maldade(nivelMaldade) {
        }

        Inimigo::~Inimigo() {
        }

        void Inimigo::neutralizar() {
            if (estaVivo())
                --num_vidas;
        }
    }
}
