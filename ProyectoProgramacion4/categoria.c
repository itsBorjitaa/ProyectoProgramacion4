#include "categoria.h"
#include <stdio.h>
#include <string.h>

Categoria pedirCategoria(Usuario usuario) {
    Categoria nuevaCategoria;

    //utiliza el nombre de usuario del usuario que ha iniciado sesión
    strcpy(nuevaCategoria.nombreUsuario, usuario.nombre);

    printf("Escribe el ID de la nueva categoría: ");
    scanf("%d", &nuevaCategoria.idCategoria);

    printf("Escribe el nombre de la nueva categoría: ");
    scanf("%s", nuevaCategoria.nombreCategoria);

    return nuevaCategoria;
}
