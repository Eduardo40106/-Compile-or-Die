#include <stdio.h>
#include "funcionalidades.h"


int main(){
    printf("\033[H\033[J"); 
    struct Cola laCola;
    inicializarCola(&laCola);
    menuPrincipal(&laCola);


    return 0;
} 