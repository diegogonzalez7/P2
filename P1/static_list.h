/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#define LNULL (-1) //Constante para indicar pos Nula.
#define MAX 25 //Tamaño máximo del array cuando usamos implementación Estática.

typedef int tPosL;
typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
}tList;

void createEmptyList(tList *L);
/*
 * Objetivo: Determinar si la lista está vacia.
 * Entradas: La lista vacia que vamos a crear.
 * Salida: Una lista vacia.
 * Poscondicion: La lista queda inicializada y no contiene elementos.
 */
bool isEmptyList(tList L);
/*
 * Objetivo: crear una lista vacía e inicializarla
 *  Una lista vacía es aquella en la que el primer puntero, L, tiene valor nulo.
 * Entradas: La lista para consultar.
 * Salida: Falso si la lista no está vacía y verdadero en caso contrario.
 */
tPosL first(tList L);
/*
 * Objetivo: Devuelve la posición del primer elemento de la lista.
 * Entradas: Lista a manipular.
 * Salida: Posición del primer elemento.
 * Precondición: La lista no está vacía.
 */
tPosL last(tList L);
/*
 * Objetivo: Devuelve la posición del último elemento de la lista.
 * Entradas: Lista a manipular.
 * Salida: Posición del último elemento.
 * Precondición: La lista no está vacía.
 */
tPosL next(tPosL p, tList L);
/*
 * Objetivo: Devuelve la posición en la lista del elemento que sigue a la posición dada
 *      (o LNULL si la posición no tiene siguiente).
 * Entradas: p: Posición del elemento actual.
 *      L: Lista a manipular.
 * Salida: Posición del siguiente elemento o nulo si es el último.
 * Precondición: La posición indicada es una posición válida en la lista.
 */
tPosL previous(tPosL p, tList L);
/*
 * Objetivo: Devuelve la posición en la lista del elemento anterior o la posición indicada
 *      (o LNULL si el puesto no tiene anterior).
 * Entradas: p: Posición del elemento actual.
 *      L: Lista a manipular.
 * Salida: Posición del elemento anterior o nulo si es el primero.
 * Precondición: La posición indicada es una posición válida en la lista.
 */
bool insertItem(tItemL d, tPosL p, tList *L);
/*
 * Objetivo: Insertar un elemento en la lista antes de la posición indicada.
 *      Si la posición es LNULL, entonces se agrega el final.
 * Entradas: p: Posición de referencia para la inserción.
 *      L: Lista donde vamos a insertar.
 *      d: Contenido del elemento a insertar.
 * Salida: Devuelve verdadero si el elemento fue insertado, falso en caso contrario.
 * Precondición: La posición indicada es una posición válida en la lista o nula (LNULL).
 * Poscondición: Las posiciones de los elementos de la lista después del elemento insertado pueden variar.
 */
void deleteAtPosition(tPosL p, tList *L);
/*
 * Objetivo: Eliminar de la lista el elemento que ocupa la posición indicada.
 * Entradas: p: Posición del elemento a borrar.
 *      L: Lista a modificar.
 * Salida: Lista sin el elemento correspondiente a la posición p.
 * Precondición: La posición indicada es una posición válida en la lista.
 * Condición posterior: las posiciones de los elementos de la lista después de la posición eliminada pueden variar.
 */
tItemL getItem(tPosL p, tList L);
/*
 * Propósito: Devuelve el contenido del elemento de la lista que ocupa la posición dada.
 * Entradas: p: Posición del elemento buscado.
 *      L: Lista donde buscar el elemento con posición p.
 * Salida: Contenido del elemento que está en posición p.
 * Precondición: La posición indicada es una posición válida en la lista.
 */
void updateItem(tItemL d, tPosL p, tList *L);
/*
 * Objetivo: Modificar el contenido del elemento ubicado en la posición indicada.
 * Entradas: p: Posición del elemento que queremos modificar.
 *      L: Lista a modificar.
 *      d: Nuevo contenido a asignar en posición p.
 * Salida: Lista con el contenido del elemento modificado.
 * Precondición: La posición indicada es una posición válida en la lista.
 * Postcondición: El orden de los elementos en la lista no cambia.
 */
tPosL findItem(tParticipantName d, tList L);
/*
 * Finalidad: Devuelve la posición del primer artículo de la lista cuyo identificador de producto le corresponde
 *      con el indicado (o LNULL si no existe tal elemento).
 * Entradas: L: Lista donde buscar el elemento d.
 *      d: Identificador del producto buscado.
 * Salida: Posición del elemento encontrado o nulo si no se encuentra.
 */

#endif
