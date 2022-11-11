/*5665788*/
#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/conjunto.h"
#include "../include/grafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool *ArregloBools;

typedef double *ArregloDouble;

void accesibles_(nat v, ArregloBools &arrB, TGrafo g) { //FUNCION AUXILIAR
	arrB[v] = true;
	for (nat i = 1; i <= cantidadVertices(g); i++) {
		if (sonVecinos(v, i, g)) {
			if (!arrB[i]) {
				accesibles_(i, arrB, g);
			}
		}
	}
}

ArregloBools accesibles(nat v, TGrafo g) {
	ArregloBools res = new bool[cantidadVertices(g) + 1];
	for (nat i = 1; i <= cantidadVertices(g); i++) {
		res[i] = false;
	}
	accesibles_(v, res, g);
	return res;
}

ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g) {
	ArregloDoubles res = new double[1];	
	return res;
}

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2) {
	TConjunto union_ = unionDeConjuntos(c1, c2);
	TConjunto dif1 = diferenciaDeConjuntos(c1, c2);
	TConjunto dif2 = diferenciaDeConjuntos(c2, c1);
	TConjunto dif = unionDeConjuntos(dif1, dif2);
	TConjunto res = diferenciaDeConjuntos(union_, dif);
	liberarConjunto(union_);
	liberarConjunto(dif1);
	liberarConjunto(dif2);
	liberarConjunto(dif);
	return res;
}

TCadena nivelEnBinario(nat l, TBinario b) {
	assert(l > 0);
	TCadena res = crearCadena();
	if (!esVacioBinario(b) && (alturaBinario(b) >= l)) {
		if (l == 1) {
			TInfo info = crearInfo(natInfo(raiz(b)), realInfo(raiz(b)));
			res = insertarAlFinal(info, res);
		} else {
			if (!esVacioBinario(izquierdo(b))) {
				TCadena res1 = nivelEnBinario(l - 1, izquierdo(b));
				res = insertarSegmentoDespues(res1, finalCadena(res), res);
			}
			if (!esVacioBinario(derecho(b))) {
				TCadena res2 = nivelEnBinario(l - 1, derecho(b));
				res = insertarSegmentoDespues(res2, finalCadena(res), res);
			}
		}
	}
	return res;
}

bool esCamino_(TCadena c, TLocalizador loc, TBinario b) { //FUNCION AUXILIAR
	if (natInfo(raiz(b)) == natInfo(infoCadena(loc, c))) {
			if (esFinalCadena(loc, c)) {
				if (esVacioBinario(izquierdo(b)) && esVacioBinario(derecho(b))) {
					return true;
				} else return false;
			} else {
				if (natInfo(raiz(izquierdo(b))) == natInfo(infoCadena(siguiente(loc, c), c))) {
					return esCamino_(c, siguiente(loc, c), izquierdo(b));
				} else if (natInfo(raiz(derecho(b))) == natInfo(infoCadena(siguiente(loc, c), c))) {
					return esCamino_(c, siguiente(loc, c), derecho(b));
				} else {
					return false;
				}
			}
		} else return false;
}

bool esCamino(TCadena c, TBinario b) {
	if (esVacioBinario(b) && esVaciaCadena(c)) {
		return true;
	} else if (esVacioBinario(b)) {
		return false;
	} else if (esVaciaCadena(c)) {
		return true;
  } else {
		TLocalizador loc = inicioCadena(c);
		return esCamino_(c, loc, b);
  }
}

bool pertenece(nat elem, TCadena cad) {
	TLocalizador aux = inicioCadena(cad);
	while ((aux != NULL) && (natInfo(infoCadena(aux, cad)) != elem)) {
		aux = siguiente(aux, cad);
	}
	if (aux != NULL) {
		return 1;
	} else {
		return 0;
	}
}

nat longitud(TCadena cad) {
	nat cont = 0;
	TLocalizador aux = inicioCadena(cad);
	while (aux != NULL) {
		cont++;
		aux = siguiente(aux, cad);
	}
	return cont;
}

bool estaOrdenadaPorNaturales(TCadena cad) {
	if ((esVaciaCadena(cad)) || (longitud(cad) == 1)) {
		return 1;
	} else {
		TLocalizador aux = inicioCadena(cad);
		TLocalizador aux0 = siguiente(aux, cad);
		while ((aux0 != NULL) && (natInfo(infoCadena(aux, cad)) <= natInfo(infoCadena(aux0, cad)))) {
			if (siguiente(aux0, cad) != NULL) {
				aux0 = siguiente(aux0, cad);
			} else {
				aux = siguiente(aux, cad);
				aux0 = siguiente(aux, cad);
			}
		}
		if (aux0 != NULL) {
			return 0;
		} else {
			return 1;
		}
	}
}

bool hayNatsRepetidos(TCadena cad) {
	if (esVaciaCadena(cad) || (longitud(cad) == 1)) {
		return 0;
	} else {
	TLocalizador aux = inicioCadena(cad);
	TLocalizador aux0 = siguiente(aux, cad);
	while ((aux0 != NULL) && (natInfo(infoCadena(aux, cad)) != natInfo(infoCadena(aux0, cad)))) {
		if (siguiente(aux0, cad) != NULL) {
			aux0 = siguiente(aux0, cad);
		} else {
			aux = siguiente(aux, cad);
			aux0 = siguiente(aux, cad);
		}
	}
	if (aux0 != NULL) {
		return 1;
	} else {
		return 0;
	}
	}
}

bool sonIgualesCadena(TCadena c1, TCadena c2) {
	if (esVaciaCadena(c1) && esVaciaCadena(c2)) {
		return 1;
	} else {
		if (longitud(c1) != longitud(c2)) {
			return 0;
		} else {
			TLocalizador aux = inicioCadena(c1);
			TLocalizador aux0 = inicioCadena(c2);
			while ((aux != NULL) && (sonIgualesInfo(infoCadena(aux, c1), infoCadena(aux0, c2)))) {
				aux = siguiente(aux, c1);
				aux0 = siguiente(aux0, c2);
			}
			if (aux != NULL) {
				return 0;
			} else {
				return 1;
			}
		}
	}
}

TCadena concatenar(TCadena c1, TCadena c2) {
	TCadena res = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
	TCadena aux = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
	insertarSegmentoDespues(aux, finalCadena(res), res);
	return res;
}

TCadena ordenar(TCadena cad) {
	assert(!hayNatsRepetidos(cad));
	if (esVaciaCadena(cad) || (longitud(cad) == 1)) {
		return cad;
	} else {
		TLocalizador aux = inicioCadena(cad);
		TLocalizador aux0 = siguiente(aux, cad);
		while (aux0 != NULL) {
			if (natInfo(infoCadena(aux0, cad)) < natInfo(infoCadena(aux, cad))) {
				intercambiar(aux, aux0, cad);
			}
			if (siguiente(aux0, cad) != NULL) {
				aux0 = siguiente(aux0, cad);
			} else {
				aux = siguiente(aux, cad);
				aux0 = siguiente(aux, cad);
			}
		}
		return cad;
	}
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
	if (original != nuevo) {
		TLocalizador aux = inicioCadena(cad);
		while (aux != NULL) {
			if (natInfo(infoCadena(aux, cad)) == original) {
				TInfo i = crearInfo(nuevo, realInfo(infoCadena(aux, cad)));
				insertarAlFinal(i, cad);
				intercambiar(aux, finalCadena(cad), cad);
				removerDeCadena(finalCadena(cad), cad);
			}
			aux = siguiente(aux, cad);
		}
		return cad;
	} else {
		return cad;
	}
}

TCadena subCadena(nat menor, nat mayor, TCadena cad) {
	assert(estaOrdenadaPorNaturales(cad) && (menor <= mayor) && pertenece(menor, cad) && pertenece(mayor, cad));
	return copiarSegmento(siguienteClave(menor, inicioCadena(cad), cad), anteriorClave(mayor, finalCadena(cad), cad), cad);
}
