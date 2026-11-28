#pragma once

namespace Listas {
	template <class TL>

	class Lista {
	public:
		// NOVO: Elemento vira gabarito proprio (UML: "TE : Class" aninhado em Lista); corrige o TE indeclarado.
		template <class TE>
		class Elemento {
		private:
			Elemento<TE>* pProx;
			TE* pInfo; //TE precisa ser declarado de alguma forma, igual à TL (template <class TL>)?
		public:
			Elemento() :
				pProx(nullptr),
				pInfo(nullptr)
			{
				//...
			};
			~Elemento() {
				//...
				pProx = nullptr;
				pInfo = nullptr;
			};

			void incluir(TE* pEl) {
				//...
				pInfo = pEl;
			};
			void setProx(Elemento<TE>* pEl) {
				if (pEl) pProx = pEl;
			}
			Elemento<TE>* getProximo() const {
				return pProx;
			}
			// NOVO: UML (Elemento tem pinfo); necessario para ListaEntidades percorrer.
			TE* getInfo() const {
				return pInfo;
			}
		};
	private:
		Elemento<TL>* pPrimeiro;
		Elemento<TL>* pUltimo;
	public:
		Lista() :
			pPrimeiro(nullptr),
			pUltimo(nullptr)
		{
			//...
		}
		~Lista() {
			//...
			limpar();
		}
		void incluir(TL* pLis) {
			//...
			Elemento<TL>* pNovo = new Elemento<TL>();
			pNovo->incluir(pLis);
			if (!pPrimeiro) {
				pPrimeiro = pNovo;
				pUltimo = pNovo;
			}
			else {
				pUltimo->setProx(pNovo);
				pUltimo = pNovo;
			}
		};
		void limpar() {
			//...
			Elemento<TL>* pAux = pPrimeiro;
			while (pAux) {
				Elemento<TL>* pProx = pAux->getProximo();
				delete pAux; //libera so o elemento; quem possui a informacao decide se a destroi
				pAux = pProx;
			}
			pPrimeiro = nullptr;
			pUltimo = nullptr;
		}
		// NOVO: UML (Lista conhece Primeiro); permite percorrer a lista a partir de ListaEntidades.
		Elemento<TL>* getPrimeiro() const {
			return pPrimeiro;
		}
		//...
	};
}
