#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"

void registrarMascota(struct ListaMascotas* mascotas) {
  
	FILE* adminFile = fopen("admin.txt", "r");

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

			nueva->adoptada = 0;

			nueva->siguiente = mascotas->inicio;
			mascotas->inicio = nueva;

			printf("Mascota registrada exitosamente\n\n");
		} else
			printf("\t\a!Datos ingresados no corresponden a la cuenta de administrador\n\n");
	} else
		printf("\t\a!No fue posible leer archivo \"admin.txt\"\n\n");
}
