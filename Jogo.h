#pragma once

#include "Entidades/Jogador.h"
#include "Entidades/Chao.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"

class Jogo {
private:
    Gerenciadores::Gerenciador_Grafico GG;
    Gerenciadores::Gerenciador_Colisoes GC;
    Entidades::Personagens::Jogador* pJogador1;
    Entidades::Chao* pChao;

public:
    Jogo();
    ~Jogo();

    Jogo(const Jogo&) = delete;
    Jogo& operator=(const Jogo&) = delete;

    void executar();
};
