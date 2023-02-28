/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include "static_list.h"

void createEmptyList(tList *L){
    L -> lastPos = LNULL;               //Aquí iguala la variable a la que apunta el puntero L a NULL.
    //L -> lastPos = LNULL;             //Hace lo mismo, pero esta orden sólo puede ejecutarse cuando se pasa la lista por referencia.
}

bool isEmptyList(tList L){              //Comprueba si la lista está vacía viendo si la última posición es NULL.
    return L.lastPos == LNULL;
}

tPosL first(tList L){                   //Devuelve la primera posición de la lista (la posición 0 al tratarse de un array).
    return 0;
}

tPosL last(tList L){                    //Devuelve la última posición (con contenido) de la lista.
    return L.lastPos;
}

tPosL next(tPosL p, tList L){           //Devuelve el elemento siguiente al introducido valorando dos casos:
    if(p == L.lastPos){
        return LNULL;                   //si la posición dada es la última de la lista, devuelve NULL
    }else{
        return ++p;                     //en caso contrario, devuelve la siguiente posición
    }
}

tPosL previous(tPosL p, tList L){       //Devuelve la posición anterior a la introducida, en este caso
    return --p;                         //si fuese el primer elemento, daría -1 que es LNULL.
}

bool insertItem(tItemL d, tPosL p, tList *L){
    tPosL i;

    if(L->lastPos == MAX - 1){          //Si la última posición de la lista es la última del array, no podremos insertar un elemento
        return false;
    }else{
        L->lastPos++;
        if(p == LNULL){                 //Insertar al final de la lista
            tPosL q = L->lastPos;
            L->data[q] = d;
        }else{                          //Insertar en posición intermedia
            for(i = L->lastPos; i >= p+1; i--){
                L->data[i] = L->data[i - 1];
            }
            L->data[p] = d;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L){   //Elimina una pos de la lista.
    tPosL i;
    L -> lastPos --;
    for(i = p; i <= L->lastPos; i++){
        L->data[i] = L->data[i + 1];
    }
}

tItemL getItem(tPosL p, tList L){   //Devuelve el contenido del elemento de la lista en la posición indicada.
    return L.data[p];
}

void updateItem(tItemL d, tPosL p, tList *L){   //Modifica el contenido del elemento situado en la pos introducida.
    //(*L).data[p] = d;                         //Asigna el valor d al campo data de la lista en la pos indicada.
    L -> data[p] = d;
}

tPosL findItem(tParticipantName d, tList L){    //Devuelve la pos del primer elemento de la lista cuyo contenido coincide con el
    if(isEmptyList(L)) {return LNULL;}          //introducido o nulo si no lo encuentra
    else{
        tPosL i;
        for(i = 0; (i < L.lastPos) && (strcmp(L.data[i].participantName, d) != 0); i++);    //Importante realizar la operación comprobando primero con el 'lastpos'
        if(strcmp(L.data[i].participantName, d) != 0){
            return LNULL;
        }else{
            return i;
        }
    }
}
