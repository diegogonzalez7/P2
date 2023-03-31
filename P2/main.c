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
void vote(char* commandNumber, char operacion, char *param1, char* param2, tListJ *J);
//void stats(char *commandNumber, char operacion, tListJ J);


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListP *P, tListJ *J) {

    switch (command) {
        case 'C':
            create(commandNumber, command, param1, param2, J);
            break;
        case 'N':
            new(commandNumber, command, param1, param2, param3, J);
            break;
        case 'V':
            vote(commandNumber, command, param1, param2, J);
            break;
        case 'D':
            break;
        case 'S':
            //stats(commandNumber, command, *J);
            break;
        case 'R':
            break;
        case 'W':
            break;
        default:
            break;
    }
}

void create(char *commandNumber, char operacion, char *param1, char *param2, tListJ *J){    //ACABADO
    tItemJ jurado;
    tPosJ q;
    strcpy(jurado.juryName, param1);
    jurado.totalVoters = atoi(param2);
    jurado.nullVotes = 0;
    jurado.validVotes = 0;

    printf("********************\n");
    printf("%s %c: jury %s totalvoters %s\n", commandNumber, operacion, param1, param2);

    q = findItemJ(jurado.juryName, *J);
    if(insertItemJ(jurado, J) && q == NULLJ){    //puede insertar y el jurado no existe
        printf("* Create: jury %s totalvoters %s\n", param1, param2);
        createEmptyListP(&jurado.participantList);
    }else{
        printf("+ Error: Create not possible\n");
    }
}
void new(char *commandNumber, char operacion, char *param1, char *param2, char *param3, tListJ *J){
    tItemJ jurado;
    tItemP participante;
    tPosP p; tPosJ j;

    participante.numVotes = 0;
    strcpy(participante.participantName, param2);
    if (strcmp(param3, "eu") != 0) {
        participante.EUParticipant = true;
    } else participante.EUParticipant = false;

    //strcpy(t.juryName, param1);

    printf("********************\n");
    printf("%s %c: jury %s participant %s location %s\n", commandNumber, operacion, param1, param2, param3);

    j = findItemJ(param1, *J);  //busca en la lista de jurados

    if (j != NULLJ) {   //lo encuentra
        jurado = getItemJ(j, *J);
        p = findItemP(param2, jurado.participantList);   //busca en la lista de participantes
        if(p == NULLP){ //no existe en la lista
            if (insertItemP(participante, &jurado.participantList)){    //mira si puede insertar
                printf("* New: jury %s participant %s location %s\n", param1, param2, param3);
                updateItemJ(jurado,j,J);
            }
        }
        else printf("+ Error: New not possible\n");
    }else{
        printf("+ Error: New not possible\n");
    }
}

void vote(char *commandNumber, char operacion, char *param1, char* param2, tListJ *J) {
    tItemJ jurado;
    tItemP participante;
    tPosJ j; tPosP p;
    char *EU;

    printf("********************\n");
    printf("%s %c: jury %s participant %s\n", commandNumber, operacion, param1, param2);
    j = (findItemJ(param1, *J));    //busca jurado

    if (j == NULLJ || isEmptyListJ(*J)) {   //no encuentra al jurado o lista vacía
        printf("+ Error: Vote not possible\n");
    } else {                //no encuentra al participante en la lista
        jurado = getItemJ(j, *J);
        p = findItemP(param2, jurado.participantList);
        if (p == NULLP) {
            printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n", param2, param1);
            jurado.nullVotes++;
            updateItemJ(jurado, j, J);
            printf("Los votos nulos del %s son %d, y los validos son %d\n",jurado.juryName, jurado.nullVotes, jurado.validVotes);
        } else {
            participante = getItemP(p, jurado.participantList);
            jurado.validVotes++;
            participante.numVotes++;
            if (!participante.EUParticipant) EU = "eu"; else EU = "non-eu";
            printf("* Vote: jury %s participant %s location %s numvotes %d\n", jurado.juryName,
                   participante.participantName, EU, participante.numVotes);
            updateItemP(participante, p, &jurado.participantList);
            updateItemJ(jurado, j, J);
            printf("Los votos nulos del %s son %d, y los validos son %d\n",jurado.juryName, jurado.nullVotes, jurado.validVotes);
        }
    }
}


/*void disqualify(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos){
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
}*/

/*
void stats(char *commandNumber, char operacion, tListJ J){
    tItemJ r;
    tItemP y;
    tPosJ p,q;
    tPosP x;
    char *EU;

    printf("********************\n");
    printf("%s %c:\n", commandNumber, operacion);


    if (!isEmptyListJ(J)) {

        for (p = firstJ(J); p != NULLJ; p = nextJ(p, J)) {
            r = getItemJ(p, J);
            printf("Jury %s\n", r.juryName);
            if(isEmptyListP(r.participantList)){ //FALLA AQUI PORQUE DEBERIA ENTRAR EN EL BUCLE y NO LO HACE
                printf("No participants\n");
            }else{
                for(x = firstP(r.participantList); x != NULLP; x = nextP(x, r.participantList)){
                    y = getItemP(x, r.participantList);
                    if(!y.EUParticipant) EU = "eu"; else EU = "non-eu";
                    printf("Participant %s location %s numvotes %d", y.participantName, EU, r.totalVoters);
                    if (r.validVoters == 0){
                        printf("(0.00%%)\n");

                    } else printf("(%.2f%%)\n", (float)y.numVotes / ((float) r.validVoters) * 100.0);
                }
            }
            printf("Nullvotes %d\n", r.nullVotes);
            printf("Participation: %d votes from %d voters (%.2f%%)\n\n", r.nullVotes, r.totalVoters, ((float)r.nullVotes)/(float)r.totalVoters * 100.0);
        }
    }else{
        printf("+ Error: Stats not possible\n");
    }


    /*if(isEmptyListJ(J) != true){
        for(p = firstJ(J); p != NULLJ; p = nextJ(p, J)){
            r = getItemJ(p, );
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
