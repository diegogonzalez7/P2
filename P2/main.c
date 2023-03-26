/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "jury_list.h"

#define MAX_BUFFER 255

void create(char *commandNumber, char operacion, char *param1, char *param2, tListJ *J);
void new(char *commandNumber, char operacion, char *param1, char *param2, char *param3, tListJ *J);

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListP *P, tListJ *J) {

    switch (command) {
        case 'C':
            create(commandNumber, command, param1, param2, J);
            break;
        case 'N':
            new(commandNumber, command, param1, param2, param3, J);
            break;
        case 'V':
            break;
        case 'D':
            break;
        case 'S':
            break;
        case 'R':
            break;
        case 'W':
            break;
        default:
            break;
    }
}

void create(char *commandNumber, char operacion, char *param1, char *param2, tListJ *J){
    tItemJ r;
    tPosJ q;
    strcpy(r.juryName, param1);
    r.totalVoters = atoi(param2);

    printf("********************\n");
    printf("%s %c: jury %s totalvoters %s\n", commandNumber, operacion, param1, param2);

    q = findItemJ(r.juryName, *J);
    if(insertItemJ(r, J) && q == NULLJ){
        printf("* Create: jury %s totalvoters %s\n", param1, param2);
        createEmptyListP(&r.participantList);
    }else{
        printf("+ Error: Create not possible\n");
    }
}
void new(char *commandNumber, char operacion, char *param1, char *param2, char *param3, tListJ *J){
    tItemP r;
    tItemJ t;
    tPosP p;
    tPosJ j;
    r.numVotes = 0;
    strcpy(r.participantName, param2);
    if (strcmp(param3, "eu") != 0) {
        r.EUParticipant = true;
    } else r.EUParticipant = false;
    strcpy(t.juryName, param1);

    printf("********************\n");
    printf("%s %c: participant %s location %s\n", commandNumber, operacion, param1, param2);

    j = findItemJ(param1, *J);  //busca en la lista de jurados
    t = getItemJ(j, *J);

    if (j != NULLJ) {   //lo encuentra
        p = findItemP(param2, t.participantList);   //busca en la lista de participantes
        if(p == NULLP){ //no existe en la lista
            if (insertItemP(r, &t.participantList)){    //mira si puede insertar
                printf("* New: jury %s participant %s location %s\n", param1, param2, param3);
            }
        }
    }else{
        printf("+ Error: New not possible\n");
    }
    /*
     * Comprobar que la lista de participantes del jurado existe, si no existe se crea, luego
     * hacemos el if para ver si se puede insertar
     */
}

/*void vote(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos, int *votacion){
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

}*/

void readTasks(char *filename, tListP *P, tListJ *J) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, P, J);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tListP P;
    tListJ J;

    createEmptyListJ(&J);
    char *file_name = "create.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &P, &J);

    return 0;
}
