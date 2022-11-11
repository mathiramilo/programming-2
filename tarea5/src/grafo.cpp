/*5665788*/
#include "../include/grafo.h"
#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/info.h"
#include "../include/binario.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct repGrafo {
  TBinario *vertices;
  nat cantV;
  nat rangoA;
  nat cantA;
};

TGrafo crearGrafo(nat N, nat M) {
  TGrafo res = new repGrafo;
  res->vertices = new TBinario[N + 1];
  for (nat i = 1; i <= N; i++) {
    res->vertices[i] = crearBinario();
  }
  res->cantV = N;
  res->rangoA = M;
  res->cantA = 0;
  return res;
}

nat cantidadVertices(TGrafo g) {
  return g->cantV;
}

bool hayMParejas(TGrafo g) {
  return (g->rangoA == g->cantA);
}

TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g) {
  assert((1 <= v1) && (v2 <= g->cantV) && (v1 != v2) && !sonVecinos(v1, v2, g) && !hayMParejas(g) && (d >= 0));
  TInfo arista1 = crearInfo(v2, d);
  TInfo arista2 = crearInfo(v1, d);
  g->vertices[v1] = insertarEnBinario(arista1, g->vertices[v1]);
  g->vertices[v2] = insertarEnBinario(arista2, g->vertices[v2]);
  g->cantA++;
	return g;
}

bool sonVecinos(nat v1, nat v2, TGrafo g) {
  assert((1 <= v1) && (v2 <= g->cantV));
  if (buscarSubarbol(v2, g->vertices[v1]) != NULL) {
    return true;
  } else {
    return false;
  }
}

double distancia(nat v1, nat v2, TGrafo g) {
  assert(sonVecinos(v1, v2, g) && (1 <= v1) && (v2 <= g->cantV));
  return realInfo(raiz(buscarSubarbol(v2, g->vertices[v1])));
}

void vecinos_(nat v, TIterador &iter, TBinario g) { //FUNCION AUXILIAR
  if (g == NULL) {
    return;
  } else {
    vecinos_(v, iter, izquierdo(g));
    iter = agregarAIterador(natInfo(raiz(g)), iter);
    vecinos_(v, iter, derecho(g));
  }
}

TIterador vecinos(nat v, TGrafo g) {
  assert((1 <= v) && (v <= g->cantV));
  TIterador res = crearIterador();
  vecinos_(v, res, g->vertices[v]);
  res = reiniciarIterador(res);
  return res;
}

void liberarGrafo(TGrafo g) {
  for (nat i = 1; i <= g->cantV; i++) {
    liberarBinario(g->vertices[i]);
  }
  delete[] g->vertices;
  delete g;
}
