// prueba de acceso a editar GT-8
// podriamos hacer que esta sea la funcion main
//No es cierto solo le tiro mrd


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Adoptante {
    char nombre[100];
    int numTelefonico;
    char correo[100];
    char apellido[50];
    char contraseña[100];
    char ID[10];
};

struct Mascota {
    char especie[50];
    char nombreMascota[100];
    int edad;
    int adoptada;
};

struct Cola {
    Adoptante** elementos;
    int capacidad;
    int frente;
    int final;
    int tamano;
};

Adoptante* adoptante = NULL;
Mascota* mascota = NULL;
int numAdoptante = 0;
int numMascota = 0;
struct Cola colaAdoptantes;

void archivoAdoptantes(const char* archivo) {
    FILE* file = fopen(archivo, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo del Adoptante x_x");
        return;
    }

    char linea[100];
    while (fgets(linea, sizeof(linea), file)) {
        numAdoptante++;
        adoptante = realloc(adoptante, numAdoptante * sizeof(Adoptante));
        Adoptante* adoptanteActual = &adoptante[numAdoptante - 1];
        sscanf(linea, "%s %s %s %s %d %s", adoptanteActual->nombre, adoptanteActual->apellido, adoptanteActual->ID, adoptanteActual->contraseña, &adoptanteActual->numTelefonico, adoptanteActual->correo);
    }

    fclose(file);
}

void archivoMascotas(const char* archivo) {
    FILE* file = fopen(archivo, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de mascotas x_x\n");
        return;
    }

    char linea[100];
    while (fgets(linea, sizeof(linea), file)) {
        numMascota++;
        mascota = realloc(mascota, numMascota * sizeof(Mascota));
        Mascota* mascotaActual = &mascota[numMascota - 1];
        sscanf(linea, "%s %s %d %d", mascotaActual->nombreMascota, mascotaActual->especie, &mascotaActual->edad, &mascotaActual->adoptada);
    }

    fclose(file);
}

void inicializar_cola(int capacidad_inicial) {
    colaAdoptantes.elementos = malloc(capacidad_inicial * sizeof(Adoptante*));
    colaAdoptantes.capacidad = capacidad_inicial;
    colaAdoptantes.frente = 0;
    colaAdoptantes.final = 0;
    colaAdoptantes.tamano = 0;
}

void agregar_adoptante(Adoptante* adoptante) {
    if (colaAdoptantes.tamano == colaAdoptantes.capacidad) {
        colaAdoptantes.capacidad *= 2;
        colaAdoptantes.elementos = realloc(colaAdoptantes.elementos, colaAdoptantes.capacidad * sizeof(Adoptante*));
    }

    colaAdoptantes.elementos[colaAdoptantes.final] = adoptante;
    colaAdoptantes.final = (colaAdoptantes.final + 1) % colaAdoptantes.capacidad;
    colaAdoptantes.tamano++;
}

int main() {
    archivoAdoptantes("adoptantes.txt");
    archivoMascotas("mascotas.txt");

    inicializar_cola(10);

    for (int i = 0; i < numAdoptante; i++) {
        agregar_adoptante(&adoptante[i]);
    }

    printf("Adoptantes:\n");
    for (int i = 0; i < numAdoptante; i++) {
        printf("%s %s %s %s %d %s\n", adoptante[i].nombre, adoptante[i].apellido, adoptante[i].ID, adoptante[i].contraseña, adoptante[i].numTelefonico, adoptante[i].correo);
    }

    printf("Mascotas:\n");
    for (int i = 0; i < numMascoducto[i].nombreMascota, mascota[i].especie, mascota[i].edad, mascota[i].adoptada);
    }

    free(adoptante);
    free(mascota);
    free(colaAdoptantes.elementos);

    return 0;
}
