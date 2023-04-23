/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: 21 / 04 / 23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "jury_list.h"

#define MAX_BUFFER 255

//FUNCIONES AUXILIARES
tItemJ inicializarJurado (char *param1, char *param2);
tItemP inicializarParticipante (char *param1, char *param2);
bool european (char *param1);
char* euro (tItemP participante, char *EU);
void salida(tItemP aux_eu, tItemP aux_non_eu, int cnt_eu, int cnt_non_eu, bool empate_eu, bool empate_non_eu);
bool cont_euro(tItemP participante, tItemP aux_eu, int cnt_eu, bool empate_eu);
bool cont_non_euro(tItemP participante, tItemP aux_non_eu, int cnt_non_eu, bool empate_non_eu);

//PRIMERA ENTREGA

void create(char *commandNumber, char operacion, char *param1, char *param2, tListJ *J);
/*  OBJETIVO: Añadir un nuevo jurado a la lista de jurados, con sus votos puestos a 0, además de inicializar su lista de participantes.
 *  ENTRADA: Recibe un número de comando, un comando (C), una lista de jurados, JuryName [NAME_LENGTH_LIMIT] y los votantes de dicho jurado.
 *  SALIDA: La lista de jurados con el nuevo jurado añadido en caso de que se pudiese realizar la operación.
 *  PRECONDICIÓN: La lista de jurados ha sido creada previamente.
 *  POST-CONDICIONES: Cada jurado deberá tener una lista de participantes vacía, además de que las posiciones de la lista de jurados han podido cambiar.
 */
void new(char *commandNumber, char operacion, char *param1, char *param2, char *param3, tListJ *J);
/*  OBJETIVO: Añadir un nuevo participante a la lista de participantes del jurado correspondiente con sus votos puestos a 0.
 *  ENTRADA: Recibe un número de comando, un comando (N), una lista de jurados, JuryName [NAME_LENGTH_LIMIT], participantName [NAME_LENGTH_LIMIT] y si es europeo o no.
 *  SALIDA: La lista de participantes del jurado con el nuevo participante en caso de que se haya podido realizar la operación.
 *  PRECONDICIÓN: La lista de participantes del jurado ha sido previamente creada.
 *  POST-CONDICIONES: Las posiciones en la lista de participantes han podido cambiar.
 */
void vote(char* commandNumber, char operacion, char *param1, char* param2, tListJ *J);
/*  OBJETIVO: Efectuar un voto para un participante de un jurado.
 *  ENTRADA: Recibe un número de comando, un comando (V), una lista de jurados, JuryName [NAME_LENGTH_LIMIT] y participantName [NAME_LENGTH_LIMIT].
 *  SALIDA: La lista de participantes del jurado concreto, y dicho participante con 1 voto más en caso de que se haya podido realizar el voto,
 *          en caso contrario los votos nulos del jurado deberán incrementarse.
 *  PRECONDICIÓN: La lista de jurados ha sido previamente creada e inicializada.
 *  POST-CONDICIONES: Los votos del jurado y del participante (en caso de existir) deberán verse modificados.
 */
void stats(char *commandNumber, char operacion, tListJ *J);
/*  OBJETIVO: Mostrar información relevante sobre la votación.
 *  ENTRADA: Recibe un número de comando, un comando (S), una lista de jurados.
 *  SALIDA: Una lista con toda la información de los jurados existentes y sus respectivos participantes, además de unas estadísticas con los votos.
 */

//SEGUNDA ENTREGA

void disqualify (char *commandNumber, char operacion, char *param1, tListJ *J);
/*  OBJETIVO: Descalificar a un participante de la lista de participantes de todos los jurados en los que aparezca.
 *  ENTRADA: Recibe un número de comando, un comando (D), una lista de jurados y un participantName [NAME_LENGTH_LIMIT].
 *  SALIDA: La lista de jurados sin el participante descalificado en todas las listas de participantes donde aparezca.
 *  PRECONDICIÓN: La lista de jurados ha sido previamente creada e inicializada.
 *  POST-CONDICIONES: Los votos nulos pueden ser modificados y las posiciones de la lista de participantes han podido cambiar.
 */
void remov(char *commandNumber, char operacion, tListJ *J);
/*  OBJETIVO: Eliminar todos los jurados sin votos válidos.
 *  ENTRADA: Recibe un número de comando, un comando (R) y una lista de jurados.
 *  SALIDA: La lista de jurados sin los jurados eliminados (los que no tenían votos válidos).
 *  PRECONDICIÓN: La lista de jurados ha sido previamente creada e inicializada.
 *  POST-CONDICIONES: Las posiciones en la lista de jurados han podido cambiar.
 */
void winners(char *commandNumber, char operacion, tListJ *J);
/*  OBJETIVO: Mostrar los participantes con más votos de cada jurado europeos y no europeos (en caso de empate o no existencia de participantes no habrá ganador).
 *  ENTRADA: Recibe un número de comando, un comando (W) y una lista de jurados.
 *  SALIDA: Los participantes ganadores.
 *  PRECONDICIÓN: La lista de jurados ha sido previamente creada e inicializada.
 *  POST-CONDICIONES: -.
 */

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListJ *J) {

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
            disqualify(commandNumber, command, param1, J);
            break;
        case 'S':
            stats(commandNumber, command, J);
            break;
        case 'R':
            remov(commandNumber, command, J);
            break;
        case 'W':
            winners(commandNumber, command, J);
            break;
        default:
            break;
    }
}

void create(char *commandNumber, char operacion, char *param1, char *param2, tListJ *J){
    tItemJ jurado;
    tPosJ q;
    jurado = inicializarJurado(param1, param2);

    printf("********************\n");
    printf("%s %c: jury %s totalvoters %s\n", commandNumber, operacion, param1, param2);

    q = findItemJ(jurado.juryName, *J);
    if (q == NULLJ) {   //comprobamos primero que el jurado no exista en la lista
        if (insertItemJ(jurado, J)) {    //luego comprobamos si se puede insertar, no podemos hacerlo junto con la otra condición porque
            //ya lo insertaría en la lista al hacer la comprobación de la condición insertItem y por lo tanto podría insertar jurados ya existentes
            printf("* Create: jury %s totalvoters %s\n", param1, param2);
            createEmptyListP(&jurado.participantList);
            q = findItemJ(jurado.juryName, *J);
            updateItemJ(jurado, q, J);
        } else {
            printf("+ Error: Create not possible\n");
        }
    }
    else {
        printf("+ Error: Create not possible\n");
    }
}

void new(char *commandNumber, char operacion, char *param1, char *param2, char *param3, tListJ *J){
    tItemJ jurado;
    tItemP participante;
    tPosP p; tPosJ j;

    participante = inicializarParticipante(param2, param3);

    printf("********************\n");
    printf("%s %c: jury %s participant %s location %s\n", commandNumber, operacion, param1, param2, param3);

    j = findItemJ(param1, *J);  //busca en la lista de jurados

    if (j != NULLJ) {   //lo encuentra
        jurado = getItemJ(j, *J);
        p = findItemP(param2, jurado.participantList);   //busca en la lista de participantes
        if(p == NULLP){ //no existe el participante en la lista
            if (insertItemP(participante, &jurado.participantList)){    //comprueba si se puede insertar
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
    char *EU = NULL;

    printf("********************\n");
    printf("%s %c: jury %s participant %s\n", commandNumber, operacion, param1, param2);
    j = (findItemJ(param1, *J));    //busca jurado

    if (j == NULLJ || isEmptyListJ(*J)) {   //no encuentra al jurado o lista vacía
        printf("+ Error: Vote not possible\n");
    } else {
        jurado = getItemJ(j, *J);
        p = findItemP(param2, jurado.participantList);
        if (p == NULLP) {                   //no existe el participante al que se vota
            printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n", param2, param1);
            jurado.nullVotes++;
            updateItemJ(jurado, j, J);
            //printf("Los votos nulos del %s son %d, y los validos son %d\n", jurado.juryName, jurado.nullVotes, jurado.validVotes);
        } else {                            //participante encontrado
            participante = getItemP(p, jurado.participantList);
            jurado.validVotes++;
            participante.numVotes++;
            EU = euro(participante, EU);
            printf("* Vote: jury %s participant %s location %s numvotes %d\n", jurado.juryName,
                   participante.participantName, EU, participante.numVotes);
            updateItemP(participante, p, &jurado.participantList);
            updateItemJ(jurado, j, J);
            //printf("Los votos nulos del %s son %d, y los validos son %d\n", jurado.juryName, jurado.nullVotes, jurado.validVotes);
        }
    }
}

void stats(char *commandNumber, char operacion, tListJ *J) {
    tItemJ jurado;
    tItemP participante;
    tPosJ j;
    tPosP p;
    char *EU;

    printf("********************\n");
    printf("%s %c:\n", commandNumber, operacion);

    if (isEmptyListJ(*J)) {         //mensaje de error para lista vacía
        printf("+ Error: Stats not possible\n");
    } else {
        j = firstJ(*J);
        while (j != NULLJ) {
            jurado = getItemJ(j, *J);
            printf("Jury %s\n", jurado.juryName);
            if (isEmptyListP(jurado.participantList)) {
                printf("No participants\n");
            } else {
                p = firstP(jurado.participantList);
                while (p != NULLP) {
                    participante = getItemP(p, jurado.participantList);
                    EU = euro(participante, EU);
                    printf("Participant %s location %s numvotes %d ", participante.participantName, EU,
                           participante.numVotes);
                    if (jurado.validVotes == 0) {
                        printf("(0.00%%)\n");
                    } else printf("(%.2f%%)\n", (float) participante.numVotes / ((float) jurado.validVotes) * 100.0);
                    p = nextP(p, jurado.participantList);
                }
            }
            printf("Nullvotes %d\n", jurado.nullVotes);
            printf("Participation: %d votes from %d voters (%.2f%%)\n\n", (jurado.validVotes + jurado.nullVotes),
                   jurado.totalVoters, ((float) jurado.validVotes + (float) jurado.nullVotes) / (float) jurado.totalVoters * 100.0);
            j = nextJ(j, *J);
        }
    }
}

void disqualify (char *commandNumber, char operacion, char *param1, tListJ *J) {
    tItemJ jurado;
    tItemP participante;
    tPosP p; tPosJ j;

    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);

    if (isEmptyListJ(*J)) {     //mensaje de error para lista vacía
        printf("+ Error: Disqualify not possible\n");
    }
    else {
        j = firstJ(*J);
        while (j != NULLJ) {
            jurado = getItemJ(j,*J);
            printf("Jury %s\n", jurado.juryName);
            p = findItemP(param1, jurado.participantList);  //busca en lista de participantes
            if (p != NULLP) {   //encuentra al participante a descalificar
                participante = getItemP(p, jurado.participantList);
                printf("Participant %s disqualified\n\n", participante.participantName);
                jurado.nullVotes += participante.numVotes;
                jurado.validVotes -= participante.numVotes;
                deleteAtPositionP(p,&jurado.participantList);
                updateItemJ(jurado, j, J);  //actualiza la lista de participantes del jurado
                //printf("Los votos nulos de %s son %d\n", jurado.juryName, jurado.nullVotes);
            } else {
                printf("No participant %s\n\n", param1);
            }
            j = nextJ(j,*J);
        }
    }
}

void remov(char *commandNumber, char operacion, tListJ *J) {
    tItemJ jurado;
    tPosJ j;
    int contador_jurados = 0;

    printf("********************\n");
    printf("%s %c: \n", commandNumber, operacion);

    if (isEmptyListJ(*J)) {     //mensaje de error lista vacía
        printf("+ Error: Remove not possible\n");
    } else {
        j = firstJ(*J);
        while (j <= lastJ(*J) && j != NULLJ) {
            jurado = getItemJ(j,*J);
            if (jurado.validVotes == 0) {
                printf("* Remove: jury %s\n", jurado.juryName);
                deleteAtPositionJ(j,J);
                contador_jurados ++;
            } else {
                j = nextJ(j, *J);
            }
        }
        if (contador_jurados == 0) {        //no se ha borrado ningún jurado
            printf("+ Error: Remove not possible\n");
        }
    }
}

void winners(char *commandNumber, char operacion, tListJ *J){
    tItemJ jurado;
    tItemP participante, aux_eu, aux_non_eu;
    tPosJ j; tPosP p;
    int cnt_eu = 0;
    int cnt_non_eu = 0;
    bool empate_eu = false;
    bool empate_non_eu = false;

    aux_eu.numVotes = 0;
    aux_non_eu.numVotes = 0;


    printf("********************\n");
    printf("%s %c: \n", commandNumber, operacion);

    if(isEmptyListJ(*J)){       //mensaje de error lista de jurados vacía
        printf("+ Error: Winners not possible\n");
    }else{
        j = firstJ(*J);
        while (j != NULLJ){
            jurado = getItemJ(j, *J);
            printf("Jury %s\n", jurado.juryName);
            if (isEmptyListP(jurado.participantList)) {     //no hay ganadores (lista de participantes vacía)
                printf("Location eu: No winner\n");
                printf("Location non-eu: No winner\n\n");
            } else {
                p = firstP(jurado.participantList);
                while (p != NULLP) {
                    participante = getItemP(p, jurado.participantList);
                    if(participante.EUParticipant){    //europeo
                        cnt_eu ++;  //contador para ver si hay participantes europeos
                        cont_euro(participante, aux_eu, cnt_eu, empate_eu);
                        if(aux_eu.numVotes <= participante.numVotes){   //asigna los datos del participante al aux_eu
                            aux_eu.numVotes = participante.numVotes;
                            strcpy(aux_eu.participantName, participante.participantName);
                        }
                    }else{  //no europeo
                        cnt_non_eu ++;  //contador para ver si hay participantes no europeos
                        cont_non_euro(participante, aux_non_eu, cnt_non_eu, empate_non_eu);
                        if(aux_non_eu.numVotes <= participante.numVotes){   //asigna los datos del participante a aux_non_eu
                            aux_non_eu.numVotes = participante.numVotes;
                            strcpy(aux_non_eu.participantName, participante.participantName);
                        }
                    }
                    p = nextP(p, jurado.participantList);
                }
                salida(aux_eu, aux_non_eu, cnt_eu, cnt_non_eu, empate_eu, empate_non_eu);
            }
            j = nextJ(j, *J);
        }
    }
}

//FUNCIONES AUXILIARES

//Asigna los valores a un jurado
tItemJ inicializarJurado (char *param1, char *param2) {
    tItemJ auxiliar;
    strcpy(auxiliar.juryName, param1);
    auxiliar.totalVoters = atoi(param2);
    auxiliar.nullVotes = 0;
    auxiliar.validVotes = 0;

    return auxiliar;
}
//Asigna los valores a un participante
tItemP inicializarParticipante (char *param1, char *param2) {
    tItemP participante;
    participante.numVotes = 0;
    strcpy(participante.participantName, param1);
    participante.EUParticipant = european(param2);
    return participante;
}
//Devuelve true si es europeo, false en caso contrario
bool european (char *param1) {
    tItemP participante;
    if (strcmp(param1, "eu") == 0) {
        participante.EUParticipant = true;
    } else participante.EUParticipant = false;
    return participante.EUParticipant;
}
//Dependiendo del valor del boolean EUParticipant asigna su string correspondiente.
char* euro (tItemP participante, char *EU) {
    if (participante.EUParticipant) EU = "eu"; else EU = "non-eu";
    return EU;
}

void salida(tItemP aux_eu, tItemP aux_non_eu, int cnt_eu, int cnt_non_eu, bool empate_eu, bool empate_non_eu){
    if (cnt_eu == 0 || empate_eu) { //no hay participantes europeos o hay empate
        printf("Location eu: No winner\n");
        cnt_eu = 0;
        empate_eu = false;  //es necesario restablecer los valores aquí también
    } else {
        printf("Location eu: Participant %s numvotes %d\n", aux_eu.participantName, aux_eu.numVotes);
        aux_eu.numVotes = 0;        //restablece los votos del participante auxiliar y el contador a 0 para pasar al siguiente jurado
        cnt_eu = 0;
        empate_eu = false;
    }
    if (cnt_non_eu == 0 || empate_non_eu) { //no hay participantes no_europeos o hay empate
        printf("Location non-eu: No winner\n\n");
        cnt_non_eu = 0;
        empate_non_eu = false;
    }
    else {
        printf("Location non-eu: Participant %s numvotes %d\n\n", aux_non_eu.participantName, aux_non_eu.numVotes);
        aux_non_eu.numVotes = 0;
        cnt_non_eu = 0;
        empate_non_eu = false;
    }
}

//contador para que compruebe si hay empate en el número de votos máximo
bool cont_euro(tItemP participante, tItemP aux_eu, int cnt_eu, bool empate_eu){
    if (cnt_eu > 1) {
        if (aux_eu.numVotes == participante.numVotes) {
              empate_eu = true;
        }
    }
    return empate_eu;
}

//contador para que compruebe si hay empate en el número de votos máximo
bool cont_non_euro(tItemP participante, tItemP aux_non_eu, int cnt_non_eu, bool empate_non_eu){
    if (cnt_non_eu > 1) {
        if (aux_non_eu.numVotes == participante.numVotes) {
            empate_non_eu = true;
        }
    }
    return empate_non_eu;
}

void readTasks(char *filename, tListJ *J) {

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

            processCommand(commandNumber, command[0], param1, param2, param3, J);
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

    readTasks(file_name, &J);

    return 0;
}