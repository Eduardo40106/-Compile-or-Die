#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructuras de datos
struct Mascota {
    char especie[50];
    char nombre[50];
    int edad_aproximada;
    char tamano[20];
    float peso;
    char descripcion[200];
    struct Mascota* siguiente;
};

struct Adoptante {
    char nombre[50];
    char apellidoP[50];
    char apellidoM[50];
    char direccion[100];
    char correo[50];
    char telefono[15];
    char contrasena[20];
    char id[30];
};

struct Nodo {
    struct Adoptante* adoptante;
    struct Nodo* siguiente;
};

struct Cola {
    struct Nodo* frente;
    struct Nodo* atras;
};

struct SistemaAdopcion {
    struct Mascota* mascotas;
    struct Cola* fila_virtual;
    int intentos_contrasena;
};

// Funciones declaradas
void mostrar_menu_adoptante(struct SistemaAdopcion* sistema);
void controlar_flujo_menu_adoptante(struct Cola* cola);
void iniciar_sesion(struct Cola* cola);
void mostrar_id(struct Cola* cola);

// Función para inicializar la cola
void inicializar_cola(struct Cola* cola) {
    cola->frente = NULL;
    cola->atras = NULL;
}

// Función para encolar un nuevo adoptante
void encolar(struct Cola* cola, struct Adoptante* nuevo) {
    struct Nodo* nodo_nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodo_nuevo->adoptante = nuevo;
    nodo_nuevo->siguiente = NULL;
    if (cola->frente == NULL) {
        cola->frente = nodo_nuevo;
        cola->atras = nodo_nuevo;
    } else {
        cola->atras->siguiente = nodo_nuevo;
        cola->atras = nodo_nuevo;
    }
}

// Función para generar ID
void generar_id(struct Adoptante* adoptante, int consecutivo) {
    time_t t = time(NULL);
    struct tm* fecha = localtime(&t);
    char fecha_str[7];
    sprintf(fecha_str, "%02d%02d%02d",
            fecha->tm_year % 100,
            fecha->tm_mon + 1,
            fecha->tm_mday);
    char inicial_nombre = adoptante->nombre[0];
    char ultima_apellido_p = strlen(adoptante->apellidoP) > 0 ?
        adoptante->apellidoP[strlen(adoptante->apellidoP) - 1] : 'X';
    char tercera_apellido_m = strlen(adoptante->apellidoM) > 2 ?
        adoptante->apellidoM[2] : 'X';
    char id[30];
    sprintf(id, "%s%02d%c%c%c",
            fecha_str, consecutivo,
            inicial_nombre, ultima_apellido_p, tercera_apellido_m);
    strcpy(adoptante->id, id);
}

// Función para validar contraseña
int validar_contrasena(struct SistemaAdopcion* sistema, char* id, char* contrasena) {
    struct Nodo* actual = sistema->fila_virtual->frente;
    if (actual == NULL || strcmp(actual->adoptante->id, id) != 0) {
        return 0;
    }
    if (strcmp(actual->adoptante->contrasena, contrasena) == 0) {
        return 1;
    }
    sistema->intentos_contrasena++;
    return 0;
}
void configTerminal() {
    system("stty -echo");  // Desactiva el eco de caracteres
}

// Función para restaurar la configuración de la terminal
void restoreTerminal() {
    system("stty echo");   // Activa nuevamente el eco de caracteres
}

// Función para eliminar el salto de línea al final de una cadena
void eliminarSaltoLinea(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Función principal para navegar en el archivo
void navegarArchivo(const char* nombreArchivo) {
    FILE *archivo;
    char caracter;
    char linea[1000];
    
    // Abrir el archivo en modo lectura
    archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return;
    }
    
    // Configurar la terminal
    configTerminal();
    
    // Mostrar menú sin salto de línea
    printf("\rNavegación en archivo: 'S': siguiente, 'A': anterior, 'Q': salir");
    
    int lineaActual = 0;
    int totalLineas = 0;
    
    // Contar el número total de líneas
    rewind(archivo);
    while (fgets(linea, sizeof(linea), archivo)) {
        totalLineas++;
    }
    
    // Volver al inicio
    rewind(archivo);
    
    while (1) {
        // Leer la línea actual
        if (fgets(linea, sizeof(linea), archivo)) {
            eliminarSaltoLinea(linea);  // Eliminar el salto de línea
            
            // Mover el cursor al inicio y mostrar la línea
            printf("\rLínea %d/%d: %.*s", 
                   lineaActual + 1, totalLineas,
                   1000 - 20, linea);  // Dejar espacio para los comandos
            
            fflush(stdout);  // Forzar la salida
        } else {
            printf("\rFin del archivo         ");
        }
        
        // Leer comando
        caracter = getchar();
        
        switch(caracter) {
            case 'S':
                if (lineaActual < totalLineas - 1) {
                    lineaActual++;
                    rewind(archivo);
                    // Avanzar hasta la línea deseada
                    for(int i = 0; i <= lineaActual; i++) {
                        fgets(linea, sizeof(linea), archivo);
                    }
                }
                break;
                
            case 'A':
                if (lineaActual > 0) {
                    lineaActual--;
                    rewind(archivo);
                    // Avanzar hasta la línea deseada
                    for(int i = 0; i <= lineaActual; i++) {
                        fgets(linea, sizeof(linea), archivo);
                    }
                }
                break;
                
            case 'Q':
                goto fin;
                break;
                
            default:
                printf("\rComando no reconocido     ");
        }
    }
    
    fin:
    fclose(archivo);
    restoreTerminal();
}
void mostrar_mascotas_por_especie(struct Mascota* mascotas, char* especie) {
    struct Mascota* actual = mascotas;
    struct SistemaAdopcion* sistema;
    char eleccion;struct Cola* laCola;
    const char *nombre_archivo;
    FILE *archivo = fopen("Juan.txt", "r");
    compararContenidoArchivo(archivo, especie);
    
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
                navegarArchivo("Juan.txt");
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
        struct Nodo* actual = laCola->frente;
        if (actual != NULL) {
            laCola->frente = actual->siguiente;
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
char* leerLineaArchivo(FILE* archivo, char* buffer, int tamano) {
    if (fgets(buffer, tamano, archivo)) {
        // Eliminar el salto de línea si existe
        buffer[strcspn(buffer, "\n")] = 0;
        return buffer;
    }
    return NULL;
}

// Función para comparar el contenido del archivo con una cadena
void compararContenidoArchivo(const char* nombreArchivo, const char* especie) {
    FILE* archivo;
    char linea[1000];
    int lineaActual = 1;
    int coincidencias = 0;
    
    // Abrir el archivo
    archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return;
    }
    
    printf("Buscando '%s' en el archivo...\n", especie);
    
    // Leer el archivo línea por línea
    while (leerLineaArchivo(archivo, linea, 1000)) {
        // Comparar la línea con la cadena buscada
        if (strstr(linea, especie) != NULL) {
            printf("Coincidencia encontrada en la línea %d:\n%s\n", 
                   lineaActual, linea);
                printf("\n=== Datos de la Mascota ===\n");
                navegarArchivo("Juan.txt");

            coincidencias++;
        }
        lineaActual++;
    }
    
    printf("\nTotal de coincidencias encontradas: %d\n", coincidencias);
    fclose(archivo);
}
// Función para buscar mascotas por especie y edad
void buscar_mascotas_especie_edad(struct Mascota* mascotas, char* especie, int edad_min, int edad_max) {
    if (mascotas == NULL) return;
    if (strcmp(mascotas->especie, especie) == 0 &&
        mascotas->edad_aproximada >= edad_min &&
        mascotas->edad_aproximada <= edad_max) {
        printf("\n=== Mascota Encontrada ===\n");
        printf("Nombre: %s\n", mascotas->nombre);
        printf("Edad: %d años\n", mascotas->edad_aproximada);
        printf("Descripción: %s\n", mascotas->descripcion);
    }
    buscar_mascotas_especie_edad(mascotas->siguiente, especie, edad_min, edad_max);
}

// Función para procesar la adopción

// Función para mostrar el menú de adoptante
void mostrar_menu_adoptante(struct SistemaAdopcion* sistema) {
    char opcion;
    char especie[50];
    int edad_min, edad_max;
    while (1) {
        printf("\n=== MENÚ DE ADOPTANTE ===\n");
        printf("1. Mostrar mascotas de todas las especies\n");
        printf("2. Mostrar mascotas por especie\n");
        printf("3. Buscar una mascota en específico por nombre\n");
        printf("4. Buscar mascotas indicando especie y un intervalo de edad\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf(" %c", &opcion);
        switch(opcion) {
            case '1':
                mostrar_mascotas_por_especie(sistema->mascotas, "");
                break;
            case '2':
                printf("Ingrese la especie a buscar: ");
                scanf("%s", especie);
                mostrar_mascotas_por_especie(sistema->mascotas, especie);
                break;
            case '3':
                break;
            case '4':
                printf("Ingrese la especie: ");
                scanf("%49s", especie);
                printf("Ingrese edad mínima: ");
                scanf("%d", &edad_min);
                printf("Ingrese edad máxima: ");
                scanf("%d", &edad_max);
                buscar_mascotas_especie_edad(sistema->mascotas, especie, edad_min, edad_max);
                break;
            case '5':
                return;
            default:
                printf("\nOpción no válida.\n");
        }
    }
}

// Función para registrar un nuevo adoptante
void registrar_adoptante(struct Cola* cola, int* consecutivo_global) {
    struct Adoptante* nuevo = (struct Adoptante*)malloc(sizeof(struct Adoptante));
    printf("Registro de adoptante.\nIngrese los datos necesarios para su registro por favor\n");
    printf("Nombre: ");
    fgets(nuevo->nombre, 50, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0;
    printf("Apellido paterno: ");
    fgets(nuevo->apellidoP, 50, stdin);
    nuevo->apellidoP[strcspn(nuevo->apellidoP, "\n")] = 0;
    printf("Apellido materno: ");
    fgets(nuevo->apellidoM, 50, stdin);
    nuevo->apellidoM[strcspn(nuevo->apellidoM, "\n")] = 0;
    printf("Direccion: ");
    fgets(nuevo->direccion, 100, stdin);
    nuevo->direccion[strcspn(nuevo->direccion, "\n")] = 0;
    printf("Correo electronico: ");
    fgets(nuevo->correo, 50, stdin);
    nuevo->correo[strcspn(nuevo->correo, "\n")] = 0;
    printf("Telefono: ");
    fgets(nuevo->telefono, 15, stdin);
    nuevo->telefono[strcspn(nuevo->telefono, "\n")] = 0;
    printf("Contrasena: ");
    fgets(nuevo->contrasena, 20, stdin);
    nuevo->contrasena[strcspn(nuevo->contrasena, "\n")] = 0;
    char confirmar[5];
    do {
        printf("\nLos datos son correctos? (SI/NO): ");
        fgets(confirmar, sizeof(confirmar), stdin);
        confirmar[strcspn(confirmar, "\n")] = 0;
    } while (strcmp(confirmar, "SI") != 0);
    generar_id(nuevo, *consecutivo_global);
    (*consecutivo_global)++;
    printf("Su ID es: \033[1;33m%s\033[0m\nNecesitara su ID y su contrasena para iniciar sesion en el sistema\n", nuevo->id);
    char continuar[20];
    printf("Escriba CONTINUAR para finalizar el registro: ");
    fgets(continuar, sizeof(continuar), stdin);
    continuar[strcspn(continuar, "\n")] = 0;
   FILE* archivo = fopen("adoptantes.txt", "w+");
if (archivo == NULL) {
    printf("Error al abrir el archivo\n");
    free(nuevo);
    return;
}

if (strcmp(continuar, "CONTINUAR") == 0) {
    encolar(cola, nuevo);
    printf("\033[H\033[J");
    printf("Adoptante agregado correctamente.\n");
    
    if (fprintf(archivo,
        "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
        nuevo->nombre, nuevo->apellidoP, nuevo->apellidoM, nuevo->direccion,
        nuevo->correo, nuevo->telefono, nuevo->contrasena, nuevo->id) < 8) {
        printf("Error al escribir en el archivo\n");
        free(nuevo);
    }
} else {
    free(nuevo);
    printf("\033[H\033[J");
    printf("Registro cancelado.\n");
}

if (fclose(archivo) == EOF) {
    printf("Error al cerrar el archivo\n");
}
}
// Función para mostrar el ID del adoptante actual
void mostrar_id(struct Cola* cola) {
    if (cola->frente != NULL) {
        printf("ID del adoptante a atender: \033[1;33m%s\033[0m\n", cola->frente->adoptante->id);
    } else {
        printf("ID del adoptante a atender: No hay nadie en la fila.\n");
    }
}

// Función para verificar credenciales
int verificar_credenciales(struct Cola* cola, const char* contrasena_ingresada) {
    if (cola->frente == NULL) {
        printf("No hay adoptantes por atender\n");
        return 0;
    }
    struct Nodo* nodo_actual = cola->frente;
    if (strcmp(nodo_actual->adoptante->contrasena, contrasena_ingresada) == 0) {
        return 1;
    } else {
        return 0;
    }
}
void agregarMascotaArchivo(struct Mascota *mascota) {
    
    printf("Especie: ");
    fgets(mascota->especie, 50, stdin);
    mascota->especie[strcspn(mascota->especie, "\n")] = 0;
    printf("Nombre: ");
    fgets(mascota->nombre, 50, stdin);
    mascota->nombre[strcspn(mascota->nombre, "\n")] = 0;
    printf("Edad Aproximada: ");
    scanf("%d", &mascota->edad_aproximada);
    getchar();
    printf("Tamano: ");
    fgets(mascota->tamano, 100, stdin);
    mascota->tamano[strcspn(mascota->tamano, "\n")] = 0;
    printf("Peso en [kg]: ");
    scanf("%f", &mascota->peso);
    getchar();
    printf("Descripcion: ");
    fgets(mascota->descripcion, 200, stdin);
    mascota->descripcion[strcspn(mascota->descripcion, "\n")] = 0;

    FILE *archivo = fopen("Mascotas.txt" ,"a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    fprintf(archivo, "%s, %s, %d, %s, %.2f, %s\n",
            mascota->especie, mascota->nombre, mascota->edad_aproximada,
            mascota->tamano, mascota->peso, mascota->descripcion);

    if (fclose(archivo) == EOF) {
        printf("Error al cerrar el archivo\n");
    }
}

// Función para iniciar sesión
void iniciar_sesion(struct Cola* cola) {
    if (cola->frente == NULL) {
        printf("No hay adoptantes por atender.\n");
        return;
    }
    char contrasena[30];
    int intentos = 3;
    printf("Atencion de adoptante.\t");
    mostrar_id(cola);
    printf("\n");
    do {
        printf("Si falla 3 veces sera retirado de la fila de adoptantes y debera registrarse de nuevo.\n\nIngrese su contrasena: ");
        fgets(contrasena, sizeof(contrasena), stdin);
        contrasena[strcspn(contrasena, "\n")] = '\0';
        if (verificar_credenciales(cola, contrasena) == 1) {
            printf("\033[H\033[J");
            printf("Bienvenido/a al sistema.\n");
            mostrar_menu_adoptante(NULL);
            break;
        } else {
            printf("\033[1;31mContrasena incorrecta.\033[0m\tIntentos restantes: %i\n", (intentos - 1));
            intentos--;
        }
    } while (intentos > 0);
    if (intentos == 0) {
        printf("\033[H\033[J");
        printf("Ha fallado 3 veces, usted fue retirado de la fila de adoptantes y debera registrarse de nuevo.\n");
        struct Nodo* nodo_actual = cola->frente;
        if (cola->frente == cola->atras) {
            cola->frente = NULL;
            cola->atras = NULL;
        } else {
            cola->frente = cola->frente->siguiente;
        }
        free(nodo_actual->adoptante);
        free(nodo_actual);
    }
}

// Función para mostrar el menú principal
void mostrar_menu_principal(struct Cola* cola) {
    struct Mascota *mascota;
    int consecutivo_global = 1;
    char opcion;
    do {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("A. Registro de adoptante\n");
        printf("B. Atender a un adoptante\n");
        printf("C.Agregar un animal\n");
        printf("D. Cerrar el sistema\n\n");
        mostrar_id(cola);
        printf("\nSeleccione una opcion: ");
        char input[3];
        fgets(input, sizeof(input), stdin);
        opcion = input[0];
        switch (opcion) {
            case 'A':
                printf("\033[H\033[J");
                registrar_adoptante(cola, &consecutivo_global);
                break;
            case 'B':
                printf("\033[H\033[J");
                iniciar_sesion(cola);
                break;
            case 'D':
                printf("\033[H\033[J");
                printf("Sistema cerrado.\n");
                break;
                case 'C':
                agregarMascotaArchivo(mascota);
                break;
            default:
                printf("\033[H\033[J");
                printf("Opcion no valida.\n");
        }
    } while (opcion != 'D');
}

int main() {
    printf("\033[H\033[J");
    struct Cola cola;
    inicializar_cola(&cola);
    mostrar_menu_principal(&cola);
    return 0;
}
