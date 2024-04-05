#include "categoria.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

int buscarIDCategoria(Categoria categoria,sqlite3 *db,sqlite3_stmt *stmt){
	int result,id;
	char buscarID[]="SELECT id_c FROM categorias WHERE categoria = ?";
	sqlite3_prepare_v2(db, buscarID, sizeof(buscarID) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, categoria.nombreCategoria, sizeof(categoria.nombreCategoria), SQLITE_STATIC);
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			id= sqlite3_column_int(stmt, 0);
		}
		} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
	return id;
}

void insertarCategoriasPorUsuario(int idUsuario,Categoria categoria, sqlite3 *db,sqlite3_stmt *stmt){
	int id=buscarIDCategoria(categoria,db,stmt);

	char insertarCategoriasPorUsuario[]="INSERT INTO categoriasUsuario VALUES(?, ?)";
	sqlite3_prepare_v2(db, insertarCategoriasPorUsuario, sizeof(insertarCategoriasPorUsuario) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, idUsuario);
	sqlite3_bind_int(stmt, 2, id);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void crearCategoria(int idUsuario,sqlite3 *db,sqlite3_stmt *stmt) {
    Categoria nuevaCategoria;

    //utiliza el nombre de usuario del usuario que ha iniciado sesión

    printf("Escribe el nombre de la nueva categoría: "); fflush(stdout); fflush(stdin);
    scanf("%s", nuevaCategoria.nombreCategoria);

    //Codigo para ejecutar el statement
    char insertarCategoria[] = "INSERT INTO Categorias(categoria) VALUES(?)";
    sqlite3_prepare_v2(db, insertarCategoria, sizeof(insertarCategoria) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nuevaCategoria.nombreCategoria, sizeof(nuevaCategoria.nombreCategoria), SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    //Insertamos la categoria en la tabla categoriasPorUsuario
    insertarCategoriasPorUsuario(idUsuario, nuevaCategoria, db, stmt);
    printf("Categoría creada correctamente!\n");
    escribirLog("Categoría creada correctamente");
}

Categoria buscarCategoriaPorId(int id, sqlite3 *db,sqlite3_stmt *stmt) {
	Categoria cat;
	int result;

	char buscarCat[]="SELECT categoria FROM categorias WHERE id_c = ?";
		sqlite3_prepare_v2(db, buscarCat, sizeof(buscarCat) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, id, sizeof(id), SQLITE_STATIC);
		result = sqlite3_step(stmt);
		strcpy(cat.nombreCategoria,(char) result);
		sqlite3_finalize(stmt);

	return cat;
}


