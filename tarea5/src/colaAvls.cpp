/*5665788*/
#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/colaAvls.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodo *TLocalizador;

struct nodo {
  TAvl elem;
  TLocalizador sig;
  TLocalizador ant;
};

struct repColaAvls {
  TLocalizador inicio;
  TLocalizador fin;
  nat cant;
};

TColaAvls crearColaAvls() {
  TColaAvls res = new repColaAvls;
  res->inicio = res->fin = NULL;
  res->cant = 0;
  return res;
}

TColaAvls encolar(TAvl avl, TColaAvls c) {
  TLocalizador nod = new nodo;
  nod->elem = avl;
  nod->sig = nod->ant = NULL;
  if (estaVaciaColaAvls(c)) {
    c->inicio = c->fin = nod;
  } else {
    c->fin->sig = nod;
    c->fin = nod;
  }
  c->cant = c->cant + 1;
  return c;
}

TColaAvls desencolar(TColaAvls c) {
  if (estaVaciaColaAvls(c)) {
    return c;
  } else {
  	if (c->cant == 1) {
  		TLocalizador aux = c->inicio;
  		c->inicio = c->fin = NULL;
  		delete aux;
  	} else {
	    TLocalizador aux = c->inicio;
	    c->inicio = c->inicio->sig;
	    c->inicio->ant = NULL;
	    aux->sig = NULL;
	    delete aux;
	}
	c->cant = c->cant - 1;
	return c;
  }
}

void liberarColaAvls(TColaAvls c) {
  TLocalizador borrar;
  while (c->inicio != NULL) {
    borrar = c->inicio;
    c->inicio = c->inicio->sig;
    delete borrar;
  }
  delete c;
}

bool estaVaciaColaAvls(TColaAvls c) {
  return ((c->inicio == NULL) && (c->fin == NULL));
}

TAvl frente(TColaAvls c) {
  assert(!estaVaciaColaAvls(c));
  return c->inicio->elem;
}
