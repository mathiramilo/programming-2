/*5665788*/
#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/conjunto.h"

#include <assert.h>
#include <stdlib.h>

struct repConjunto {
  nat *elems;
  nat cant;
};

TConjunto crearConjunto() {
  TConjunto res = new repConjunto;
  res->elems = NULL;
  res->cant = 0;
  return res;
}

TConjunto singleton(nat elem) {
  TConjunto res = new repConjunto;
  res->elems = new nat[1];
  res->elems[0] = elem;
  res->cant = 1;
  return res;
}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2) {
  TConjunto res = new repConjunto;
  nat cont = 0, a1 = 0, a2 = 0;
  while ((a1 < c1->cant) || (a2 < c2->cant)) {
    if ((a1 < c1->cant) && (a2 < c2->cant)) {
      if (c1->elems[a1] < c2->elems[a2]) {
        cont++;
        a1++;
      } else if (c2->elems[a2] < c1->elems[a1]) {
        cont++;
        a2++;
      } else {
        cont++;
        a1++;
        a2++;
      }
    } else if (a1 < c1->cant) {
      cont++;
      a1++;
    } else {
      cont++;
      a2++;
    }
  }
  res->elems = new nat[cont];
  res->cant = cont;
  cont = 0; a1 = 0; a2 = 0;
  while ((a1 < c1->cant) || (a2 < c2->cant)) {
    if ((a1 < c1->cant) && (a2 < c2->cant)) {
      if (c1->elems[a1] < c2->elems[a2]) {
        res->elems[cont] = c1->elems[a1];
        cont++;
        a1++;
      } else if (c2->elems[a2] < c1->elems[a1]) {
        res->elems[cont] = c2->elems[a2];
        cont++;
        a2++;
      } else {
        res->elems[cont] = c1->elems[a1];
        cont++;
        a1++;
        a2++;
      }
    } else if (a1 < c1->cant) {
      res->elems[cont] = c1->elems[a1];
      cont++;
      a1++;
    } else {
      res->elems[cont] = c2->elems[a2];
      cont++;
      a2++;
    }
  }
  return res;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2) {
  TConjunto res = new repConjunto;
  nat cont = 0, a1 = 0, a2 = 0;
  while (a1 < c1->cant) {
    if ((a1 < c1->cant) && (a2 < c2->cant)) {
      if (c1->elems[a1] < c2->elems[a2]) {
        cont++;
        a1++;
      } else if (c2->elems[a2] < c1->elems[a1]) {
        a2++;
      } else {
        a1++;
        a2++;
      }
    } else if (a1 < c1->cant) {
      cont++;
      a1++;
    }
  }
  res->elems = new nat[cont];
  res->cant = cont;
  cont = 0; a1 = 0; a2 = 0;
  while (a1 < c1->cant) {
    if ((a1 < c1->cant) && (a2 < c2->cant)) {
      if (c1->elems[a1] < c2->elems[a2]) {
        res->elems[cont] = c1->elems[a1];
        cont++;
        a1++;
      } else if (c2->elems[a2] < c1->elems[a1]) {
        a2++;
      } else {
        a1++;
        a2++;
      }
    } else if (a1 < c1->cant) {
      res->elems[cont] = c1->elems[a1];
      cont++;
      a1++;
    }
  }
  return res;
}

//Binary search
bool perteneceAConjunto(nat elem, TConjunto c) {
  int low = 0, high = c->cant - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (elem == c->elems[mid]) {
      return true;
    } else if (elem < c->elems[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return false;
}

bool estaVacioConjunto(TConjunto c) {
  return c->cant == 0;
}

nat cardinalidad(TConjunto c) {
  return c->cant;
}

bool arregloCrecienteEsctricto(nat *elems, nat n) { //FUNCION AUXILIAR.
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

TConjunto arregloAConjunto(nat *elems, nat n) {
  assert(n > 0 && arregloCrecienteEsctricto(elems, n));
  TConjunto res = new repConjunto;
  res->elems = new nat[n];
  res->cant = n;
  for (nat i = 0; i < n; i++) {
    res->elems[i] = elems[i];
  }
  return res;
}

TIterador iteradorDeConjunto(TConjunto c) {
  TIterador iter = crearIterador();
  for (nat i = 0; i < c->cant; i++) {
    agregarAIterador(c->elems[i], iter);
  }
  iter = reiniciarIterador(iter);
  return iter;
}

void liberarConjunto(TConjunto c) {
  delete[] c->elems;
  delete c;
}
