#include "ListaEntidades.h"

#include "../Entidades/Entidade.h"

using namespace Listas;

typedef Lista<Entidades::Entidade>::Elemento<Entidades::Entidade> ElementoEntidade;

ListaEntidades::ListaEntidades() :
	LEs()
{
}

// NOVO: a lista eh dona das entidades que recebe: destroi cada uma ao ser destruida.
ListaEntidades::~ListaEntidades() {
	limpar();
}

void ListaEntidades::incluir(Entidades::Entidade* pE) {
	if (pE) LEs.incluir(pE);
}

void ListaEntidades::executar() {
	ElementoEntidade* pEl = LEs.getPrimeiro();
	while (pEl) {
		Entidades::Entidade* pE = pEl->getInfo();
		if (pE) pE->executar();
		pEl = pEl->getProximo();
	}
}

void ListaEntidades::desenhar() {
	ElementoEntidade* pEl = LEs.getPrimeiro();
	while (pEl) {
		Entidades::Entidade* pE = pEl->getInfo();
		if (pE) pE->desenhar();
		pEl = pEl->getProximo();
	}
}

void ListaEntidades::limpar() {
	ElementoEntidade* pEl = LEs.getPrimeiro();
	while (pEl) {
		delete pEl->getInfo();
		pEl = pEl->getProximo();
	}
	LEs.limpar();
}
