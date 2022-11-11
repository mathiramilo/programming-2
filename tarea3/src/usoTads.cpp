/*5665788*/
#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

TCadena nivelEnBinario(nat l, TBinario b) {
	assert(l > 0);
	TCadena res = crearCadena();
	TBinario aux = b;
	if (esVacioBinario(b)) {
		return res;
	} else {
		nivelEnBinario(l, izquierdo(b));
		if ((profundidadNodo(natInfo(raiz(b)), aux) + 1) == l) {
			insertarAlFinal(raiz(b), res);
		}
		nivelEnBinario(l, derecho(b));
	}
	return res;
}

bool esCamino(TCadena c, TBinario b) {
	if (esVaciaCadena(c)) {
		return true;
	} else if (esVacioBinario(b)) {
		return false;
	} else if (alturaBinario(b) < longitud(c)) {
		return false;
	} else {
		TLocalizador loc = inicioCadena(c);
		if (raiz(b) == infoCadena(loc, c)) {
			loc = siguiente(loc, c);
		} else {
			return false;
		}
		if (loc == NULL) {
			return true;
		} else if (raiz(derecho(b)) == infoCadena(loc, c)) {
			esCamino(c, derecho(b));
		} else if (raiz(izquierdo(b)) == infoCadena(loc, c)) {
			esCamino(c, izquierdo(b));
		} else return false;
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
		while ((siguiente(aux, cad) != NULL) && (natInfo(infoCadena(aux, cad)) <= natInfo(infoCadena(siguiente(aux, cad), cad)))) {
			aux = siguiente(aux, cad);
		}
		if (siguiente(aux, cad) != NULL) {
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
