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
	TLocalizador aux = new nodo;
	aux->dato = i;
	aux->siguiente = NULL;
	aux->anterior = NULL;
	if (esVaciaCadena(cad)) {
		cad->inicio = aux;
		cad->final = aux;
	} else {
		TLocalizador loc = finalCadena(cad);
		loc->siguiente = aux;
		aux->anterior = loc;
		cad->final = aux;
	}
	return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador aux = new nodo;
	aux->dato = i;
	aux->siguiente = NULL;
	aux->anterior = NULL;	
	if (esInicioCadena(loc, cad)) {
		aux->siguiente = loc;
		loc->anterior = aux;
		cad->inicio = aux; 
	} else {
		aux->siguiente = loc;
		aux->anterior = loc->anterior;
		anterior(loc, cad)->siguiente = aux;
		loc->anterior = aux;
	}
	return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	if ((inicioCadena(cad) == loc) && (finalCadena(cad) == loc)) {
		cad->inicio = NULL;
		cad->final = NULL;
		liberarInfo(loc->dato);
		delete loc;
	} else {
		if (inicioCadena(cad) == loc) {
			TLocalizador aux = loc->siguiente;
			aux->anterior = NULL;
			cad->inicio = aux;
			liberarInfo(loc->dato);
			delete loc;
		} else {
			if (finalCadena(cad) == loc) {
				TLocalizador aux = loc->anterior;
				aux->siguiente = NULL;
				cad->final = aux;
				liberarInfo(loc->dato);
				delete loc;
			} else {
				loc->anterior->siguiente = loc->siguiente;
				loc->siguiente->anterior = loc->anterior;
				liberarInfo(loc->dato);
				delete loc;
			}
		}
	}
	return cad;
}

void imprimirCadena(TCadena cad) {
	TLocalizador aux = cad->inicio;
	while (aux != NULL) {
		printf("(%u,%.2lf)", natInfo(aux->dato), realInfo(aux->dato));
		aux = aux->siguiente;
	}
	printf("\n");
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
	if (!esVaciaCadena(sgm)) {
	if (esVaciaCadena(cad)) {
		cad->inicio = sgm->inicio;
		cad->final = sgm->final;
	} else {
		if (!esFinalCadena(loc, cad)) {		
			sgm->final->siguiente = loc->siguiente;
			siguiente(loc, cad)->anterior = finalCadena(sgm);			
			sgm->inicio->anterior = loc;
			loc->siguiente = inicioCadena(sgm);
		} else {
			loc->siguiente = inicioCadena(sgm);
			inicioCadena(sgm)->anterior = loc;
			cad->final = finalCadena(sgm);
		}
	}
	}
	delete sgm;
	return cad;		
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	TCadena res;
	if (esVaciaCadena(cad)) {
		res = crearCadena();
	} else {
		res = crearCadena();
		while (precedeEnCadena(desde, hasta, cad)) {
			insertarAlFinal(copiaInfo(desde->dato), res);
			desde = desde->siguiente;
		}
	}
	return res;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	TLocalizador aux = desde;	
	while (precedeEnCadena(desde, hasta, cad)) {
		desde = desde->siguiente;
		removerDeCadena(aux, cad);
		aux = desde;;
	}
return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	loc->dato = i;
	return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	assert(localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad));
	TInfo aux = loc1->dato;
	loc1->dato = loc2->dato;
	loc2->dato = aux;
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
