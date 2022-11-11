/*5665788*/
#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct repBinario {
  TInfo dato;
  TBinario izq;
  TBinario der;
};

TBinario crearBinario() {
  return NULL;
}

TBinario crearNodo(TInfo elem) {
	TBinario nuevoNodo = new repBinario;
	nuevoNodo->dato = elem;
	nuevoNodo->der = NULL;
	nuevoNodo->izq = NULL;
	return nuevoNodo;
}

void insertar(TInfo i, TBinario &b) {
	if (b == NULL) {
    TBinario nodoNuevo = crearNodo(i);
   	b = nodoNuevo;
  } else {
	  nat raiz = natInfo(b->dato);
		if (natInfo(i) > raiz) {
			insertar(i, b->der);
		} else {
			insertar(i, b->izq);
   }
  }
}

TBinario insertarEnBinario(TInfo i, TBinario b) {
  assert(esVacioBinario(buscarSubarbol(natInfo(i), b)));
  insertar(i, b);
  return b;
}

TInfo mayor(TBinario b) {
  assert(!esVacioBinario(b));
  if (b->der == NULL) {
    return b->dato;
  } else {
    return mayor(b->der);
  }
}

void remover_mayor(TBinario &b) {
	if (b->der == NULL) {
  TBinario aux = b;
  b = b->izq;
  delete aux;
  } else if(b->der->der == NULL) {
      TBinario aux = b->der;
      b->der = b->der->izq;
      delete aux;
  }
  else {
    removerMayor(b->der);
  }
}

TBinario removerMayor(TBinario b) {
  assert(!esVacioBinario(b));
  remover_mayor(b);
  return b;
}

TBinario mayor_(TBinario &b) { //FUNCION AUXILIAR
  if (b->der == NULL) {
    return b;
  } else if (b->der->der == NULL) {
    return b;
  } else {
		return mayor_(b->der);
	}
}

TBinario menor_(TBinario &b) { //FUNCION AUXILIAR
  if (b->izq == NULL) {
    return b;
  } else if (b->izq->izq == NULL) {
    return b;
  } else {
		return menor_(b->izq);
	}
}

void eliminarNodo(TBinario &b) { //FUNCION AUXILIAR
  if ((b->izq == NULL) && (b->der == NULL)) {
    liberarInfo(b->dato);
    delete b;
    b = NULL;
  } else if (b->izq == NULL) {
    TBinario aux0 = menor_(b->der);
		if (aux0->izq == NULL) {
			TInfo n = crearInfo(natInfo(aux0->dato), realInfo(aux0->dato));
			liberarInfo(b->dato);
		  b->dato = n;
		  liberarInfo(aux0->dato);
			b->der = aux0->der;
			delete aux0;
		} else {
			TInfo m = crearInfo(natInfo(aux0->izq->dato), realInfo(aux0->izq->dato));
			liberarInfo(b->dato);
			b->dato = m;
			liberarInfo(aux0->izq->dato);
			TBinario b1 = aux0->izq;
			aux0->izq = aux0->izq->der;
			delete b1;
		}
  } else {
    TBinario aux = mayor_(b->izq);
		if (aux->der == NULL) {
			TInfo n1 = crearInfo(natInfo(aux->dato), realInfo(aux->dato));
			liberarInfo(b->dato);
		  b->dato = n1;
		  liberarInfo(aux->dato);
			b->izq = aux->izq;
			delete aux;
		} else {
			TInfo m2 = crearInfo(natInfo(aux->der->dato), realInfo(aux->der->dato));
			liberarInfo(b->dato);
			b->dato = m2;
			liberarInfo(aux->der->dato);
			TBinario b2 = aux->der;
			aux->der = aux->der->izq;
			delete b2;
		}
  }
}

void remover(nat elem, TBinario &b) { //FUNCION AUXILIAR
  if (b == NULL) {
    return;
  } else if (elem < natInfo(b->dato)) {
    return remover(elem, b->izq);
  } else if (elem > natInfo(b->dato)) {
    return remover(elem, b->der);
  } else {
    eliminarNodo(b);
  }
}

TBinario removerDeBinario(nat elem, TBinario b) {
  assert(!esVacioBinario(buscarSubarbol(elem, b)));
  remover(elem, b);
  return b;
}

void liberarBinario(TBinario b) {
  if (b == NULL) {
    return;
  } else {
    liberarBinario(b->izq);
    liberarBinario(b->der);
    liberarInfo(b->dato);
    delete b;
  }
}

bool esVacioBinario(TBinario b) {
  return (b == NULL);
}

int altura(TBinario b) {
	if (b == NULL) {
    return 0;
  } else {
    int alturaIzq = altura(b->izq);
    int alturaDer = altura(b->der);
		if (((alturaIzq == 0) && (b->izq != NULL)) || ((alturaDer == 0) && (b->der != NULL))) {
			return 0;
		} else {    
			if ((alturaIzq - alturaDer > -2) && (alturaIzq - alturaDer < 2)) {
		    if (alturaIzq > alturaDer) {
					return alturaIzq + 1;
				} else {
					return alturaDer + 1;
				}
		  } else {
		    return 0;
		  }
		}
  }
}

bool esAvl(TBinario b) {
  if (b == NULL) {
    return true;
  } else {
		return altura(b); 
  }
}

TInfo raiz(TBinario b) {
  assert(!esVacioBinario(b));
  return b->dato;
}

TBinario izquierdo(TBinario b) {
  assert(!esVacioBinario(b));
  return b->izq;
}

TBinario derecho(TBinario b) {
  assert(!esVacioBinario(b));
  return b->der;
}

bool pertenece(nat elem, TBinario b) {
  if (esVacioBinario(b)) {
    return false;
  } else if (elem < natInfo(b->dato)) {
    return pertenece(elem, b->izq);
  } else if (elem > natInfo(b->dato)) {
    return pertenece(elem, b->der);
  } else {
    return true;
  }
}

TBinario buscarSubarbol(nat elem, TBinario b) {
  if (!pertenece(elem, b)) {
    return NULL;
  } else if (elem < natInfo(b->dato)) {
    return buscarSubarbol(elem, b->izq);
  } else if (elem > natInfo(b->dato)) {
    return buscarSubarbol(elem, b->der);
  } else {
    return b;
  }
}

nat alturaBinario(TBinario b) {
  if (b == NULL) {
    return 0;
  } else {
    nat alturaIzq = alturaBinario(b->izq);
    nat alturaDer = alturaBinario(b->der);
    if (alturaIzq >= alturaDer) {
      return alturaIzq + 1;
    } else {
      return alturaDer + 1;
    }
  }
}

nat cantidadBinario(TBinario b) {
  if (b == NULL) {
    return 0;
  } else {
    return 1 + cantidadBinario(b->izq) + cantidadBinario(b->der);
  }
}

void sumaUltimosPositivos_(nat i, nat &cont, double &suma, TBinario b) { //FUNCION AUXILIAR
  if ((cont < i) && (b != NULL)) {
    sumaUltimosPositivos_(i, cont, suma, b->der);
		if ((realInfo(b->dato) > 0) && (cont < i)) {
		  suma = suma + realInfo(b->dato);
		  cont++;	
		}
    sumaUltimosPositivos_(i, cont, suma, b->izq);
  }
}

double sumaUltimosPositivos(nat i, TBinario b) {
  nat cont = 0;
  double suma = 0;
  sumaUltimosPositivos_(i, cont, suma, b);
  return suma;
}

void linealizacion_(TCadena &res, TBinario b) { //FUNCION AUXILIAR
  if (b == NULL) {
    return;
  } else {
    linealizacion_(res, b->izq);
    TInfo aux = crearInfo(natInfo(b->dato), realInfo(b->dato));
    res = insertarAlFinal(aux, res);
    linealizacion_(res, b->der);
  }
}

TCadena linealizacion(TBinario b) {
  TCadena res = crearCadena();
  linealizacion_(res, b);
  return res;
}

void menores_(double cota, TBinario &res, TBinario b) {
  if (b == NULL) {
    return;
  } else {
    if (realInfo(b->dato) < cota) {
      TInfo aux = crearInfo(natInfo(b->dato), realInfo(b->dato));
      res = insertarEnBinario(aux, res);
    }
    menores_(cota, res, b->izq);
    menores_(cota, res, b->der);
  }
}

TBinario menores(double cota, TBinario b) {
  TBinario res = crearBinario();
  menores_(cota, res, b);
  return res;
}

void imprimir(TBinario b, int cont) {
	if (b == NULL) {
    printf("\n");
  } else {
  imprimir(b->der, cont+1);
  for (int i = 0; (i < cont); i++) {
    printf("-");
  }
  printf("(%d,%4.2lf)",natInfo(b->dato), realInfo(b->dato));
  imprimir(b->izq, cont+1);
	}
}

void imprimirBinario(TBinario b) {
  int cont = 0;
	imprimir(b, cont);
}
