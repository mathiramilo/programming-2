/*5665788*/
#include "../include/utils.h"
#include "../include/mapping.h"
#include "../include/info.h"
#include "../include/cadena.h"

#include <assert.h>
#include <stdlib.h>

struct repMap {
  TCadena *elems;
  nat cant;
  nat capacidad;
};

TMapping crearMap(nat M) {
  TMapping res = new repMap;
  res->elems = new TCadena[M];
  for (nat i = 0; i < M; i++) {
    res->elems[i] = NULL;
  }
  res->cant = 0;
  res->capacidad = M;
  return res;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
  assert(!estaLlenoMap(map) && !existeAsociacionEnMap(clave, map));
  TInfo n = crearInfo(clave, valor);
  if (map->elems[clave % map->capacidad] == NULL) {
    map->elems[clave % map->capacidad] = crearCadena();
  }
  map->elems[clave % map->capacidad] = insertarAlFinal(n, map->elems[clave % map->capacidad]);
  map->cant++;
  return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
  assert(existeAsociacionEnMap(clave, map));
  TLocalizador aux = inicioCadena(map->elems[clave % map->capacidad]);
  while (natInfo(infoCadena(aux, map->elems[clave % map->capacidad])) != clave) {
    aux = siguiente(aux, map->elems[clave % map->capacidad]);
  }
  map->elems[clave % map->capacidad] = removerDeCadena(aux, map->elems[clave % map->capacidad]);
  map->cant--;
  if (esVaciaCadena(map->elems[clave % map->capacidad])) {
    liberarCadena(map->elems[clave % map->capacidad]);
    map->elems[clave % map->capacidad] = NULL;
  }
  return map;
}

bool existeAsociacionEnMap(nat clave, TMapping map) {
  if (map->elems[clave % map->capacidad] == NULL) {
    return false;
  } else {
    TLocalizador aux = inicioCadena(map->elems[clave % map->capacidad]);
    while (aux != NULL && natInfo(infoCadena(aux, map->elems[clave % map->capacidad])) != clave) {
      aux = siguiente(aux, map->elems[clave % map->capacidad]);
    }
    if (aux != NULL) {
      return true;
    } else {
      return false;
    }
  }
}

double valorEnMap(nat clave, TMapping map) {
  assert(existeAsociacionEnMap(clave, map));
  TLocalizador aux = inicioCadena(map->elems[clave % map->capacidad]);
  while (natInfo(infoCadena(aux, map->elems[clave % map->capacidad])) != clave) {
    aux = siguiente(aux, map->elems[clave % map->capacidad]);
  }
  return realInfo(infoCadena(aux, map->elems[clave % map->capacidad]));
}

bool estaLlenoMap(TMapping map) {
  if (map->cant == map->capacidad) {
    return true;
  } else {
    return false;
  }
}

void liberarMap(TMapping map) {
  for (nat i = 0; i < map->capacidad; i++) {
    if (map->elems[i] != NULL) {	
    	liberarCadena(map->elems[i]);
    }	
  }
  delete[] map->elems;
  delete map;
}
