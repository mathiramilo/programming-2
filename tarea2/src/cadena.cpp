/*5665788*/
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo {
	TInfo dato;
	TLocalizador anterior;
	TLocalizador siguiente;
};

struct repCadena {
	TLocalizador inicio;
	TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
	TCadena res = new repCadena;
	res->inicio = res->final = NULL;  
	return res;
}

void liberarCadena(TCadena cad) {
	TLocalizador a_borrar;
	while (cad->inicio != NULL) {
		a_borrar = cad->inicio; 
		cad->inicio = cad->inicio->siguiente;   
		liberarInfo(a_borrar->dato);
		delete a_borrar;
	}
	delete cad;
}  

bool esVaciaCadena(TCadena cad) {
	assert(((cad->inicio == NULL) && (cad->final == NULL)) || 
	((cad->inicio != NULL) && (cad->final != NULL)));
	return ((cad->inicio == NULL) /*&& (cad->final == NULL)*/);
}

TLocalizador inicioCadena(TCadena cad) {
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		res = cad->inicio; 
	}
	return res;
}

TLocalizador finalCadena(TCadena cad){
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		res = cad->final; 
	}
	return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TInfo info;
	info = loc->dato; 
	return info;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esFinalCadena(loc, cad)) {
		res = NULL;
	} else {
		res = loc->siguiente; 
	}
	return res;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esInicioCadena(loc, cad)) {
		res = NULL;
	} else {
		res = loc->anterior; 
	}
	return res;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
	if (esVaciaCadena(cad)) {
		return 0;
	} else {
		if (localizadorEnCadena(loc, cad)) {
			if (loc->siguiente == NULL) {
				return 1;
			} else return 0;
		} else return 0;
	}
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
	if (esVaciaCadena(cad)) {
		return 0;
	} else {
		if (localizadorEnCadena(loc, cad)) {
			if (loc->anterior == NULL) {
				return 1;
			} else return 0;
		} else return 0;
	}
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
	TCadena res = cad;
	TLocalizador loc = finalCadena(res);
	TLocalizador aux = new loc->siguiente;
	aux->dato = i; 
	res->final = aux;
	aux->siguiente = NULL;
	return res;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador aux = new nodo;
	aux->dato = i;
	aux->siguiente = loc;
	aux->anterior = loc->anterior;	
	return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	liberarInfo(loc->dato);
	delete loc;
	return cad;
}

void imprimirCadena(TCadena cad) {
	TLocalizador aux = cad->inicio;
	while (aux != NULL) {
		printf("(%n,%d)", natInfo(aux->dato), realInfo(aux->dato));
		aux = aux->siguiente
	}
	printf("\n");
	delete aux;
}

TLocalizador kesimo(nat k, TCadena cad) {
	TLocalizador res;
	if (k != 0) {
		TLocalizador aux = cad->inicio;
		nat cont = 1;
		while ((aux != NULL) && (cont < k)) {
			aux = aux->siguiente;
			cont++;
		}
		if (aux != NULL) {
			res = aux;
		} else res = NULL;
	} else res = NULL;
	return res;
}
	
bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
	TLocalizador cursor = inicioCadena(cad);
	while (esLocalizador(cursor) && (cursor != loc))
		cursor = siguiente(cursor, cad);
	return esLocalizador(cursor);	
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	bool res;
	res = localizadorEnCadena(loc1, cad);
	if (res) {
		TLocalizador cursor = loc1;
		while (esLocalizador(cursor) && (cursor != loc2))
			cursor = siguiente(cursor, cad);
		res = esLocalizador(cursor);
		assert(!res || localizadorEnCadena(loc2, cad));	
	}
	return res;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	if (esVaciaCadena(cad)) {
		cad = sgm;
	} else {
		sgm->inicio->anterior = loc;
		sgm->final->siguiente = loc->siguiente;
		}	
	return cad;
	delete sgm;		
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	TCadena res;
	if (esVaciaCadena(cad)) {
		res = crearCadena();
	} else {
		res = crearCadena();
		TLocalizador aux = desde;
		TLocalizador aux1 = res->inicio = new nodo;
		aux1->dato = copiaInfo(aux->dato);
		TLocalizador aux0 = aux1;
		while (precedeEnCadena(aux,hasta->anterior,cad)) {
			aux = aux->siguiente;
			TLocalizador aux0 =  aux0->siguiente = new nodo;
			aux0->dato = copiaInfo(aux->dato);
		}
		res->final = aux0;
	}
	return res;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	TCadena res;
	if (esVaciaCadena(cad)) {
		res = crearCadena();
	} else {			
		while (precedeEnCadena(desde, hasta, cad)) {
			removerDeCadena(desde, cad);
			desde = desde->siguiente;
		}
		res = cad;
	}
	return res;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador aux = new nodo;
	aux->dato = i;
	aux->anterior = loc->anterior;
	aux->siguiente = loc->siguiente;
	return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	assert(localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad));
	TLocalizador aux1 = new nodo;
	TLocalizador aux2 = new nodo;
	aux1->dato = loc1->dato;
	aux2->dato = loc2->dato;
	aux1->anterior = loc2->anterior;
	aux1->siguiente = loc2->siguiente;
	aux2->anterior = loc1->anterior;
	aux2->siguiente = loc1->siguiente;
	return cad;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		while ((loc != NULL) && (natInfo(loc->dato) != clave)) {
			loc = loc->siguiente;
		}
		if (loc != NULL) {
			res = loc;	
		} else {
			res = NULL;
		}
	}
	return res;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		while ((loc != NULL) && (natInfo(loc->dato) != clave)) {
			loc = loc->anterior;
		}
		if (loc != NULL) {
			res = loc;
		} else {
			res = NULL;
		}
	}
	return res;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res = loc;
	nat menor = natInfo(loc->dato);
	while (loc->siguiente != NULL) {
		loc = loc->siguiente;
		if (natInfo(loc->dato) < menor) {
			menor = natInfo(loc->dato);
			res = loc;
		}
	}
	return res;
}
