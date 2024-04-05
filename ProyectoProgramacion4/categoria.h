#ifndef CATEGORIA_H_
#define CATEGORIA_H_

#include "usuario.h"
#include "sqlite3.h"

typedef struct categoria {
    char nombreCategoria[20];
}Categoria;

void crearCategoria(int idUsuario,sqlite3 *db,sqlite3_stmt *stmt);
Categoria buscarCategoriaPorId(int id, sqlite3 *db,sqlite3_stmt *stmt);
void insertarCategoriasPorUsuario(int idUsuario,Categoria categoria, sqlite3 *db,sqlite3_stmt *stmt);
Categoria buscarCategoriaPorId(int id, sqlite3 *db,sqlite3_stmt *stmt);
void cargarCategoria(int idUsuario, sqlite3 *db,sqlite3_stmt *stmt);
void modificarCategoria(char nomCat, sqlite3 *db,sqlite3_stmt *stmt);
void eliminarCategoria(int idU, sqlite3 *db,sqlite3_stmt *stmt);

#endif /* CATEGORIA_H_ */
