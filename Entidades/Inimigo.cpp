#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {

        Inimigo::Inimigo(const int nivelMaldade) :
            Personagem(1),
            nivel_maldade(nivelMaldade) {
        }

        Inimigo::~Inimigo() {
        }

    }
}
