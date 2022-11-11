/*
  Módulo principal de la tarea 5.

Intérprete de comandos para probar los módulos.

Están creados una TCadena 'cad', un TLocalizador 'loc',  un TBinario 'b',
un TAvl 'avl', una TPila 'p', un TIterador 'it', un TConjunto 'conj',
una TColaDePrioridad 'cp', un TMapping 'map' y un TGrafo 'g'..

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo TInfo su formato cumple con lo descrito en
'infoATexto' del módulo 'info''.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciar
libera la memoria asignada a 'cad', 'b', 'avl', 'it', 'conj', 'cp', 'map', 'g' y
los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/cadena.h"
#include "include/info.h"
#include "include/usoTads.h"
#include "include/utils.h"

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h> // para srand, rand
#include <string.h>
#include <assert.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256



/*
  Lee y devuelve un TInfo desde la entrada estándar.
  Se asume que la antrada cumple con el formato descrito en 'infoATexto' del 
  módulo 'info''.
 */
TInfo leerInfo(){
  char simbolo = leerChar();
  assert(simbolo == '(');
  nat natural = leerNat();
  simbolo = leerChar();
  assert(simbolo == ',');
  double real = leerDouble();
  simbolo = leerChar();
  assert(simbolo == ')');
  return crearInfo(natural,real);
} // leerInfo



/*
  Lee y devuelve una TCadena desde la entrada estándar.
  Se asume que en la entrada hay un espacio en blanco después de cada elemento.
 */
TCadena leerCadena() {
  nat n = leerNat();
  TCadena res = crearCadena();
  for (nat i = 1; i <= n; i++) {
    TInfo info = leerInfo();
    res = insertarAlFinal(info, res);
  }
  return res;
} // leerCadena

struct tArregloTope {
  ArregloNats datos;
  nat tope;
};
typedef struct tArregloTope TArregloTope;

/*
  Lee una secuencia de nat desde la entrada estándar y las devuelve en un
  arreglo con tope.
  Primero lee la cantidad de elemntos.
  Después de cada elemento hay un espacio en blanco.
  La secuencia está ordenada de manera creciente estricta según los campos
  naturales.
 */
TArregloTope leerArregloOrdenado() {
  nat n = leerNat();
  TArregloTope res;
  res.tope = n;
  if (n == 0) {
    res.datos = NULL;
  } else {
    res.datos = new nat[n];// obtMemNats(n);
    for (nat i = 0; i < n; i++) {
      res.datos[i] = leerNat();
    }
  }

  bool estaOrdenado = true;
  nat pos = 0;
  while (estaOrdenado && pos + 1 < res.tope) {
    if (res.datos[pos] < res.datos[pos + 1])
      pos++;
    else
      estaOrdenado = false;
  }
  if (!estaOrdenado) {
    printf("Secuencia no ordenada. \n");
    delete [] res.datos;// libMemNats(res.datos);
    res.tope = 0;
  }
  return res;
}


// programa principal
int main() {

  TCadena cad = crearCadena();
  TLocalizador loc = inicioCadena(cad); // no válido porque cad es vacía

  char restoLinea[MAX_LINEA];
  char nom_comando[MAX_PALABRA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    leerChars(nom_comando);

    // procesar el comando
    if (!strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (!strcmp(nom_comando, "#")) {
      leerRestoLinea(restoLinea);
      printf("# %s.\n", restoLinea);







      // operaciones de cadena

    } else if (!strcmp(nom_comando, "esLocalizador")) {
      printf("loc%s válido.\n", esLocalizador(loc) ? "" : " no");

    } else if (!strcmp(nom_comando, "esVaciaCadena")) {
      printf("cad%s.\n", esVaciaCadena(cad) ? " vacia" : " no vacia");

    } else if (!strcmp(nom_comando, "inicioCadena")) {
      loc = inicioCadena(cad);
      printf("loc al inicio.\n");

    } else if (!strcmp(nom_comando, "finalCadena")) {
      loc = finalCadena(cad);
      printf("loc al final.\n");

    } else if (!strcmp(nom_comando, "infoCadena")) {
      assert(localizadorEnCadena(loc, cad));
      ArregloChars txtInfo = infoATexto(infoCadena(loc, cad));
      printf("%s\n", txtInfo);
      delete [] txtInfo;//libMemChars(txtInfo);

    } else if (!strcmp(nom_comando, "esFinalCadena")) {
      printf("loc%s es final de cad.\n", esFinalCadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "esInicioCadena")) {
      printf("loc%s es incio de cad.\n", esInicioCadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "siguiente")) {
      assert(localizadorEnCadena(loc, cad));
      loc = siguiente(loc, cad);
      printf("loc al siguiente.\n");

    } else if (!strcmp(nom_comando, "anterior")) {
      assert(localizadorEnCadena(loc, cad));
      loc = anterior(loc, cad);
      printf("loc al anterior.\n");

    } else if (!strcmp(nom_comando, "insertarAlFinal")) {
      cad = insertarAlFinal(leerInfo(), cad);
      printf("Insertado al final.\n");

    } else if (!strcmp(nom_comando, "insertarAntes")) {
      assert(localizadorEnCadena(loc, cad));
      cad = insertarAntes(leerInfo(), loc, cad);
      printf("Insertado antes de loc.\n");

    } else if (!strcmp(nom_comando, "removerDeCadena")) {
      assert(localizadorEnCadena(loc, cad));
      cad = removerDeCadena(loc, cad);
      printf("Removido.\n");

    } else if (!strcmp(nom_comando, "imprimirCadena")) {
      imprimirCadena(cad);

    } else if (!strcmp(nom_comando, "kesimo")) {
      nat k = leerNat();
      loc = kesimo(k, cad);
      if (esLocalizador(loc))
        printf("loc en la posición %d.\n", k);
      else
        printf("loc quedó no válido.\n");

    } else if (!strcmp(nom_comando, "localizadorEnCadena")) {
      printf("loc%s pertenece a cad.\n",
             localizadorEnCadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "precedeEnCadena")) {
      printf("loc1%s precede a loc.\n",
             precedeEnCadena(kesimo(leerNat(), cad), loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "insertarSegmentoDespues")) {
      assert (esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      cad = insertarSegmentoDespues(leerCadena(), loc, cad);
      printf("Segmento insertado después de loc.\n");

    } else if (!strcmp(nom_comando, "copiarSegmento")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert (esVaciaCadena(cad) ||
          ((1 <= k1) && (k1 <= k2) && (k2 <= longitud(cad))));
      TCadena sgm = copiarSegmento(kesimo(k1, cad), kesimo(k2, cad), cad);
      imprimirCadena(sgm);
      liberarCadena(sgm);

    } else if (!strcmp(nom_comando, "borrarSegmento")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert (esVaciaCadena(cad) ||
          ((1 <= k1) && (k1 <= k2) && (k2 <= longitud(cad))));
      cad = borrarSegmento(kesimo(k1, cad), kesimo(k2, cad), cad);
      printf("Segmento borrado.\n");

    } else if (!strcmp(nom_comando, "cambiarEnCadena")) {
      assert(localizadorEnCadena(loc, cad));
      TInfo anteriorInfo = infoCadena(loc, cad);
      cad = cambiarEnCadena(leerInfo(), loc, cad);
      liberarInfo(anteriorInfo);
      printf("Cambio.\n");

    } else if (!strcmp(nom_comando, "intercambiar")) {
      nat k1 = leerNat(), k2 = leerNat();
      nat cantidad = longitud(cad);
      assert((1 <= k1) && (k1 <= cantidad) && (1 <= k2) && (k2 <= cantidad));
      cad = intercambiar(kesimo(k1, cad), kesimo(k2, cad), cad);
      printf("Intercambio.\n");

    } else if (!strcmp(nom_comando, "siguienteClave")) {
      assert (esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      int clave = leerNat();
      loc = siguienteClave(clave, loc, cad);
      if (esLocalizador(loc))
        printf("loc avanzó buscando %d.\n", clave);
      else
        printf("loc quedó no válido.\n");

    } else if (!strcmp(nom_comando, "anteriorClave")) {
      assert (esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      int clave = leerNat();
      loc = anteriorClave(clave, loc, cad);
      if (esLocalizador(loc))
        printf("loc retrocedió buscando %d.\n", clave);
      else
        printf("loc quedó no válido.\n");
 
    } else if (!strcmp(nom_comando, "menorEnCadena")) {
      assert (localizadorEnCadena(loc, cad));
      loc = menorEnCadena(loc, cad);
      printf("El menor es %d.\n", natInfo(infoCadena(loc, cad)));



      // operaciones de usoTads


    } else if (!strcmp(nom_comando, "pertenece")) {
      int i = leerNat();
      printf("%d%s pertenece a cad.\n", i, pertenece(i, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "longitud")) {
      printf("Longitud: %u\n", longitud(cad));

    } else if (!strcmp(nom_comando, "estaOrdenadaPorNaturales")) {
      printf("cad%s.\n",
             estaOrdenadaPorNaturales(cad) ? " ordenada" : " no ordenada");

    } else if (!strcmp(nom_comando, "hayNatsRepetidos")) {
      printf("En cad%s.\n",
             hayNatsRepetidos(cad) ? " hay naturales repetidos" : 
                   " no hay naturales repetidos");

    } else if (!strcmp(nom_comando, "sonIgualesCadena")) {
      TCadena otra = leerCadena();
      printf("%s.\n",
             sonIgualesCadena(cad, otra) ? "Son iguales" : "No son iguales");
      liberarCadena(otra);

    } else if (!strcmp(nom_comando, "concatenar")) {
      TCadena otra = leerCadena();
      TCadena conc = concatenar(cad, otra);
      imprimirCadena(conc);
      liberarCadena(conc);
      liberarCadena(otra);

    } else if (!strcmp(nom_comando, "ordenar")) {
      assert(! hayNatsRepetidos(cad)); 
      cad = ordenar(cad);
      printf("Quedó ordenada.\n");

    } else if (!strcmp(nom_comando, "cambiarTodos")) {
      nat original = leerNat(), nuevo = leerNat();
      cad = cambiarTodos(original, nuevo, cad);
      printf("Cambiados.\n");

    } else if (!strcmp(nom_comando, "subCadena")) {
      assert (estaOrdenadaPorNaturales(cad));
      nat menor = leerNat(), mayor = leerNat();
      assert(menor <= mayor);
      assert(pertenece(menor, cad) && pertenece(mayor, cad));
      TCadena sub = subCadena(menor, mayor, cad);
      imprimirCadena(sub);
      liberarCadena(sub);


    } else if (!strcmp(nom_comando, "reiniciar")) {
      liberarCadena(cad);
      cad = crearCadena();
      loc = inicioCadena(cad);
      printf("Estructuras reiniciadas.\n");


    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(restoLinea, MAX_LINEA + 1, stdin);
  } // while

  liberarCadena(cad);
  return 0;
} // main
