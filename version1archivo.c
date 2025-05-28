#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void mostrarMenuB();
void controlarFlujoMenuB();
void iniciarSesion();
void mostrarID();
// Estructura que representa a un adoptante con sus datos
struct Adoptante {
    char nombre[50];
    char apellidoP[50];
    char apellidoM[50];
    char direccion[100];
    char correo[50];
    char telefono[15];
    char contrasena[20];
    char id[30]; // ID generado
};

// Nodo de la cola que contiene un adoptante 
struct Nodo {
    struct Adoptante* persona;
    struct Nodo* Aptsiguiente;
};
//Estructura que representa una mascota 
struct Mascota {
    char especie[50];
    char nombre[50];
    int edad;
    char tamano[20];
    float peso;
    char descripcion[200];
struct Mascota * Aptsiguiente;
};
// Cola de adoptantes
struct Cola {
    struct Nodo* Aptfrente;
    struct Nodo* Aptatras;
};

void inicializarCola(struct Cola* laCola) {
    laCola->Aptfrente = NULL;
    laCola->Aptatras = NULL;
}

// Encola a un nuevo adoptante
void encolar(struct Cola* laCola, struct Adoptante* nuevo) {
    struct Nodo* AptnodoNuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    AptnodoNuevo->persona = nuevo;
    AptnodoNuevo->Aptsiguiente = NULL;
    
    if (laCola->Aptfrente == NULL) {
        laCola->Aptfrente = AptnodoNuevo;
        laCola->Aptatras = AptnodoNuevo;
    } else {
        laCola->Aptatras->Aptsiguiente = AptnodoNuevo;
        laCola->Aptatras = AptnodoNuevo;
    }//hola
}
// Lista de mascotas
struct Mascota* listaMascotas = NULL;
void leerAdoptantesDesdeArchivo(struct Cola* laCola, int* consecutivoGlobal);
void leerMascotasDesdeArchivo();
void agregarMascotaLista(struct Mascota** lista, struct Mascota* nueva);

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
//Lectura del adoptantes 
void leerAdoptantesDesdeArchivo(struct Cola* laCola, int* consecutivoGlobal) {
    FILE* archivo = fopen("adoptantes.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de adoptantes.\n");
        return;
    }

    struct Adoptante* nuevo;
    while (!feof(archivo)) {
        nuevo = (struct Adoptante*)malloc(sizeof(struct Adoptante));

        if (fscanf(archivo, "%s\n|%s\n|%s\n%s\n%s\n|%s\n%s\n%s\n\n",
                   nuevo->nombre, nuevo->apellidoP, nuevo->apellidoM, nuevo->direccion,
                   nuevo->correo, nuevo->telefono, nuevo->contrasena, nuevo->id) == 8) {

            encolar(laCola, nuevo);
            (*consecutivoGlobal)++;
        } else {
            free(nuevo);
            break;
        }
    }

    fclose(archivo);
}
// Lectura del apotante 
void leerMascotasDesdeArchivo() {
    FILE* archivo = fopen("mascotas.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de mascotas.\n");
        return;
    }


    while (!feof(archivo)) {
        struct Mascota* nueva = (struct Mascota*)malloc(sizeof(struct Mascota));
        if (fscanf(archivo, "%s49[^|]|%s29[^|]|%d\n", nueva->nombre, nueva->especie, &nueva->edad) == 3) {
            nueva->Aptsiguiente = NULL;
            agregarMascotaLista(&listaMascotas, nueva);
        } else {
            free(nueva);
            break;
        }
    }

    fclose(archivo);
}
void agregarMascotaLista(struct Mascota** lista, struct Mascota* nueva) {
    if (*lista == NULL) {
        *lista = nueva;
    } else {
        struct Mascota* actual = *lista;
        while (actual->Aptsiguiente != NULL) {
            actual = actual->Aptsiguiente;
        }
        actual->Aptsiguiente = nueva;
    }
}
// Realiza el registro del adoptante
void registroAdoptante(struct Cola* laCola, int* consecutivoGlobal) {
    struct Adoptante* Aptnuevo = (struct Adoptante*)malloc(sizeof(struct Adoptante));

    printf("Registro de adoptante.\nIngrese los datos necesarios para su registro porfavor\n");
    // Solicita los datos del adoptante
    printf("Nombre: "); //Imprime en pantalla el nombre del adoptante.
    fgets(Aptnuevo->nombre, 50, stdin);  //Guarda el nombre elegido por el usuario.
    Aptnuevo->nombre[strcspn(Aptnuevo->nombre, "\n")] = 0; //Elimia el salto de linea que por defecto tiene fgets.

    printf("Apellido paterno: "); //Imprime en pantalla el apellido paterno del adoptante.
    fgets(Aptnuevo->apellidoP, 50, stdin);  //Guarda el apellido paterno elegido por el usuario.
    Aptnuevo->apellidoP[strcspn(Aptnuevo->apellidoP, "\n")] = 0;  //Elimia el salto de linea que por defecto tiene fgets.

    printf("Apellido materno: ");  //Imprime en pantalla el apellido materno del adoptante.
    fgets(Aptnuevo->apellidoM, 50, stdin); //Guarda el apellido materno elegido por el usuario.
    Aptnuevo->apellidoM[strcspn(Aptnuevo->apellidoM, "\n")] = 0;  //Elimina el salto de linea que por defecto tiene fgets.

    printf("Direccion: "); //Imprime en pantalla la direccion del adoptante.
    fgets(Aptnuevo->direccion, 100, stdin); //Guarda la direccion elegida por el usuario.
    Aptnuevo->direccion[strcspn(Aptnuevo->direccion, "\n")] = 0; //Elimina el salto de linea que por defecto tiene fgets.

    printf("Correo electronico: "); //Imprime en pantalla el correo electronico del adoptante.
    fgets(Aptnuevo->correo, 50, stdin); //Guarda el correo electronico elegido por el usuario.
    Aptnuevo->correo[strcspn(Aptnuevo->correo, "\n")] = 0; //Elimina el salto de linea que por defecto tiene fgets.

    printf("Telefono: "); //Imprime en pantalla el telefono del adoptante.
    fgets(Aptnuevo->telefono, 15, stdin); //Guarda el telefono del adoptante.
    Aptnuevo->telefono[strcspn(Aptnuevo->telefono, "\n")] = 0; //Elimina el salto de linea que por defecto tiene fgets.

    printf("Contrasena: "); //Imprime en pantalla la contraseña del adoptante.
    fgets(Aptnuevo->contrasena, 20, stdin); //Guarda la contraseña elegida por el usuario.
    Aptnuevo->contrasena[strcspn(Aptnuevo->contrasena, "\n")] = 0; //Elimina el salto de linea que por defecto tiene fgets.

    // Confirmacion del usuario
    char confirmar[5];
    do {
        printf("\nLos datos son correctos? (SI/NO): ");
        fgets(confirmar, sizeof(confirmar), stdin); //Guarda el SI O NO elegido por el usuario 
        confirmar[strcspn(confirmar, "\n")] = 0; //Elimia el salto de linea que por defecto tiene fgets
    } while (strcmp(confirmar, "SI") != 0); //Terminara de ejecutarse el ciclo hasta que el usuario diga que SI. 

    // Genera ID
    generarID(Aptnuevo, *consecutivoGlobal);
    (*consecutivoGlobal)++; // Incrementa para el siguiente adoptante

    printf("Su ID es: \033[1;33m%s\033[0m\nNecesitara su ID y su contrasena para iniciar sesion en el sistema\n", Aptnuevo->id);

    // Confirmacion final
    printf("Escriba CONTINUAR para finalizar el registro: ");
    char continuar[20];
    fgets(continuar, sizeof(continuar), stdin);
    continuar[strcspn(continuar, "\n")] = 0;
    FILE* archivo = fopen("adoptantes.txt", "w+");
    if (strcmp(continuar, "CONTINUAR") == 0) {
        encolar(laCola, Aptnuevo);
        printf("\033[H\033[J");  
        printf("Adoptante agregado correctamente.\n");
        fprintf(archivo,
            "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
                   Aptnuevo->nombre, Aptnuevo->apellidoP, Aptnuevo->apellidoM, Aptnuevo->direccion,
                   Aptnuevo->correo, Aptnuevo->telefono, Aptnuevo->contrasena, Aptnuevo->id);
    } else {
        free(Aptnuevo);
        printf("\033[H\033[J");  
        printf("Registro cancelado.\n");
    }
    fclose(archivo);
}

// Muestra el menu principal
void menuPrincipal(struct Cola* laCola) {
    int consecutivoGlobal = 1;
    char opcion;

    do {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("A. Registro de adoptante\n");
        printf("B. Atender a un adoptante\n");
        printf("C. Cerrar el sistema\n\n");
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



int main() {
    printf("\033[H\033[J");

    struct Cola laCola;
    inicializarCola(&laCola);

    int consecutivoGlobal = 1;

    leerAdoptantesDesdeArchivo(&laCola, &consecutivoGlobal);
    leerMascotasDesdeArchivo();

    menuPrincipal(&laCola);
    return 0;
}