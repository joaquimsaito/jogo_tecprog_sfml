#pragma once

#include "Entidade.h"

namespace Entidades {
    namespace Personagens {
        class Jogador;
        class Personagem;
    }

    namespace Obstaculos {
        class Obstaculo : public Entidade {
        protected:
            bool danoso;
            // NOVO: false enquanto a Plataforma esta ausente (pisca e some): nao colide nem eh desenhada.
            bool ativo;

        public:
            Obstaculo(const bool pDanoso = false);
            virtual ~Obstaculo();

            const bool getDanoso() const;
            // NOVO: Gerenciador_Colisoes ignora obstaculos inativos (plataforma que sumiu faz quem esta em cima cair).
            const bool getAtivo() const;

            // NOVO: unica resolucao de "impedir que atravesse" (Plataforma e Gelatina) e da colisao inimigo x obstaculo (Req. 8/9); retorna true se foi colisao lateral.
            const bool bloquear(Personagens::Personagem* pPer, const bool habilitaPulo = true);

            virtual void executar() = 0;

            virtual void obstaculizar(Personagens::Jogador* pJ) = 0;
        };
    }
}
