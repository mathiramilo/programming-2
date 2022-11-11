/*5665788*/
#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
	delete aux;
}

nat longitud(TCadena cad) {
	nat cont = 0;
	TLocalizador aux = inicioCadena(cad);
	while (aux != NULL) {
		cont++;
		aux = siguiente(aux, cad);
	}
	delete aux;
	return cont;
}

bool estaOrdenadaPorNaturales(TCadena cad) {
	if ((esVaciaCadena(cad)) || (longitud(cad) == 1)) {
		return 1;
	} else {
		TLocalizador aux = inicioCadena(cad);
		while ((aux->siguiente != NULL) && (natInfo(infoCadena(aux, cad)) >= natInfo(infoCadena(siguiente(aux, cad)))) {
			aux = siguiente(aux, cad);
		}
		if (siguiente(aux, cad) != NULL) {
			return 0;
		} else {
			return 1;
		}
	}
	delete aux;
}

bool hayNatsRepetidos(TCadena cad) {
	TLocalizador aux = inicioCadena(aux, cad);
	TLocalizador aux0 = siguiente(aux);
	while ((aux0 != NULL) && (natInfo(infoCadena(aux, cad)) != natInfo(infoCadena(aux0)))) {
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
	delete aux;
	delete aux0;
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
			delete aux;
			delete aux0;
		}
	}
}

TCadena concatenar(TCadena c1, TCadena c2) {
	TCadena res = copiarSegmento(inicioCadena(c1), finalCadena(c2), c1);
	TCadena aux = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
	insertarSegmentoDespues(aux, finalCadena(res), res);
	return res;
}

TCadena ordenar(TCadena cad) {
	assert(!hayNatsRepetidos(cad));
	TLocalizador aux = inicioCadena(cad);
	TLocalizador aux0 = siguiente(aux, cad);
	while (aux0 != NULL) {
		if (natInfo(infoCadena(aux0, cad)) < natInfo(infoCadena(aux, cad))) {
			intercambiar(aux, aux0);
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

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
	TLocalizador aux = incioCadena(cad);
	while (aux != NULL) {
		if (natInfo(infoCadena(aux, cad)) == original) {
			infoCadena(aux, cad) = nuevo;
		}
		aux = siguiente(aux, cad);
	}
	return cad;
	delete aux;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad) {
	assert(estaOrdenadaPorNaturales(cad) && (menor <= mayor) && pertenece(menor, cad) && pertenece(mayor, cad));
	return copiarSegmento(anteriorClave(menor, finalCadena(cad), cad), siguienteClave(mayor, inicioCadena(cad), cad), cad);
}

