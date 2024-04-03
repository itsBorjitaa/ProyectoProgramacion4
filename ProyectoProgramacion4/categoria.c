#include "categoria.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

void crearCategoria(Usuario usuario,sqlite3 *db,sqlite3_stmt *stmt) {
    Categoria nuevaCategoria;

    //utiliza el nombre de usuario del usuario que ha iniciado sesión

    printf("Escribe el nombre de la nueva categoría: ");
    scanf("%s", nuevaCategoria.nombreCategoria);

    //Codigo para ejecutar el statement
    char insertarCategoria[] = "INSERT INTO Categorias VALUES(?)";
    sqlite3_prepare_v2(db, insertarCategoria, sizeof(insertarCategoria) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nuevaCategoria.nombreCategoria, sizeof(nuevaCategoria.nombreCategoria), SQLITE_STATIC);
    sqlite3_step(stmt);
}
void insertarCategoriasPorUsuario(Usuario usuario,Categoria categoria, sqlite3 *db,sqlite3_stmt *stmt){
	int id=buscarIDCategoria(categoria.nombreCategoria);

	char insertarCategoriasPorUsuario[]="INSERT INTO categoriasUsuario VALUES(?, ?)";
	sqlite3_prepare_v2(db, insertarCategoriasPorUsuario, sizeof(insertarCategoriasPorUsuario) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, usuario.nombre, sizeof(usuario.nombre), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, id);
	sqlite3_step(stmt);
}
int buscarIDCategoria(Categoria categoria,sqlite3 *db,sqlite3_stmt *stmt){
	int result;

	char buscarID[]="SELECT id_c FROM categorias WHERE categoria = ?";
	sqlite3_prepare_v2(db, buscarID, sizeof(buscarID) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, categoria.nombreCategoria, sizeof(categoria.nombreCategoria), SQLITE_STATIC);
	result=sqlite3_step(stmt);

	return result;
}
