#pragma once

namespace Listas {
    template <class TL>
    class Lista {
    public:
        class Elemento {
        private:
            Elemento* pProx;
            TL pInfo;
        public:
            Elemento(TL info) : pProx(nullptr), pInfo(info) {};
            ~Elemento() {};
            void setProx(Elemento* p) { pProx = p; };
            Elemento* getProx() const { return pProx; };
            TL getInfo() const { return pInfo; };
        };
    private:
        Elemento* pPrimeiro;
        Elemento* pUltimo;
    public:
        Lista() : pPrimeiro(nullptr), pUltimo(nullptr) {};
        ~Lista() { limpar(); };
        void incluir(TL info) {
            Elemento* pAux = new Elemento(info);
            if (!pPrimeiro) {
                pPrimeiro = pAux;
                pUltimo = pAux;
            }
            else {
                pUltimo->setProx(pAux);
                pUltimo = pAux;
            }
        };
        void remover(TL info) {
            Elemento* pAux = pPrimeiro;
            Elemento* pAnt = nullptr;
            while (pAux) {
                if (pAux->getInfo() == info) {
                    if (pAux == pPrimeiro) {
                        pPrimeiro = pAux->getProx();
                    }
                    else {
                        pAnt->setProx(pAux->getProx());
                    }
                    if (pAux == pUltimo) {
                        pUltimo = pAnt;
                    }
                    delete pAux;
                    return;
                }
                pAnt = pAux;
                pAux = pAux->getProx();
            }
        };
        void limpar() {
            Elemento* pAux = pPrimeiro;
            while (pAux) {
                Elemento* pDeletar = pAux;
                pAux = pAux->getProx();
                delete pDeletar;
            }
            pPrimeiro = nullptr;
            pUltimo = nullptr;
        };
        Elemento* getPrimeiro() const { return pPrimeiro; };
    };
};

