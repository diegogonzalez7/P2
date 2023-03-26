/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#ifndef JURY_LIST_H
#define JURY_LIST_H

#include "types.h"
#include "participant_list.h"

#define NULLJ (-1)  //Constante para indicar pos Nula.
#define MAX 10      //Tamaño máximo del array cuando usamos implementación Estática.

typedef int tPosJ;
typedef struct tItemJ { //Creamos el struct con los datos del jurado.
    tJuryName juryName;
    tNumVotes totalVoters;
    tNumVotes validVoters;
    tNumVotes nullVotes;
    tListP participantList;
} tItemJ;
typedef struct {
    tItemJ data[MAX];
    tPosJ lastPos;
}tListJ;

//GENERADORAS
void createEmptyListJ(tListJ *L);
/*
 * Objetivo: Crear una lista vacía e inicializarla.
 * Entradas: La lista vacía que vamos a crear.
 * Salida: Una lista vacía.
 * Post-condición: La lista queda inicializada y no contiene elementos.
 */
bool isEmptyListJ(tListJ L);
/*
 * Objetivo: Determinar si la lista está vacía.
 * Una lista vacía es aquella en la que el primer puntero, L, tiene valor nulo.
 * Entradas: La lista para consultar.
 * Salida: Falso si la lista no está vacía y verdadero en caso contrario.
 */

//OBSERVADORAS
tPosJ firstJ(tListJ L);
/*
 * Objetivo: Devolver la posición del primer elemento de la lista.
 * Entradas: Lista a manipular.
 * Salida: Posición del primer elemento.
 * Precondición: La lista no está vacía.
 */
tPosJ lastJ(tListJ L);
/*
 * Objetivo: Devuelve la posición del último elemento de la lista.
 * Entradas: Lista a manipular.
 * Salida: Posición del último elemento.
 * Precondición: La lista no está vacía.
 */
tPosJ nextJ(tPosJ p, tListJ L);
/*
 * Objetivo: Devuelve la posición en la lista del elemento que sigue a la posición dada
 *           (o NULLP si la posición no tiene siguiente).
 * Entradas: p: Posición del elemento actual.
 *           L: Lista a manipular.
 * Salida: Posición del siguiente elemento o nulo si es el último.
 * Precondición: La posición indicada es una posición válida en la lista.
 */
tPosJ previousJ(tPosJ p, tListJ L);
/*
 * Objetivo: Devuelve la posición en la lista del elemento anterior o la posición indicada
 *           (o NULLP si el puesto no tiene anterior).
 * Entradas: p: Posición del elemento actual.
 *           L: Lista a manipular.
 * Salida: Posición del elemento anterior o nulo si es el primero.
 * Precondición: La posición indicada es una posición válida en la lista.
 */
tPosJ findItemJ(tJuryName d, tListJ L);
/*
 * Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre de participante se corresponde
 *            con el indicado (o NULLP si no existe tal elemento).
 * Entradas: L: Lista donde buscar el elemento d.
 *           d: Identificador del producto buscado.
 * Salida: Posición del elemento encontrado o nulo si no se encuentra.
 */
tItemJ getItemJ(tPosJ p, tListJ L);
/*
 * Objetivo: Devuelve el contenido del elemento de la lista que ocupa la posición dada.
 * Entradas: p: Posición del elemento buscado.
 *           L: Lista donde buscar el elemento con posición p.
 * Salida: Contenido del elemento que está en posición p.
 * Precondición: La posición indicada es una posición válida en la lista.
 */

//MODIFICADORAS
bool insertItemJ(tItemJ d, tListJ *L);
/*
 * Objetivo: Insertar un elemento en la lista de forma ordenada mediante el tParticipantName.
 * Entradas: L: Lista donde vamos a insertar.
 *           d: Contenido del elemento a insertar.
 * Salida: Devuelve verdadero si el elemento fue insertado, falso en caso contrario.
 * Post-condición: Las posiciones de los elementos de la lista después del elemento insertado pueden variar.
 */
void updateItemJ(tItemJ d, tPosJ p, tListJ *L);
/*
 * Objetivo: Modificar el contenido del elemento ubicado en la posición indicada.
 * Entradas: p: Posición del elemento que queremos modificar.
 *           L: Lista a modificar.
 *           d: Nuevo contenido a asignar en posición p.
 * Salida: Lista con el contenido del elemento modificado.
 * Precondición: La posición indicada es una posición válida en la lista.
 * Post-condición: El orden de los elementos en la lista no cambia.
 */

//DESTRUCTORAS
void deleteAtPositionJ(tPosJ p, tListJ *L);
/*
 * Objetivo: Eliminar de la lista el elemento que ocupa la posición indicada.
 * Entradas: p: Posición del elemento a borrar.
 *           L: Lista a modificar.
 * Salida: Lista sin el elemento correspondiente a la posición p.
 * Precondición: La posición indicada es una posición válida en la lista.
 * Condición posterior: Las posiciones de los elementos de la lista después de la posición eliminada pueden variar.
 */


#endif