#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"


struct Mascota* mascotas = NULL;
void mostrar_mascotas_por_especie(struct Mascota* mascotas, char* especie) {
    struct Mascota* actual = mascotas;
    char eleccion;struct Cola* laCola;
    const char *nombre_archivo;
    FILE *archivo = fopen("Mascota.txt", "r");
    
    if (archivo == NULL) {
        printf("No existe el archivo\n");
        return;
    }

    int encontrado = 0;
    
    char linea[1024];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Leer datos de la línea actual
        char nombre[50], especie_actual[50], tamano[10], descripcion[200];
        float peso;
        int edad;
        
        if (sscanf(linea, "%[^,],%[^,],%d,%f,%[^,],%[^\n]", 
                   nombre, especie_actual, &edad, &peso, tamano, descripcion) == 6) {
            
            if (strcmp(especie_actual, especie) == 0) {
                encontrado = 1;
                printf("\n=== Datos de la Mascota ===\n");
                printf("Especie: %s\n", especie_actual);
                printf("Nombre: %s\n", nombre);
                printf("Edad: %d años\n", edad);
                printf("Tamaño: %s\n", tamano);
                printf("Peso: %.2f kg\n", peso);
                printf("Descripción: %s\n", descripcion);
                printf("S -> siguiente, A-> Antras, Q->regresar al menu, M->Aoptar\n");
                printf("Que desea hacer?");
                scanf("%s", eleccion);
                switch (eleccion)
                {
                case 'A':
                    leer_archivo(nombre_archivo);
                    break;
                case 'S':
                    leer_archivo(nombre_archivo);
                break;
                case 'M':
                    procesar_adopcion(laCola, mascotas);
                break;
                case 'Q':
                    controlarFlujoMenuB(laCola);
                break;

                default:
                    break;
                }
            }
        }
    }

    if (!encontrado) {
        printf("\nNo se encontraron mascotas de la especie seleccionada.\n");
    }

    fclose(archivo);
}

void procesar_adopcion(struct Cola* laCola, struct Mascota* mascota) {
    char confirmacion[20];
    printf("\n¿Desea adoptar a %s? (CONFIRMAR/CANCELAR): ", mascota->nombre);
    scanf("%19s", confirmacion);
    if (strcmp(confirmacion, "CONFIRMAR") == 0) {
        printf("\n¡Felicitaciones! Ha adoptado a %s.\n", mascota->nombre);
        printf("Por favor, diríjase al área de mascotas bajo resguardo.\n");
        struct Nodo* actual = laCola->Aptfrente;
        if (actual != NULL) {
            laCola->Aptfrente = actual->Aptsiguiente;
            free(actual);
        }
        time_t inicio = time(NULL);
        while (time(NULL) - inicio < 3);
    } else {
        printf("\nPuede seguir revisando la lista de mascotas.\n");
    }
}

void leer_archivo(const char *nombre_archivo) {
    FILE *archivo;
    char buffer[1024];
    
    archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo: %s\n", nombre_archivo);
        return;
    }
    
    printf("\nContenido de %s:\n", nombre_archivo);
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(archivo);
}
