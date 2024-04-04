#ifndef CATEGORIA_H_
#define CATEGORIA_H_

#include "usuario.h"
#include "sqlite3.h"

typedef struct categoria {
    char nombreCategoria[20];
}Categoria;

void crearCategoria(Usuario *usuario,sqlite3 *db,sqlite3_stmt *stmt);
Categoria buscarCategoriaPorId(int id, sqlite3 *db,sqlite3_stmt *stmt);
void insertarCategoriasPorUsuario(Usuario *usuario,Categoria categoria, sqlite3 *db,sqlite3_stmt *stmt);

#endif /* CATEGORIA_H_ */
