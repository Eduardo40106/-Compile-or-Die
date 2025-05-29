#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"

void buscar_mascotas_especie_edad(struct Mascota* mascotas, char* especie, int edad_min, int edad_max) {
	char opcion = 0;

	if(mascotas != NULL && !strcmp(mascotas->especie, especie) &&
			mascotas->edad >= edad_min && mascotas->edad <= edad_max) {
		printf("\n=== Mascota Encontrada ===\n");
		printf("Nombre: %s\n", mascotas->nombre);
		printf("Edad: %d años\n", mascotas->edad);
		printf("Descripción: %s\n", mascotas->descripcion);

		printf("Ingrese \"M\" para ADOPTAR, \"Q\" para SALIR, cualquier otra letra para continuar: ");
		scanf("%c", &opcion); getchar();
	}

	switch(opcion) {
		case 'M':
			mascotas->adoptada = 1;
		case 'Q':
			break;
		default:
			buscar_mascotas_especie_edad(mascotas->siguiente, especie, edad_min, edad_max);
	}
}
