/*5665788*/
#include "../include/utils.h"
#include "../include/colaDePrioridad.h"
#include "../include/info.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodo *TNodo;    

struct nodo {
  bool pertenece;
  double prioridad;
  nat posicion;
};

struct repCP {
  TInfo *elems;
  nat rango;
  nat cant;
  TNodo *aux;
};

TColaDePrioridad crearCP(nat N) {
  TColaDePrioridad res = new repCP;
  res->elems = new TInfo[N + 1];
  res->rango = N;
  res->cant = 0;
  res->aux = new TNodo[N + 1];
  for (nat i = 1; i <= N; i++) {
    res->aux[i] = NULL;
  }
  return res;
}

nat rangoCP(TColaDePrioridad cp) {
  return cp->rango;
}

//Intercambia 2 posiciones de un arreglo
void intercambioAscendente(nat i, TColaDePrioridad &cp) { // FUNCION AUXILIAR
  TInfo aux = cp->elems[i];
  cp->elems[i] = cp->elems[i / 2];
  cp->elems[i / 2] = aux;
  cp->aux[natInfo(cp->elems[i])]->posicion = i;
  cp->aux[natInfo(cp->elems[i / 2])]->posicion = i / 2;
}

void filtradoAscendente(nat n, TColaDePrioridad &cp) { //FUNCION AUXILIAR
  while ((n != 1) && (realInfo(cp->elems[n]) < realInfo(cp->elems[n / 2]))) {
    intercambioAscendente(n, cp);
    n = n / 2;
  }
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  assert((1 <= elem && elem <= rangoCP(cp)) && !estaEnCP(elem, cp));
  TInfo dato = crearInfo(elem, valor);
  cp->cant++;
  cp->elems[cp->cant] = dato;
  cp->aux[elem] = new nodo;
  cp->aux[elem]->pertenece = true;
  cp->aux[elem]->prioridad = valor;
  cp->aux[elem]->posicion = cp->cant;
  filtradoAscendente(cp->cant, cp);
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
  return (cp->cant == 0);
}

nat prioritario(TColaDePrioridad cp) {
  assert(!estaVaciaCP(cp));
  return natInfo(cp->elems[1]);
}

//Intercambia el elemento prioritario con el ultimo del arreglo
void intercambiarPU(TColaDePrioridad &cp) { //FUNCION AUXILIAR
  TInfo aux = cp->elems[cp->cant];
  cp->elems[cp->cant] = cp->elems[1];
  cp->elems[1] = aux;
  cp->aux[natInfo(cp->elems[1])]->posicion = 1;
}

//Intercambia 2 posiciones de un arreglo
void intercambioDescendente(nat &i, TColaDePrioridad &cp) { //FUNCION AUXILIAR
  TInfo aux = cp->elems[i];
  if ((2*i <= cp->cant) && (2*i + 1 <= cp->cant)) {
    if (realInfo(cp->elems[2*i]) < realInfo(cp->elems[2*i + 1])) {
			if (realInfo(cp->elems[2*i]) < realInfo(cp->elems[i])) {
		    cp->elems[i] = cp->elems[2*i];
		    cp->elems[2*i] = aux;
		    cp->aux[natInfo(cp->elems[i])]->posicion = i;
		    cp->aux[natInfo(cp->elems[2*i])]->posicion = 2*i;
		    i = 2*i;
			} else i = cp->cant + 1;
    } else {
			if (realInfo(cp->elems[2*i + 1]) < realInfo(cp->elems[i])) {
		    cp->elems[i] = cp->elems[2*i + 1];
		    cp->elems[2*i + 1] = aux;
		    cp->aux[natInfo(cp->elems[i])]->posicion = i;
		    cp->aux[natInfo(cp->elems[2*i + 1])]->posicion = 2*i + 1;
		    i = 2*i + 1;
			} else i = cp->cant + 1;
    }
  } else if (2*i <= cp->cant) {
		if (realInfo(cp->elems[2*i]) < realInfo(cp->elems[i])) {
		  cp->elems[i] = cp->elems[2*i];
		  cp->elems[2*i] = aux;
		  cp->aux[natInfo(cp->elems[i])]->posicion = i;
		  cp->aux[natInfo(cp->elems[2*i])]->posicion = 2*i;
		  i = 2*i;
		} else i = cp->cant + 1;
  } else {
		if (realInfo(cp->elems[2*i + 1]) < realInfo(cp->elems[i])) {
		  cp->elems[i] = cp->elems[2*i + 1];
		  cp->elems[2*i + 1] = aux;
		  cp->aux[natInfo(cp->elems[i])]->posicion = i;
		  cp->aux[natInfo(cp->elems[2*i + 1])]->posicion = 2*i + 1;
		  i = 2*i + 1;
		} else i = cp->cant + 1;
  }
}

void filtradoDescendente(nat i, TColaDePrioridad &cp) { //FUNCION AUXILIAR
  while ((2*i <= cp->cant) || (2*i + 1 <= cp->cant)) {
    intercambioDescendente(i ,cp);
  }
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) {
  assert(!estaVaciaCP(cp));
  nat p = prioritario(cp);
  delete cp->aux[p];
  cp->aux[p] = NULL;
	if (cp->cant == 1) {
		liberarInfo(cp->elems[cp->cant]);
  	cp->cant--;
		return cp;
	}	else {
		intercambiarPU(cp);
		liberarInfo(cp->elems[cp->cant]);
		cp->cant--;
		filtradoDescendente(1, cp);
		return cp;
	}
}

bool estaEnCP(nat elem, TColaDePrioridad cp) {
  if (cp->aux[elem] == NULL) {
    return false;	
  } else return true;
}

double prioridad(nat elem, TColaDePrioridad cp) {
  assert(estaEnCP(elem, cp));
  return cp->aux[elem]->prioridad;
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  assert(estaEnCP(elem, cp));
  TInfo info = crearInfo(elem, valor);
  nat p = cp->aux[elem]->posicion;
	liberarInfo(cp->elems[p]);
  cp->elems[p] = info;
  cp->aux[elem]->prioridad = valor;
  filtradoAscendente(p, cp);
  filtradoDescendente(p, cp);
  return cp;
}

void liberarCP(TColaDePrioridad cp) {
  for (nat i = 1; i <= cp->cant; i++) {
    liberarInfo(cp->elems[i]);
  }
  delete[] cp->elems;
	for (nat j = 1; j <= cp->rango; j++) {
		delete cp->aux[j];
	}
  delete[] cp->aux;
  delete cp;
}
