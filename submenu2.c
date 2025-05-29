#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"

void mostrar_mascotas_por_especie(struct Mascota* mascotas, char* especie) {
    struct Mascota* actual = mascotas;
    char eleccion;struct SistemaAdopcion* sistema;
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
                    leer_archivo(&nombre_archivo);
                    break;
                case 'S':
                    leer_archivo(&nombre_archivo);
                break;
                case 'M':
                    procesar_adopcion(&sistema, &mascotas);
                break;
                case 'Q':
                    mostrar_menu_adoptante(sistema);
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
