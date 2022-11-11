/*
  Módulo de definición de 'TCola'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_H
#define _COLA_H

#include "utils.h"

// Representación de 'TCola'.
// Se debe definir en colaInfo.cpp.
// struct repCola;
// Declaración del tipo 'TCola'.
typedef struct repCola *TCola;

/* Operaciones de TCola */

/*
  Devuelve un elemento de tipo 'TCola' vacío (sin elementos).
 */
TCola crearCola();

/*
  Devuelve 'true' si y solo si 'cola' no tiene elementos.
 */
bool esVaciaCola(TCola cola);

/*
  Si en 'cola' hay menos de MAX (definido en utils.h) elementos encola
  'nuevo' en 'cola'.
  Devulve 'cola'.
 */
TCola encolar(info_t nuevo, TCola cola);

/*
  Devuelve el frente de 'cola'.
  Precondición: 'cola' tiene elementos.
 */
info_t frente(TCola cola);

/*
  Si 'cola' tiene elementos desapila el frente de 'cola'.
  Devulve 'cola'.
 */
TCola desencolar(TCola c);

#endif
