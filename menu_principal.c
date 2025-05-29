#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"

void menuPrincipal(struct Cola* laCola) {
    int consecutivoGlobal = 1;
    char opcion;

    do {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("A. Registro de adoptante.\n");
        printf("B. Atender a un adoptante.\n");
        printf("C. Cerrar el sistema\n");
        printf("D. Registro de mascotas");
        mostrarID(laCola);
        printf("\nSeleccione una opcion: ");


        char input[3];
        fgets(input, sizeof(input), stdin);
        opcion = input[0];

        switch (opcion) {
            case 'A':
                printf("\033[H\033[J");
                registroAdoptante(laCola, &consecutivoGlobal);
                break;
            case 'B':
            	printf("\033[H\033[J");            	
            	iniciarSesion(laCola);

            	break;
            case 'C':
                printf("\033[H\033[J");
                printf("Sistema cerrado.\n");
                break;
            default:
            	printf("\033[H\033[J");
                printf("Opcion no valida.\n");
        }
    } while (opcion != 'C');
}

void mostrarID(struct Cola* laCola) {
    if (laCola->Aptfrente != NULL) {
        printf("ID del adoptante a atender: \033[1;33m%s\033[0m\n", laCola->Aptfrente->persona->id);
    } else {
        printf("ID del adoptante a atender: No hay nadie en la fila.\n");
    }
}
