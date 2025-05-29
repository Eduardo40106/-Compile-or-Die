#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"

void encolar(struct Cola* lacola, struct Adoptante* nuevo) {
    struct Nodo* AptnodoNuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    AptnodoNuevo->persona = nuevo;
    AptnodoNuevo->Aptsiguiente = NULL;
    
    if (lacola->Aptfrente == NULL) {
        lacola->Aptfrente = AptnodoNuevo;
        lacola->Aptatras = AptnodoNuevo;
    } else {
        lacola->Aptatras->Aptsiguiente = AptnodoNuevo;
        lacola->Aptatras = AptnodoNuevo;
    }
}
// Genera el ID basado en la fecha y letras del nombre
void generarID(struct Adoptante* a, int consecutivo) {
    time_t t = time(NULL); //time (NULL) obtiene la hora actual en formato de segundos y se guarda ese valor en t, una variable de tipo time_t
    struct tm tm = *localtime(&t); //*localtime(&t) convierte esos segundos en una fecha (año, mes, dia, etc), y se guarda esa informacion en una variable tm de tipo struct tm 

    char fecha[7]; //Almacena la fecha como cadena
    sprintf(fecha, "%02d%02d%02d",
            tm.tm_year % 100,
            tm.tm_mon + 1,
            tm.tm_mday);
    //sprintf: escribe en la cadena fecha un texto con formato.
    //%02d: formatea los numeros para que siempre tengan dos digitos, agregando ceros si es necesario.
     //tm.tm_year % 100: Obtiene los dos ultimos digitos del año.
     //tm.tm_mon + 1: el mes(se suma en 1, porque en C enero=0).
      //tm.tm_mday: el dia del mes.
      
    // Extrae letras del nombre y apellidos
    char inicialNombre = a->nombre[0]; //Toma la primera letra del nombre de adoptante.
    char ultimaApellidoP = strlen(a->apellidoP) > 0 ? a->apellidoP[strlen(a->apellidoP) - 1] : 'X'; //Obtiene la ultima letra del apellido paterno.
    // strlen(a->apellidoP: obtiene la longitud del apellido materno.
    // Se verifica si esa longitus es mayor a 0 strlen(a->apellidoP) > 0
    // Si, si hay letras, se toma la ultima letra con: a->apellidoP[strlen(a->apellidoP) - 1].
    // Si no hay letras, se asigna una letra por defecto: 'X'.
    char terceraApellidoM = strlen(a->apellidoM) > 2 ? a->apellidoM[2] : 'X'; //Obtiene la tercera letra del apellido materno.
    // Verifica si el apellido materno tiene al menos 3 letras: strlen(a->apellidoM) > 2.
    // Si sí, toma la letra en la posición 2 (que es la tercera letra, porque se empieza a contar desde 0).
    // Si no hay suficientes letras, asigna una letra por defecto: 'X'.
    

    // Formato: AAMMDD + consecutivo + letraNombre + letraApellidoP + letraApellidoM
    char id[30];  //Almacenara el ID completo.
    sprintf(id, "%s%02d%c%c%c",
            fecha, consecutivo,
            inicialNombre,
            ultimaApellidoP,
            terceraApellidoM);
    // Usamos sprintf para forma una cadena de texto con formato y almacenarla dentro de id.
    strcpy(a->id, id); // Copia el ID generado a la estructura
}

// Realiza el registro del adoptante
void registroAdoptante(struct Cola* laCola, int* consecutivoGlobal) {
    struct Adoptante* Aptnuevo;
    char confirmar[5];

    do {
        Aptnuevo = (struct Adoptante*)malloc(sizeof(struct Adoptante));

        printf("Registro de adoptante.\nIngrese los datos necesarios para su registro porfavor\n");

        printf("Nombre: ");
        fgets(Aptnuevo->nombre, 50, stdin);
        Aptnuevo->nombre[strcspn(Aptnuevo->nombre, "\n")] = 0;

        printf("Apellido paterno: ");
        fgets(Aptnuevo->apellidoP, 50, stdin);
        Aptnuevo->apellidoP[strcspn(Aptnuevo->apellidoP, "\n")] = 0;

        printf("Apellido materno: ");
        fgets(Aptnuevo->apellidoM, 50, stdin);
        Aptnuevo->apellidoM[strcspn(Aptnuevo->apellidoM, "\n")] = 0;

        printf("Direccion: ");
        fgets(Aptnuevo->direccion, 100, stdin);
        Aptnuevo->direccion[strcspn(Aptnuevo->direccion, "\n")] = 0;

        printf("Correo electronico: ");
        fgets(Aptnuevo->correo, 50, stdin);
        Aptnuevo->correo[strcspn(Aptnuevo->correo, "\n")] = 0;

        printf("Telefono: ");
        fgets(Aptnuevo->telefono, 15, stdin);
        Aptnuevo->telefono[strcspn(Aptnuevo->telefono, "\n")] = 0;

        printf("Contrasena: ");
        fgets(Aptnuevo->contrasena, 20, stdin);
        Aptnuevo->contrasena[strcspn(Aptnuevo->contrasena, "\n")] = 0;

        // Confirmacion del usuario
        printf("\nLos datos son correctos? (SI/NO): ");
        fgets(confirmar, sizeof(confirmar), stdin);
        confirmar[strcspn(confirmar, "\n")] = 0;

        if (strcmp(confirmar, "SI") != 0) {
            free(Aptnuevo);
            printf("\033[H\033[J");
            printf("\nVolviendo a ingresar los datos...\n\n");
        }

    } while (strcmp(confirmar, "SI") != 0);

    // Genera ID
    generarID(Aptnuevo, *consecutivoGlobal);
    (*consecutivoGlobal)++;

    printf("Su ID es: \033[1;33m%s\033[0m\nNecesitara su ID y su contrasena para iniciar sesion en el sistema\n", Aptnuevo->id);

    // Confirmacion final
    printf("Escriba CONTINUAR para finalizar el registro: ");
    char continuar[20];
    fgets(continuar, sizeof(continuar), stdin);
    continuar[strcspn(continuar, "\n")] = 0;

    if (strcmp(continuar, "CONTINUAR") == 0) {
        encolar(laCola, Aptnuevo);
        printf("\033[H\033[J");
        printf("Adoptante agregado correctamente.\n");
    } else {
        free(Aptnuevo);
        printf("\033[H\033[J");
        printf("Registro cancelado.\n");
    }
}
