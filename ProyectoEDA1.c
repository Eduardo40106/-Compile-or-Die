#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define PREFIJO "C:\\Temp\\edagpo15sem252\\"
#else
#define PREFIJO "/tmp/edagpo15sem252/"
#endif

// Estructuras de datos
struct Mascota {
	struct Mascota* siguiente;
	char descripcion[202];
	char especie[52];
	char nombre[52];
	char tamano[22];
	int edad;
	float peso;
};

struct Adoptante {
	struct Adoptante* siguiente;
	char direccion[102];
	char nombre[52];
	char apellidoP[52];
	char apellidoM[52];
	char correo[52];
	char id[32];
	char contrasena[22];
	char telefono[17];
};

struct ListaMascotas {
	struct Mascota* inicio;
};

struct FilaAdoptantes {
	struct Adoptante* frente;
	struct Adoptante* atras;
};

struct SistemaAdopcion {
	struct ListaMascotas* mascotas;
	struct FilaAdoptantes* filaVirtual;
};


// Funciones declaradas
//void menuAdoptante(struct SistemaAdopcion* sistema);
//void iniciarSesion(struct SistemaAdopcion* sistema);
//void mostrarID(struct FilaAdoptantes* cola);

// Función para encolar un nuevo adoptante
void encolar(struct FilaAdoptantes* cola, struct Adoptante* nuevo) {
	nuevo->siguiente = NULL;

	if (cola->frente == NULL) {
		cola->frente = nuevo;
		cola->atras = nuevo;
	} else {
		cola->atras->siguiente = nuevo;
		cola->atras = nuevo;
	}
}


// Función para generar ID
void generarID(struct Adoptante* adoptante, int consecutivo) {
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


// Función para mostrar mascotas por especie
void mostrarMascotasEspecie(struct ListaMascotas* mascotas, char* especie, char bandera) {
	struct Mascota* actual = mascotas->inicio;
	int encontrado = 0;

	while(actual != NULL) {
		if(!(strcmp(actual->especie, especie) * bandera)) {
			printf("\n=== Datos de la Mascota ===\n");
			printf("Especie: %s\n", actual->especie);
			printf("Nombre: %s\n", actual->nombre);
			printf("Edad: %d años\n", actual->edad);
			printf("Tamaño: %s\n", actual->tamano);
			printf("Peso: %.2f kg\n", actual->peso);
			printf("Descripción: %s\n", actual->descripcion);
			encontrado = 1;
		}

		actual = actual->siguiente;
	}

	if(!encontrado)
		printf("\nNo se encontraron mascotas de la especie seleccionada.\n");
}

// Función para buscar mascotas por especie y edad
struct Mascota* buscarMascotasEspEd(struct Mascota* mascotas, char* especie, int edad_min, int edad_max) {
	if(mascotas != NULL) {
		char opcion = 0;

		if(!strcmp(mascotas->especie, especie) &&
				mascotas->edad >= edad_min && mascotas->edad <= edad_max) {
			printf("\n=== Mascota Encontrada ===\n");
			printf("Nombre: %s\n", mascotas->nombre);
			printf("Edad: %d años\n", mascotas->edad);
			printf("Descripción: %s\n", mascotas->descripcion);

			printf("Ingrese \"M\" para ADOPTAR, \"Q\" para SALIR, cualquier letra para continuar: ");
			scanf("%c", &opcion); getchar();
		}

		switch(opcion) {
			case 'M':
				return mascotas;
			case 'Q':
				break;
			default:
				return buscarMascotasEspEd(mascotas->siguiente, especie, edad_min, edad_max);
		}
	}

	return NULL;
}

// Función para procesar la adopción
void procesarAdopcion(struct SistemaAdopcion* sistema, struct Mascota* mascota) {
	if(mascota != NULL) {
		char confirmacion[20];

		printf("\n¿Desea adoptar a %s? (CONFIRMAR/CANCELAR): ", mascota->nombre);
		scanf("%19s", confirmacion); getchar();

		if(!strcmp(confirmacion, "CONFIRMAR")) {
			struct Mascota* ant = sistema->mascotas->inicio;
			struct Adoptante* act = sistema->filaVirtual->frente;

			printf("\n¡Felicitaciones! Ha adoptado a %s.\n", mascota->nombre);
			printf("Por favor, diríjase al área de mascotas bajo resguardo.\n");

			if(sistema->mascotas->inicio != mascota) {
				while(ant->siguiente != mascota)
					ant = ant->siguiente;
				ant->siguiente = mascota->siguiente;
			} else
				sistema->mascotas->inicio = sistema->mascotas->inicio->siguiente;

			sistema->filaVirtual->frente = act->siguiente;

			free(mascota); free(act);

			time_t inicio = time(NULL);

			while(time(NULL) - inicio < 3);
		} else
			printf("\nPuede seguir revisando la lista de mascotas.\n");
	}
}

// Función para mostrar el menú de adoptante
void menuAdoptante(struct SistemaAdopcion* sistema) {
	char opcion = 0;
	char especie[50];
	int edad_min, edad_max;

	while(opcion != '5') {
		printf("\n=== MENÚ DE ADOPTANTE ===\n");
		printf("1. Mostrar mascotas de todas las especies\n");
		printf("2. Mostrar mascotas por especie\n");
		printf("3. Buscar una mascota en específico por nombre\n");
		printf("4. Buscar mascotas indicando especie y un intervalo de edad\n");
		printf("5. Salir\n");
		printf("Seleccione una opción: ");
		scanf(" %c", &opcion); getchar();

		switch(opcion) {
			case '1':
				mostrarMascotasEspecie(sistema->mascotas, "", 0);
				break;
			case '2':
				printf("Ingrese la especie a buscar: ");
				scanf("%49s", especie); getchar();

				mostrarMascotasEspecie(sistema->mascotas, especie, 1);
				break;
			case '3':
				break;
			case '4':
				printf("Ingrese la especie: ");
				scanf("%49s", especie); getchar();

				printf("Ingrese edad mínima: ");
				scanf("%d", &edad_min); getchar();

				printf("Ingrese edad máxima: ");
				scanf("%d", &edad_max); getchar();

				procesarAdopcion(sistema,
						buscarMascotasEspEd(sistema->mascotas->inicio, especie, edad_min, edad_max));
				break;
			case '5':
				break;
			default:
				printf("\nOpción no válida.\n");
		}
	}
}

// Función para registrar un nuevo adoptante
void registrarAdoptante(struct FilaAdoptantes* cola, int* consecutivoGlobal) {
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
	} while(strcmp(confirmar, "SI") != 0);

	generarID(nuevo, *consecutivoGlobal);
	(*consecutivoGlobal)++;

	printf("Su ID es: \033[1;33m%s\033[0m\nNecesitara su ID y su contrasena para iniciar sesion en el sistema\n", nuevo->id);

	char continuar[20];

	printf("Escriba CONTINUAR para finalizar el registro: ");
	fgets(continuar, sizeof(continuar), stdin);

	continuar[strcspn(continuar, "\n")] = 0;

	if(strcmp(continuar, "CONTINUAR") == 0) {
		encolar(cola, nuevo);
		printf("\033[H\033[J");
		printf("Adoptante agregado correctamente.\n");
	} else {
		free(nuevo);
		//printf("\033[H\033[J");
		printf("Registro cancelado.\n");
	}
}

// Funcion para registrar mascota
void registrarMascota(struct ListaMascotas* mascotas) {
	char archivo[50] = PREFIJO;

	strcat(archivo, "admin.txt");

	FILE* adminFile = fopen(archivo, "r");

	if(adminFile != NULL) {
		char adminNick[26] = {"\0"}, nick[26] = {"\0"}, adminContr[26] = {"\0"}, contr[26] = {"\0"};
		char i = 0;

		while((adminNick[i] = fgetc(adminFile)) != ':')
			i++;
		adminNick[i] = 0;
		fscanf(adminFile, "%s", adminContr);

		printf("Ingrese nickname: ");
		scanf("%s", nick); getchar();

		printf("Ingrese contraseña: ");
		scanf("%s", contr); getchar();

		if(!strcmp(adminNick, nick) && !strcmp(adminContr, contr)) {
			struct Mascota* nueva = (struct Mascota*)calloc(1, sizeof(struct Mascota));

			printf("\nRegistro de mascota.\nIngrese los datos necesarios para su registro por favor\n");

			printf("Nombre: ");
			fgets(nueva->nombre, 51, stdin);
			nueva->nombre[strcspn(nueva->nombre, "\n")] = 0;

			printf("Especie: ");
			fgets(nueva->especie, 51, stdin);
			nueva->especie[strcspn(nueva->especie, "\n")] = 0;

			printf("Tamaño: ");
			fgets(nueva->tamano, 21, stdin);
			nueva->tamano[strcspn(nueva->tamano, "\n")] = 0;

			printf("Descripcion: ");
			fgets(nueva->descripcion, 201, stdin);
			nueva->descripcion[strcspn(nueva->descripcion, "\n")] = 0;

			printf("Edad aproximada: ");
			scanf("%d", &nueva->edad); getchar();

			printf("Peso: ");
			scanf("%f", &nueva->peso); getchar();

			nueva->siguiente = mascotas->inicio;
			mascotas->inicio = nueva;

			printf("\nMascota registrada exitosamente\n\n");
		} else
			printf("\t\a!Datos ingresados no corresponden a la cuenta de administrador\n\n");

		fclose(adminFile);
		adminFile = NULL;
	} else
		printf("\t\a!No fue posible leer archivo \"admin.txt\"\n\n");
}

// Función para mostrar el ID del adoptante actual
void mostrarID(struct FilaAdoptantes* cola) {
	if(cola->frente != NULL)
		printf("ID del adoptante a atender: \033[1;33m%s\033[0m\n", cola->frente->id);
	else
		printf("ID del adoptante a atender: No hay nadie en la fila.\n");
}

// Función para verificar credenciales
int verificarCredenciales(struct FilaAdoptantes* cola, const char* contrasenaIngresada) {
	if(cola->frente == NULL) {
		printf("No hay adoptantes por atender\n");
		return 0;
	}

	if(!strcmp(cola->frente->contrasena, contrasenaIngresada))
		return 1;
	else
		return 0;
}

// Función para iniciar sesión
void iniciarSesion(struct SistemaAdopcion* sistema) {
	struct FilaAdoptantes* cola = sistema->filaVirtual;

	if (cola->frente == NULL) {
		printf("No hay adoptantes por atender.\n");
		return;
	}

	char contrasena[30];
	int intentos = 3;

	printf("Atencion de adoptante.\t");
	mostrarID(cola);
	printf("\n");

	do {
		printf("Si falla 3 veces sera retirado de la fila de adoptantes y debera registrarse de nuevo.\n\nIngrese su contrasena: ");
		fgets(contrasena, sizeof(contrasena), stdin);
		contrasena[strcspn(contrasena, "\n")] = '\0';

		if (verificarCredenciales(cola, contrasena) == 1) {
			printf("\033[H\033[J");
			printf("Bienvenido/a al sistema.\n");
			menuAdoptante(sistema);
			break;
		} else {
			printf("\033[1;31mContrasena incorrecta.\033[0m\tIntentos restantes: %i\n", (intentos - 1));
			intentos--;
		}
	} while (intentos > 0);

	if (!intentos) {
		printf("\033[H\033[J");
		printf("Ha fallado 3 veces, usted fue retirado de la fila de adoptantes y debera registrarse de nuevo.\n");

		struct Adoptante* actual = cola->frente;

		if (cola->frente == cola->atras) {
			cola->frente = NULL;
			cola->atras = NULL;
		} else {
			cola->frente = cola->frente->siguiente;
		}

		free(actual);
	}
}

// Función para inicializar el sistema
struct SistemaAdopcion* inicializarSistema() {
	struct SistemaAdopcion* sistema = (struct SistemaAdopcion*)calloc(1, sizeof(struct SistemaAdopcion));
	FILE *adoptFile, *mascotFile;
	char archivo1[51] = PREFIJO, archivo2[51] = PREFIJO;

	sistema->filaVirtual = (struct FilaAdoptantes*)calloc(1, sizeof(struct FilaAdoptantes));
	sistema->mascotas = (struct ListaMascotas*)calloc(1, sizeof(struct ListaMascotas));

	sistema->filaVirtual->frente = NULL; sistema->filaVirtual->atras = NULL;
	sistema->mascotas->inicio = NULL;

	strcat(archivo1, "adoptantes.txt"); strcat(archivo2, "mascotas.txt");

	if((adoptFile = fopen(archivo1, "r")) != NULL) {
		struct Adoptante* actual = (struct Adoptante*)calloc(1, sizeof(struct Adoptante));

		fseek(adoptFile, 0, SEEK_SET);

		while(fscanf(adoptFile, "%s%s%s%s%s%s%s%s",
					actual->nombre, actual->apellidoP, actual->apellidoM, actual->direccion,
					actual->correo, actual->telefono, actual->contrasena, actual->id) != EOF) {
			encolar(sistema->filaVirtual, actual);
			actual = (struct Adoptante*)calloc(1, sizeof(struct Adoptante));
		}

		fclose(adoptFile);
	}

	if((mascotFile = fopen(archivo2, "r")) != NULL) {
		struct Mascota* actual = (struct Mascota*)calloc(1, sizeof(struct Mascota));

		fseek(mascotFile, 0, SEEK_SET);

		while(fscanf(mascotFile, "%s%s%d%s%f%s",
					actual->nombre, actual->especie, &actual->edad,
					actual->tamano, &actual->peso, actual->descripcion) != EOF) {
			actual->siguiente = sistema->mascotas->inicio;
			sistema->mascotas->inicio = actual;
			actual = (struct Mascota*)calloc(1, sizeof(struct Mascota));
		}

		fclose(mascotFile);
	}

	return sistema;
}

void cerrarSistema(struct SistemaAdopcion* sistema) {
	char archivo1[51] = PREFIJO, archivo2[51] = PREFIJO;

	strcat(archivo1, "adoptantes.txt"); strcat(archivo2, "mascotas.txt");

	FILE *adoptFile = fopen(archivo1, "w"), *mascotFile = fopen(archivo2, "w");

	while(sistema->filaVirtual->frente != NULL) {
		struct Adoptante* tmp = sistema->filaVirtual->frente;

		if(adoptFile != NULL)
			fprintf(adoptFile,
					"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
					tmp->nombre, tmp->apellidoP, tmp->apellidoM, tmp->direccion,
					tmp->correo, tmp->telefono, tmp->contrasena, tmp->id);

		sistema->filaVirtual->frente = sistema->filaVirtual->frente->siguiente;
		free(tmp);
	} sistema->filaVirtual->atras = NULL;

	while(sistema->mascotas->inicio != NULL) {
		struct Mascota* tmp = sistema->mascotas->inicio;

		if(mascotFile != NULL)
			fprintf(mascotFile,
					"%s\n%s\n%d\n%s\n%f\n%s\n",
					tmp->nombre, tmp->especie, tmp->edad, tmp->tamano,
					tmp->peso, tmp->descripcion);

		sistema->mascotas->inicio = sistema->mascotas->inicio->siguiente;
		free(tmp);
	}

	fclose(adoptFile);
	fclose(mascotFile);

	free(sistema->filaVirtual);
	free(sistema->mascotas);
	free(sistema);
}


int main() {
	struct SistemaAdopcion* sistema = inicializarSistema();

	int consecutivoGlobal = 1;
	char opcion = 0;

	printf("\033[H\033[J");
	do {
		printf("\033[H\033[J");
		printf("\n----- MENU PRINCIPAL -----\n");
		printf("A. Registro de adoptante\n");
		printf("B. Atender a un adoptante\n");
		printf("C. Cerrar el sistema\n");
		printf("D. Registro de mascotas (solo administradores)\n\n");
		mostrarID(sistema->filaVirtual);

		printf("\nSeleccione una opcion: ");
		scanf("%c", &opcion); getchar();

		printf("\033[H\033[J");
		switch (opcion) {
			case 'A':
				registrarAdoptante(sistema->filaVirtual, &consecutivoGlobal);
				break;
			case 'B':
				iniciarSesion(sistema);
				break;
			case 'C':
				cerrarSistema(sistema);
				printf("Sistema cerrado.\n");
				break;
			case 'D':
				registrarMascota(sistema->mascotas);
				break;
			default:
				printf("Opcion no valida.\n");
		}
	} while(opcion != 'C');

	return 0;
}
