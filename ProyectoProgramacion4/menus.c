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

char menuGastos(){
	char opcion;
		printf("1. Añadir gasto\n");
		printf("2. Modificar gasto\n");
		printf("3. Eliminar gasto\n");
		printf("4. Ver gastos del usuario\n");
		printf("0. Volver\n");
		printf("Elige una opción: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%c",&opcion);
		return opcion;
}

char menuCategorias(){
	char opcion;
		printf("1. Añadir categoria\n");
		printf("2. Modificar categoria\n");
		printf("3. Eliminar categoria\n");
		printf("4. Ver categorias del usuario\n");
		printf("0. Volver\n");
		printf("Elige una opción: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%c",&opcion);
		return opcion;
}

char menuSaldo(){
	char opcion;
		printf("1. Modificar saldo\n");
		printf("0. Cerrar sesión\n");
		printf("Elige una opción: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%c",&opcion);
		return opcion;
}

