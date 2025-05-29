// Aqui van las declaraciones de las estructuras y los prototipos de las funciones
#ifndef MISFUNCIONES_H
#define MISFUNCIONES_H

#ifdef _WIN32
    #define PREFIJO "C:\\Temp\\edagpo15sem252\\"
#elif __unix__
    #define PREFIJO "/tmp/edagpo15sem252/"

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

struct Mascota {
	char descripcion[202];
	char especie[52];
	char nombre[52];
	char tamano[22];
	int edad;
	float peso;
	char adoptada;
	struct Mascota* siguiente;

};

struct Nodo {
    struct Adoptante* persona;
    struct Nodo* Aptsiguiente;
};

struct ListaMascotas {
    struct Mascota* inicio;
}

struct Cola {
    struct Nodo* Aptfrente;
    struct Nodo* Aptatras;
};

void inicializarCola(struct Cola* laCola);
void encolar(struct Cola* laCola, struct Adoptante* nuevo);
void generarID(struct Adoptante* a, int consecutivo);
void registroAdoptante(struct Cola* laCola, int* consecutivoGlobal);
void registrarMascota(struct ListaMascotas* mascotas);
void buscarMascotasEspecie(struct Mascota* mascotas, char* especie, int edad_min, int edad_max) {
void menuPrincipal(struct Cola* laCola);
void mostrarMenuB();
void controlarFlujoMenuB(struct Cola* laCola);
void iniciarSesion(struct Cola *laCola);
void mostrarID(struct Cola* laCola);
int verificarCredenciales(struct Cola *laCola, const char *contrasenaIngresada);
void mostrar_mascotas_por_especie(struct Mascota* mascotas, char* especie);



#endif
