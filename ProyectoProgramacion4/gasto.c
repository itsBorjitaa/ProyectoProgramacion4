#include "gasto.h"
#include <stdio.h>
#include <string.h>

//función para pedir al usuario que ingrese una fecha en el formato "dd/mm/aa"
void pedirFecha(struct tm *fecha) {
    printf("Ingrese la fecha (día/mes/año): ");
    scanf("%d/%d/%d", &fecha->tm_mday, &fecha->tm_mon, &fecha->tm_year);
    fecha->tm_mon -= 1; //para que en struct tm el mes empiece desde 0
    fecha->tm_year -= 1900; //para que en struct tm el año sea el número de años desde 1900
}

Gasto pedirGasto(Usuario usuario) {
    Gasto nuevoGasto;

    //utiliza el nombre de usuario del usuario que ha iniciado sesión
    strcpy(nuevoGasto.nombreUsuario, usuario.nombre);

    printf("Escribe el ID de la categoría: ");
    scanf("%d", &nuevoGasto.idCategoria);

    printf("Escribe la cantidad: ");
    scanf("%lf", &nuevoGasto.cantidad);

    //se le pide al usuario que ingrese la fecha
    printf("Escribe la fecha del gasto:\n");
    pedirFecha(&nuevoGasto.fecha);

    return nuevoGasto;
}
