/* 5665788 */
#include "../include/colaInfo.h"
#include "../include/listaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repCola {
	TLista lst;
};

TCola crearCola() {
	TCola resultado = new repCola;
	(*resultado).lst = crearLista();
	return resultado;
}

bool esVaciaCola(TCola cola) {
	return longitud((*cola).lst) == 0;
}

TCola encolar(info_t nuevo, TCola cola) {
	(*cola).lst = insertar(longitud((*cola).lst) + 1, nuevo, (*cola).lst);
	return cola;
}

info_t frente(TCola cola) {
	assert(!esVaciaCola(cola))
	return infoLista(1, (*cola).lst);
}

TCola desencolar(TCola cola) {
	(*cola).lst = remover(1, (*cola).lst);
	return cola;
}
