/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

void new(char *commandNumber, char operacion, char *param1, char *param2, tList *L, int *votacion);
void stats(char *commandNumber, char operacion, char* param1, tList L, const int *votosnulos);
void vote(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos, int *votacion);
void disqualify(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos);


void processCommand(char *commandNumber, char operacion, char *param1, char *param2, tList *L, int *votosnulos, int *votacion) {

    switch (operacion) {
        case 'N':
            /*
             * Objetivo: Añadir un nuevo participante al concurso con 0 votos inicialmente.
             * Entradas: El nombre del participante (char[NAME_LENGTH_LIMIT]) y si es europeo o no (bool), no puede ser distinto de eu o non-eu.
             * Salida: La lista de participantes con el participante añadido o un mensaje de error en caso de que no se pueda añadir.
             */
            new(commandNumber, operacion, param1, param2, L, votacion);
            break;
        case 'V':
            /*
             * Objetivo: Añadir un voto a un participante.
             * Entradas: El nombre del participante (char[NAME_LENGTH_LIMIT]) al cual se le quiere sumar un voto.
             * Salida: La lista con el número de votos de dicho participante incrementado o un voto nulo si el participante no existe.
             */
            vote(commandNumber, operacion, param1, L, votosnulos, votacion);
            break;
        case 'D':
            /*
             * Objetivo: Descalificar un participante del concurso.
             * Entradas: El nombre del participante (char[NAME_LENGTH_LIMIT]) que se quiere descalificar.
             * Salida: La lista de participante sin este participante o un mensaje de error si no se pudo eliminar.
             */
            disqualify(commandNumber, operacion, param1, L, votosnulos);
            break;
        case 'S':
            /*
             * Objetivo: Ver las estadísticas de participación y votos de todos los participantes.
             * Entradas: El número total de votantes (int).
             * Salida: -.
             * Precondición: El número de votos totales no puede ser mayor al número total de votantes, y el número de votantes debe ser mayor o igual que 1 al menos.
             */
            stats(commandNumber, operacion, param1, *L, votosnulos);
            break;
        default:
            break;
    }
}

void new(char *commandNumber, char operacion, char *param1, char *param2, tList *L, int *votacion) {
    tItemL r;
    r.numVotes = 0;
    strcpy(r.participantName, param1);
    if (strcmp(param2, "eu") != 0) {
        r.EUParticipant = true;
    } else r.EUParticipant = false;

    printf("********************\n");
    printf("%s %c: participant %s location %s\n", commandNumber, operacion, param1, param2);

    if (*votacion == 0) {
        if ((findItem(param1, *L)) != LNULL) {
            printf("+ Error: New not possible\n");
        } else {
            insertItem(r, LNULL, L);
            printf("* New: participant %s location %s\n", param1, param2);
        }
    }
    else {
        printf("+ Error: New not possible\n");
    }
}

void vote(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos, int *votacion){
    tItemL r;
    tPosL p;
    char *EU;
    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);
    p = (findItem(param1, *L));
    if((p == LNULL) || isEmptyList(*L)){
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", param1);
        (*votosnulos)++;
    }else{
        r = getItem(p, *L);
        r.numVotes++;
        updateItem(r, p, L);
        if(!r.EUParticipant) EU = "eu"; else EU = "non-eu" ;
        printf("* Vote: participant %s location %s", param1, EU);
        printf(" numvotes %d\n", r.numVotes);
    }
    *votacion = 1;
}


void disqualify(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos){
    tItemL r;
    tPosL p;
    char *EU;
    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);
    p = (findItem(param1, *L));
    if(p == LNULL){
        printf("+ Error: Disqualify not possible\n");
    }else{
        r = getItem(p, *L);
        (*votosnulos) += r.numVotes;
        deleteAtPosition(p, L);
        if(!r.EUParticipant) EU = "eu"; else EU = "non-eu" ;
        printf("* Disqualify: participant %s location %s\n", param1, EU);
    }
}


void stats(char *commandNumber, char operacion, char* param1, tList L, const int *votosnulos){
    tItemL r;
    tPosL p,q;
    char *EU;
    int votosnuloss;
    int votosvalidoss = 0;
    int votos = atoi(param1);
    if(votosnulos == NULL){
        votosnuloss = 0;
    }else{
        votosnuloss = (*votosnulos);
    }

    if (!isEmptyList(L)) {
        for (q = first(L);q != LNULL;q = next(q, L)) {
            r = getItem(q, L);
            votosvalidoss += r.numVotes;
        }
    }

    printf("********************\n");

    printf("%s %c: totalvoters %d\n", commandNumber, operacion, votos);
    if(isEmptyList(L) != true){
        for(p = first(L); p != LNULL; p = next(p, L)){
            r = getItem(p, L);
            if(!r.EUParticipant) EU = "eu"; else EU = "non-eu" ;
            printf("Participant %s location %s", r.participantName, EU);
            printf(" numvotes %d ", r.numVotes);
            if (votosvalidoss == 0){
                printf("(0.00%%)\n");

            } else printf("(%.2f%%)\n", (float)r.numVotes / ((float) votosvalidoss) * 100.0);
        }

        printf("Null votes %d\n", votosnuloss);
        printf("Participation: %d votes from %d voters (%.2f%%)\n", votosvalidoss + votosnuloss, votos, ((float)votosvalidoss + (float) votosnuloss)/(float)votos *100.0);


    }else{
        printf("+ Error: Stats not possible\n");
    }

}

void readTasks(char *filename, tList *L, int *votosnulos, int *votacion) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, L, votosnulos, votacion);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tList L;
    createEmptyList(&L);
    int *votacion = malloc(sizeof (int));      //true = ha comenzado la votación
    *votacion = 0;
    int *votosnulos = malloc(sizeof (int));
    *votosnulos = 0;
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &L, votosnulos, votacion);

    return 0;
}




