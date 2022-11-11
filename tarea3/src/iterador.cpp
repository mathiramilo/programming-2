/*5665788*/
#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodoIt *PNodoIt;
struct nodoIt {
  nat elem;
  PNodoIt sig;
};
struct repIterador {
  PNodoIt inicio, fin, actual;
  bool bloqueado;
};

TIterador crearIterador {
  TIterador res = new repIterador;
  res->actual = res->inicio = res->fin = NULL;
  res->bloqueado = false;
  return res;
}

TIterador agregarAIterador(nat elem, TIterador iter) {
  if (iter->bloqueado) {
    return iter;
  } else {
    PNodoIt aux = new nodoIt;
    aux->elem = elem;
    aux->sig = NULL;
    iter->inicio = iter->fin = aux;
    return iter;
  }
}

TIterador reiniciarIterador(TIterador iter) {
  if ((iter->inicio != NULL) && (iter->fin !=NULL)) {
    iter->actual = iter->inicio;
  }
  iter->bloqueado = true;
  return iter;
}

TIterador avanzarIterador(TIterador iter) {
  if (estaDefinidaActual(iter)) {
    iter->actual = iter->actual->sig;
  }
  return iter;
}

nat actualEnIterador(TIterador iter) {
  assert(estaDefinidaActual(iter));
  return iter->actual->elem;
}

bool estaDefinidaActual(TIterador iter) {
  if (iter->actual != NULL) {
    return true;
  } else {
    return false;
  }
}

void liberarIterador(TIterador iter) {
  reiniciarIterador(iter);
  TIterador a_borrar;
  while (iter->actual != NULL) {
    a_borrar = iter->actual;
    iter->actual = iter->actual->sig;
    delete a_borrar;
  }
  delete iter;
}
