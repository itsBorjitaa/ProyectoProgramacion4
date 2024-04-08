#include <stdio.h>
#include "menus.h"
#include "saldo.h"
#include "sqlite3.h"

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

char menuPrincipal(int idU,sqlite3 *db,sqlite3_stmt *stmt) {
    char opcion;
    printf("────────────────------────────────────\n");
    printf("1. Gastos\n");
    printf("2. Categorías\n");
    printf("3. Saldo\n");
    printf("0. Cerrar sesión\n");
    mostrarSaldo(idU,db,stmt);
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
    printf("0. Volver\n");
    printf("──────────────────────────────────────────\n");
    printf("Elige una opción: ");
    fflush(stdout);
    fflush(stdin);
    scanf(" %c", &opcion);
    return opcion;
}
