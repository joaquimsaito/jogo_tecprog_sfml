#pragma once

#include "Entidades/Jogador.h"
#include "Entidades/Chao.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"

class Jogo {
private:
	Gerenciadores::Gerenciador_Grafico GG; // composicao (como no diagrama): declarado primeiro, nasce antes dos demais
	// Provisorio: no diagrama o Gerenciador_Colisoes pertence a Fase (#GC). Enquanto nao ha Fase, fica aqui.
	Gerenciadores::Gerenciador_Colisoes GC;
	Entidades::Personagens::Jogador* pJogador1;
	// Provisorio: no diagrama seria um Obstaculo dentro da ListaEntidades da Fase.
	Entidades::Chao* pChao;
public:
	Jogo();
	~Jogo();
	void executar();
};