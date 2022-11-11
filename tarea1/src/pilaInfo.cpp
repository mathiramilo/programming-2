/* 5665788 */
#include "../include/pilaInfo.h"
#include "../include/listaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repPila {
	TLista lst;
};

TPila crearPila() {
	TPila resultado = new repPila;
	(*resultado).lst = crearLista();
	return resultado;
}

bool esVaciaPila(TPila pila) {
	return longitud((*pila).lst) == 0;
}

TPila apilar(info_t nuevo, TPila pila) {
	(*pila).lst = insertar(longitud((*pila).lst) + 1, nuevo, (*pila).lst);
	return pila;
}

info_t cima(TPila pila) {
	assert(!esVaciaPila(pila));
	return infoLista(longitud((*pila).lst), (*pila).lst);
}

TPila desapilar(TPila pila) {
	(*pila).lst = remover(longitud((*pila).lst), (*pila).lst);
	return pila;
}
