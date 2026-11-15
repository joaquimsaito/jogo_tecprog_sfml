#pragma once

#include <list>
#include <vector>

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

        float larguraMundo; // informado pela Fase

        DadosColisao calcularColisaoAABB(
            const Entidades::Entidade* pE1,
            const Entidades::Entidade* pE2
        ) const;

        std::vector<Entidades::Personagens::Personagem*> coletarPersonagens() const;

        void resolverColisaoPersonagemSolido(
            Entidades::Personagens::Personagem* pPer,
            const Entidades::Entidade* pSolido,
            const DadosColisao& colisao
        );

        void resolverColisaoVertical(
            Entidades::Personagens::Personagem* pPer,
            const Entidades::Entidade* pSolido,
            const DadosColisao& colisao
        );

        void resolverColisaoHorizontal(
            Entidades::Personagens::Personagem* pPer,
            const Entidades::Entidade* pSolido,
            const DadosColisao& colisao
        );

        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesInimgsObstacs();
        void tratarLimitesDoMundo();

    public:
        Gerenciador_Colisoes();
        ~Gerenciador_Colisoes();

        void setJogador(Entidades::Personagens::Jogador* pJ) { pJog1 = pJ; }
        void setChao(Entidades::Chao* pC) { pChao = pC; }
        void setLarguraMundo(const float largura) { larguraMundo = largura; }

        void incluirInimigo(Entidades::Personagens::Inimigo* pi);
        void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);

        void executar();
    };
}
