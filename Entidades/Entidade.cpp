#include "Entidade.h"

namespace Entidades {
    Entidade::Entidade() :
        Ente(),
        corpo(),
        posicao(0.f, 0.f) {
        pFig = &corpo;
    }
    Entidade::~Entidade() {
        pFig = nullptr;
    }
}
