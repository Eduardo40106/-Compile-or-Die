#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionalidades.h"

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
    }
}