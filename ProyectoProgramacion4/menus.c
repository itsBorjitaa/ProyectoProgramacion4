#include <stdio.h>
#include "menus.h"

char menuLogin() {
    char opcion;
    printf("─────────────── DEUSTOFINANZAS ───────────────\n");
    printf("1. Iniciar Sesión\n");
    printf("2. Registrarse\n");
    printf("0. Salir\n");
    printf("──────────────────────────────────────────────\n");
    printf("Elige una opción: ");
    fflush(stdout);
    fflush(stdin);
    scanf(" %c", &opcion);
    return opcion;
}

char menuPrincipal() {
    char opcion;
    printf("──────────────── SALDO: ────────────────\n");
    printf("1. Gastos\n");
    printf("2. Categorías\n");
    printf("3. Saldo\n");
    printf("0. Cerrar sesión\n");
    printf("──────────────────────────────────────\n");
    printf("Elige una opción: ");
    fflush(stdout);
    fflush(stdin);
    scanf(" %c", &opcion);
    return opcion;
}

char menuGastos() {
    char opcion;
    printf("────────────────── GASTOS ──────────────────\n");
    printf("1. Añadir gasto\n");
    printf("2. Modificar gasto\n");
    printf("3. Eliminar gasto\n");
    printf("4. Ver gastos del usuario\n");
    printf("0. Volver\n");
    printf("──────────────────────────────────────────\n");
    printf("Elige una opción: ");
    fflush(stdout);
    fflush(stdin);
    scanf(" %c", &opcion);
    return opcion;
}

char menuCategorias() {
    char opcion;
    printf("──────────────── CATEGORÍAS ────────────────\n");
    printf("1. Añadir categoría\n");
    printf("2. Modificar categoría\n");
    printf("3. Eliminar categoría\n");
    printf("4. Ver categorías del usuario\n");
    printf("0. Volver\n");
    printf("──────────────────────────────────────────\n");
    printf("Elige una opción: ");
    fflush(stdout);
    fflush(stdin);
    scanf(" %c", &opcion);
    return opcion;
}

char menuSaldo() {
    char opcion;
    printf("────────────── MODIFICAR SALDO ─────────────\n");
    printf("1. Modificar saldo\n");
    printf("0. Cerrar sesión\n");
    printf("──────────────────────────────────────────\n");
    printf("Elige una opción: ");
    fflush(stdout);
    fflush(stdin);
    scanf(" %c", &opcion);
    return opcion;
}

char menuModificarGastos() {
	char opcion;
	printf("────────────── MODIFICAR GASTOS ─────────────\n");
	printf("1. Modificar fecha\n");
	printf("2. Modificar concepto\n");
	printf("3. Modificar codste\n");
	printf("4. Modificar categoria\n");
	printf("0. Cerrar sesión\n");
	printf("──────────────────────────────────────────\n");
	printf("Elige una opción: ");
	fflush(stdout);
	fflush(stdin);
	scanf(" %c", &opcion);
	return opcion;
}
