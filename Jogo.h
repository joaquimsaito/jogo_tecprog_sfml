#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"

namespace Entidades {
    namespace Personagens {
        class Jogador;
    }
}

namespace Fases {
    class Fase;
}

class Jogo {
private:
    Gerenciadores::Gerenciador_Grafico GG;
    Entidades::Personagens::Jogador* pJog1;
    Fases::Fase* pFase; // provisorio: so a Fase Primeira por enquanto


public:
    Jogo();
    ~Jogo();

    void executar();
};
