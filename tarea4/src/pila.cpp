/*5665788*/
#include "../include/utils.h"
#include "../include/pila.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodo *TLocalizador;

struct nodo {
  nat elem;
  TLocalizador sig;
  TLocalizador ant;
};

struct repPila {
  TLocalizador inicio;
  TLocalizador fin;
  nat max;
  nat cant;
};

TPila crearPila(nat tamanio) {
  TPila res = new repPila;
  res->inicio = res->fin = NULL;
  res->max = tamanio;
  res->cant = 0;
  return res;
}

TPila apilar(nat num, TPila p) {
  if (p->cant < p->max) {
    TLocalizador nod = new nodo;
    nod->elem = num;
    nod->sig = nod->ant = NULL;
    if (p->cant == 0) {
      p->inicio = p->fin = nod;
      p->cant = p->cant + 1;
    } else {
      nod->sig = p->inicio;
      p->inicio = nod;
      p->cant = p->cant + 1;
    }
  }
  return p;
}

TPila desapilar(TPila p) {
  if (p->cant != 0) {
    if (p->cant == 1) {
      delete p->inicio;
      p->inicio = p->fin = NULL;
      p->cant = 0;
    } else {
      TLocalizador eliminar = p->inicio;
      p->inicio = p->inicio->sig;
      p->inicio->ant = NULL;
      delete eliminar;
      p->cant = p->cant - 1;
    }
  }
  return p;
}

void liberarPila(TPila p) {
  TLocalizador borrar;
  while (p->inicio != NULL) {
    borrar = p->inicio;
    p->inicio = p->inicio->sig;
    delete borrar;
  }
  delete p;
}

bool estaVaciaPila(TPila p) {
  return (p->inicio == NULL);
}

bool estaLlenaPila(TPila p) {
  return (p->cant == p->max);
}

nat cima(TPila p) {
  assert(!estaVaciaPila(p));
  return p->inicio->elem;
}
