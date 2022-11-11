/* 5665788 */
#include "../include/mapping.h"
#include "../include/listaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repMap {
	TLista lst;
};

TMapping crearMapping() {
	TMapping resultado = new repMap;
	(*resultado).lst = crearLista();
	return resultado;
}

bool esClave(nat clave, TMapping map) {
	return (posNat(clave, (*map).lst) != 0);
}

TMapping asociar(nat clave, double valor, TMapping map) {
	if (!esClave(clave, map)) {
		info_t info;
		info.natural = clave;
		info.real = valor;
		(*map).lst = insertar(longitud((*map).lst) + 1, info, (*map).lst);
	}	
	return map;
}		

double valor(nat clave, TMapping map) {
	assert(esClave(clave, map));
	return infoLista(posNat(clave, (*map).lst), (*map).lst).real;
}

TMapping desasociar(nat clave, TMapping map) {
	if (esClave(clave, map)) {
		(*map).lst = remover(posNat(clave, (*map).lst), (*map).lst);
		return map;
	} else 
		return map;
}		











