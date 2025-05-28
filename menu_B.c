#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"

int verificarCredenciales(struct Cola *laCola, const char *contrasenaIngresada) {
    if (laCola->Aptfrente == NULL) {
        printf("No hay adoptantes por atender\n");
        return 0;  // Devolvemos 0 si no hay adoptantes
    }

    struct Nodo* nodoActual = laCola->Aptfrente;

    if (strcmp(nodoActual->persona->contrasena, contrasenaIngresada) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void iniciarSesion(struct Cola *laCola) {
    if (laCola->Aptfrente == NULL) {
        printf("No hay adoptantes por atender.\n");
        return; 
    }
    char contrasena[30];
    int intentos = 3;

    printf("Atencion de adoptante.\t");
    mostrarID(laCola);
    printf("\n");
    do {
        printf("Si falla 3 veces sera retirado de la fila de adoptantes y debera registrarse de nuevo.\n\nIngrese su contrasena: ");
        fgets(contrasena, sizeof(contrasena), stdin);
        contrasena[strcspn(contrasena, "\n")] = '\0';

        if (verificarCredenciales(laCola, contrasena) == 1) {
            printf("\033[H\033[J");
            printf("Bienvenido/a al sistema.\n");
            controlarFlujoMenuB(laCola);
            break;
        } else {
            printf("\033[1;31mContrasena incorrecta.\033[0m\tIntentos restantes: %i\n", (intentos - 1));
            intentos--;
        }
    } while (intentos > 0);

    if (intentos == 0) {
        printf("\033[H\033[J");    
        printf("Ha fallado 3 veces, usted fue retirado de la fila de adoptantes y debera registrarse de nuevo.\n");
        struct Nodo* aptNodoActual = laCola->Aptfrente;

        if (laCola->Aptfrente == laCola->Aptatras) {
            laCola->Aptfrente = NULL;
            laCola->Aptatras = NULL;
        } else {
            laCola->Aptfrente = laCola->Aptfrente->Aptsiguiente;
        }

        free(aptNodoActual->persona);
        free(aptNodoActual);
    }
}

void mostrarMenuB() {
    printf("\n========= MENU DE ADOPTANTE =========\n");
    printf("1. Mostrar mascotas de todas las especies\n");
    printf("2. Mostrar mascotas por especie\n");
    printf("3. Buscar una mascota en especifico por nombre\n");
    printf("4. Buscar mascotas indicando especie y un intervalo de edad\n");
    printf("5. Salir\n");
    printf("======================================\n"); }

void controlarFlujoMenuB(struct Cola* laCola) {
    int opcion;
    char decision[10];

    while (1) {
        mostrarMenuB();
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch (opcion) {
            case 1:
                printf("\033[H\033[J");
                printf("Opcion 1 seleccionada (no implementada).\n");
                break;
            case 2:
                printf("Opcion 2 seleccionada (no implementada).\n");
                break;
            case 3:
                printf("Opcion 3 seleccionada (no implementada).\n");
                break;
            case 4:
                printf("Opcion 4 seleccionada (no implementada).\n");
                break;
            case 5:
                printf("\nSi cierra sesion perdera su lugar en la fila de adoptantes y debera registrarse de nuevo.\n");
                printf("Escriba SALIR para cerrar sesion o REGRESAR para volver al menu de adoptante: ");
                fgets(decision, sizeof(decision), stdin);
                decision[strcspn(decision, "\n")] = '\0'; 

                if (strcasecmp(decision, "REGRESAR") == 0) {
                    printf("\033[H\033[J");
                    continue; 
                } else if (strcasecmp(decision, "SALIR") == 0) {
                    printf("\033[H\033[J");
                    printf("Cerrando sesion...\n");

                    if (laCola->Aptfrente != NULL) {
                        struct Nodo* nodoEliminar = laCola->Aptfrente;
                        laCola->Aptfrente = nodoEliminar->Aptsiguiente;
                        if (laCola->Aptfrente == NULL) {
                            laCola->Aptatras = NULL;
                        }
                        free(nodoEliminar->persona);
                        free(nodoEliminar);
                    }

                    return; 
                } else {
                    printf("Entrada no valida. Continuando sesion...\n");
                }
                break;
            default:
                printf("Opcion no valida. Intenta nuevamente.\n");
        }
    }
}