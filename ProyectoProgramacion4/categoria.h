#ifndef CATEGORIA_H_
#define CATEGORIA_H_

#include "usuario.h"

typedef struct categoria {
    int idCategoria;
    char nombreCategoria[20];
    char nombreUsuario[20];
}Categoria;

Categoria pedirCategoria(Usuario usuario);

#endif /* CATEGORIA_H_ */
