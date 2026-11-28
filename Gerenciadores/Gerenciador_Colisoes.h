#pragma once

#include <list>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace Entidades {
    class Entidade;
    class Chao;
    namespace Personagens {
        class Personagem;
        class Jogador;
        class Inimigo;
    }
    namespace Obstaculos {
        class Obstaculo;
    }
}

namespace Gerenciadores {

    // achei uma solucao elegante e organizada usar struct
    // NOVO: justificativa - calcularColisaoAABB() precisa devolver mais de um dado (houve colisao? quanto se sobrepoe em cada eixo?); a struct evita tres parametros de saida por referencia.
    struct DadosColisao {
        bool houveColisao;
        float sobreposicaoX;
        float sobreposicaoY;

        DadosColisao() :
            houveColisao(false),
            sobreposicaoX(0.f),
            sobreposicaoY(0.f) {
        }
    };

    class Gerenciador_Colisoes {
    private:
        std::vector<Entidades::Personagens::Inimigo*> LIs;
        std::list<Entidades::Obstaculos::Obstaculo*> LOs;
        Entidades::Personagens::Jogador* pJog1;

        Entidades::Chao* pChao; // excecao ao diagrama

        // NOVO: tamanho do mundo (informado pela Fase) para limitar personagens e descartar inimigos que cairam (comentario do Zlurp: "limites do mundo").
        sf::Vector2f limitesMundo;

        // so DETECTA: a resolucao fica em Obstaculo::bloquear()/obstaculizar(), Jogador::colidir() e Inimigo::danificar()
        DadosColisao calcularColisaoAABB(
            const Entidades::Entidade* pE1,
            const Entidades::Entidade* pE2
        ) const;

        // NOVO: Req. 9 - o chao (entidade, nao obstaculo) segura jogador e inimigos sob a gravidade.
        void pousarNoChao(Entidades::Personagens::Personagem* pPer);

        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesInimgsObstacs();
        void tratarLimitesDoMundo();
        // NOVO: decisao 5 - inimigo neutralizado que saiu do mundo pela base deixa de ser considerado (segue na lista da Fase).
        void descartarInimigosCaidos();

    public:
        Gerenciador_Colisoes();
        ~Gerenciador_Colisoes();

        void setJogador(Entidades::Personagens::Jogador* pJ);
        void setChao(Entidades::Chao* pC);
        void setLimitesMundo(const sf::Vector2f& limites);

        void incluirInimigo(Entidades::Personagens::Inimigo* pi);
        void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);

        void executar();
    };
}
