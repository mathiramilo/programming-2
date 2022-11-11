/*5665788*/
#include "../include/utils.h"
#include "../include/avl.h"
#include "../include/iterador.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct repAvl {
  nat dato;
  nat altura;
  nat cant;
  TAvl izq;
  TAvl der;
};

TAvl crearAvl() {
  return NULL;
}

//Crea nodo con elem de dato
TAvl crearNodo(nat elem) { //FUNCION AUXILIAR
  TAvl res = new repAvl;
  res->dato = elem;
  res->cant = 1;
  res->altura = 1;
  res->der = res->izq = NULL;
  return res;
}

bool estaVacioAvl(TAvl avl) {
  return (avl == NULL);
}

//Rotacion simple izquierda
void RSI(TAvl &avl) { //FUNCION AUXILIAR
  TAvl aux = avl->izq;
  avl->izq = aux->der;
  aux->der = avl;
  avl->altura = fmax(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
  avl->cant = cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der) + 1;
  aux->altura = fmax(alturaDeAvl(aux->izq), avl->altura) + 1;
  aux->cant = cantidadEnAvl(aux->izq) + avl->cant + 1;
  avl = aux;
}

//Rotacion simple derecha
void RSD(TAvl &avl) { //FUNCION AUXILIAR
  TAvl aux = avl->der;
  avl->der = aux->izq;
  aux->izq = avl;
  avl->altura = fmax(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
  avl->cant = cantidadEnAvl(avl->der) + cantidadEnAvl(avl->izq) + 1;
  aux->altura = fmax(alturaDeAvl(aux->der), avl->altura) + 1;
  aux->cant = cantidadEnAvl(aux->der) + avl->cant + 1;
  avl = aux;
}

//Doble rotacion izquierda
void DRI(TAvl &avl) { //FUNCION AUXILIAR
  RSD(avl->izq);
  RSI(avl);
}

//Doble rotacion derecha
void DRD(TAvl &avl) { //FUNCION AUXILIAR
  RSI(avl->der);
  RSD(avl);
}

void insertar(nat elem, TAvl &avl) { //FUNCION AUXILIAR
  if (avl == NULL) {
    TAvl res = crearNodo(elem);
    avl = res;
  } else if (elem < avl->dato) {
    insertar(elem, avl->izq);
    if (alturaDeAvl(avl->izq) - alturaDeAvl(avl->der) == 2) {
      if (elem < avl->izq->dato) {
        RSI(avl);
      } else {
        DRI(avl);
      }
    }
  } else if (elem > avl->dato) {
    insertar(elem, avl->der);
    if (alturaDeAvl(avl->der) - alturaDeAvl(avl->izq) == 2) {
      if (elem > avl->der->dato) {
        RSD(avl);
      } else {
        DRD(avl);
      }
    }
  }
  avl->altura = fmax(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
  avl->cant = cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der) + 1;
}

TAvl insertarEnAvl(nat elem, TAvl avl) {
  assert(estaVacioAvl(buscarEnAvl(elem, avl)));
  insertar(elem, avl);
  return avl;
}

TAvl buscarEnAvl(nat elem, TAvl avl) {
  if (avl == NULL) {
    return NULL;
  } else if (elem < avl->dato) {
    return buscarEnAvl(elem, avl->izq);
  } else if (elem > avl->dato) {
    return buscarEnAvl(elem, avl->der);
  } else {
    return avl;
  }
}

nat raizAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->dato;
}

TAvl izqAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->izq;
}

TAvl derAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->der;
}

nat cantidadEnAvl(TAvl avl) {
  if (avl == NULL) {
  	return 0;
  } else 
  return avl->cant;
}

nat alturaDeAvl(TAvl avl) {
  if (avl == NULL) {
	return 0;
  } else	
  return avl->altura;
}

void enOrdenAvl_(TAvl avl, TIterador &iter) { //FUNCION AUXILIAR
  if (avl == NULL) {
    return;
  } else {
    enOrdenAvl_(avl->izq, iter);
    iter = agregarAIterador(avl->dato, iter);
    enOrdenAvl_(avl->der, iter);
  }
}

TIterador enOrdenAvl(TAvl avl) {
  TIterador res = crearIterador();
  enOrdenAvl_(avl, res);
  res = reiniciarIterador(res);
  return res;
}

//Funcion que verifica si un arreglo es creciente estricto
bool arregloCrecienteEsctricto_(nat *elems, nat n) { //FUNCION AUXILIAR
  if (n == 1) {
    return true;
  } else {
    nat i = 0;
    nat j = 1;
    while ((j != n) && (elems[i] < elems[j])) {
      if ((j + 1) != n) {
        j++;
      } else {
        i++;
        j = i + 1;
      }
    }
    if (j == n) {
      return true;
    } else {
      return false;
    }
  }
}

void arregloAAvl_(nat *elems, nat desde, nat hasta, TAvl &avl) { //FUNCION AUXILIAR
  if (hasta - desde != 0) {
    avl = crearNodo(elems[(hasta + desde - 1) / 2]);
    avl->cant = hasta - desde;
    nat i = 0;
    while (pow(2,i) <= avl->cant) {
      i++;
    }
    avl->altura = i;
    arregloAAvl_(elems, desde, (hasta + desde - 1) / 2, avl->izq);
    arregloAAvl_(elems, (hasta + desde + 1) / 2, hasta, avl->der);
  } else {
    return;
  }
}

TAvl arregloAAvl(nat *elems, nat n) {
  assert((n > 0) && arregloCrecienteEsctricto_(elems, n));
  TAvl res = crearAvl();
  arregloAAvl_(elems, 0, n, res);
  return res;
}

nat cantNodos(nat h) {
	if (h == 0) {
		return 0;
	} else if (h == 1) {
		return 1;
	} else {
		return (cantNodos(h-2) + cantNodos(h-1) + 1);
	}
}

void avlMin_(nat h, nat min, nat max, TAvl &avl) { //FUNCION AUXILIAR
	if (h == 0) {
		avl = NULL;
	} else if (h == 1) {
		avl = crearNodo(min);	
	}	else {		
		nat actual = cantNodos(h - 1) + min;
  	avl = crearNodo(actual);
		avl->altura = h;
		avl->cant = max - min + 1;
		avlMin_(h - 2, actual + 1, max, avl->der);
		avlMin_(h - 1, min, actual - 1,avl->izq);
	}  
}

TAvl avlMin(nat h) {
  TAvl res = crearAvl();
	nat max = cantNodos(h);
  avlMin_(h, 1, max, res);
  return res;
}

typedef TIterador *TIter; 

void avlArreglo(nat h, TAvl avl, TIter &elems) { //FUNCION AUXILIAR
  if (avl == NULL) {
    return;
  } else {
    elems[h] = agregarAIterador(avl->dato, elems[h]);
    avlArreglo(h - 1, avl->izq, elems);
    avlArreglo(h - 1, avl->der, elems);
  }
}

void imprimirIterador(TIterador iter) { //FUNCION AUXILIAR
  while (estaDefinidaActual(iter)) {
    printf("%d ", actualEnIterador(iter));
    avanzarIterador(iter);
  }
  printf("\n");
}

void imprimirAvl(TAvl avl) {
  if (avl == NULL) {
    return;
  } else {
    TIter elems = new TIterador[avl->altura + 1];
    for (nat i = 1; i <= avl->altura; i++) {
      elems[i] = crearIterador();
    }
    avlArreglo(avl->altura, avl, elems);
    for (nat j = 1; j <= avl->altura; j++) {
      elems[j] = reiniciarIterador(elems[j]);
    }
    for (nat h = 1; h <= avl->altura; h++) {
      imprimirIterador(elems[h]);
			liberarIterador(elems[h]);
    }
		delete[] elems; 
  }
}

void liberarAvl(TAvl avl) {
  if (avl == NULL) {
    return;
  } else {
    liberarAvl(avl->izq);
    liberarAvl(avl->der);
    delete avl;
  }
}
