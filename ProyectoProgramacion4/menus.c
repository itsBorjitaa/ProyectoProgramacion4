#include <stdio.h>
#include "menus.h"

char menuLogin(){
	char opcion;
	printf("DEUSTOFINANZAS\n");
	printf("1. Iniciar Sesión\n");
	printf("2. Registrarse\n");
	printf("0. Salir\n");
	printf("Elige una opción: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}

char menuPrincipal(){
	char opcion;
	printf("SALDO: \n");
	printf("1. Gastos\n");
	printf("2. Categorías\n");
	printf("3. Saldo\n");
	printf("0. Cerrar sesión\n");
	printf("Elige una opción: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}



