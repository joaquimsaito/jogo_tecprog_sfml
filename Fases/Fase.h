#pragma once

#include <SFML/Graphics.hpp>
#include "../Ente.h"
#include "../Listas/ListaEntidades.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"

namespace Entidades {
    namespace Personagens {
        class Jogador;
    }
}

namespace Fases {

    class Fase : public Ente {
    protected:
        static const float ALTURA_CHAO;

        Listas::ListaEntidades lista_ents;   // dona das entidades do cenario
        Gerenciadores::Gerenciador_Colisoes GC;

        // o Jogador ta pertencendo ao Jogo; a Fase so conhece ele (N deleta)
        Entidades::Personagens::Jogador* pJog1;

        sf::Vector2f tamanhoMundo;
        sf::Vector2f posInicialJogador;

        void criarChao();
        void criarInimFaceis();
        void criarPlataformas();
        void criarCenario(); // chao + obstaculos + inimigos

        virtual void criarInimigos() = 0;
        virtual void criarObstaculos() = 0;

    public:
        Fase();
        virtual ~Fase();

        // executa as entidades, resolve colisoes e desenha
        void executar();

        void setJogador(Entidades::Personagens::Jogador* pJ);
    };
}
