#pragma once

#include "Personagem.h"

namespace Entidades {
    namespace Personagens {
        class Jogador;

        class Inimigo : public Personagem {
        protected:
            int nivel_maldade;
            int direcao; // +1 direita, -1 esquerda
            // NOVO: decisao 5 - inimigo sem vidas (pisao) deixa de colidir e cai do chao, mas segue na lista da Fase.
            bool neutralizado;

        public:
            Inimigo(const int nivelMaldade = 1, const int vidas = 1);
            virtual ~Inimigo();

            void setDirecao(const int d);

            const int getNivelMaldade() const;
            // NOVO: Gerenciador_Colisoes ignora inimigos neutralizados (decisao 5).
            const bool getNeutralizado() const;

            // NOVO: comentario do Zlurp - "inverte a direcao caso colida com algum obstaculo ou com os limites do mundo".
            void inverterDirecao();
            // NOVO: decisao 5 - cada pisao tira uma vida; retorna true se neutralizou (Jogador::colidir pontua com operator++).
            const bool neutralizar();

            virtual void executar() = 0;
            virtual void mover() = 0;
            virtual void danificar(Jogador* pJ) = 0;
        };
    }
}
