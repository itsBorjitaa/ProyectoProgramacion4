#include "categoria.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

int buscarIDCategoria(Categoria categoria,sqlite3 *db,sqlite3_stmt *stmt){
	int result,id = 0;
	char buscarID[]="SELECT * FROM categorias";
	sqlite3_prepare_v2(db, buscarID, sizeof(buscarID) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, categoria.nombreCategoria, sizeof(categoria.nombreCategoria), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	while (result == SQLITE_ROW) {
		if(strcmp(categoria.nombreCategoria,sqlite3_column_text(stmt,1))==0){
			id= sqlite3_column_int(stmt, 0);
		}
		result = sqlite3_step(stmt);
		} ;
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
	int id;
    Categoria nuevaCategoria;

    //utiliza el nombre de usuario del usuario que ha iniciado sesión

    printf("Escribe el nombre de la nueva categoría: "); fflush(stdout); fflush(stdin);
    scanf("%s", nuevaCategoria.nombreCategoria);
    id=buscarIDCategoria(nuevaCategoria,db,stmt);
    if(id==0){
    //Codigo para ejecutar el statement
    char insertarCategoria[] = "INSERT INTO Categorias(categoria) VALUES(?)";
    sqlite3_prepare_v2(db, insertarCategoria, sizeof(insertarCategoria) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nuevaCategoria.nombreCategoria, sizeof(nuevaCategoria.nombreCategoria), SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    }

    //Insertamos la categoria en la tabla categoriasPorUsuario
    insertarCategoriasPorUsuario(idUsuario, nuevaCategoria, db, stmt);
    printf("Categoría creada correctamente!\n");
    escribirLog("Categoría creada correctamente");
}

Categoria buscarCategoriaPorId(int id, sqlite3 *db,sqlite3_stmt *stmt) {
	Categoria cat;
	int result;

	char buscarCat[]="SELECT * FROM categorias";
		sqlite3_prepare_v2(db, buscarCat, sizeof(buscarCat) + 1, &stmt, NULL);
		result=sqlite3_step(stmt);
				while (result == SQLITE_ROW){
					if(id==sqlite3_column_int(stmt,0)){
						strcpy(cat.nombreCategoria,sqlite3_column_text(stmt,1));
					}
					result = sqlite3_step(stmt);
				}
		sqlite3_finalize(stmt);

	return cat;
}

void cargarCategoria(int idUsuario, sqlite3 *db,sqlite3_stmt *stmt) {
	int resultCant,i=0;
	//Consigo el numero de categorias que hay en la BD
	char buscarCantCat[] = "SELECT * FROM categoriasUsuario";
	sqlite3_prepare_v2(db, buscarCantCat, sizeof(buscarCantCat) + 1, &stmt, NULL);
	resultCant = sqlite3_step(stmt) ;
	while (resultCant == SQLITE_ROW){
		if(idUsuario==sqlite3_column_int(stmt,0)){
			i++;
		}
		resultCant = sqlite3_step(stmt);
	}

	int arrayId[i];
	i=0;
	char pegarArrayCat[] = "SELECT * FROM categoriasUsuario";
	sqlite3_prepare_v2(db, pegarArrayCat, sizeof(pegarArrayCat) + 1, &stmt, NULL);
	resultCant = sqlite3_step(stmt) ;
	while (resultCant == SQLITE_ROW){
	        	if(idUsuario==sqlite3_column_int(stmt,0)){
	        		arrayId[i]=sqlite3_column_int(stmt,1);
	        		i++;
	        	}
	        	resultCant = sqlite3_step(stmt);

	}
	sqlite3_finalize(stmt);
	for(int u=0;u<i;u++){
		printf("%i. %s\n",u+1, buscarCategoriaPorId(arrayId[u],db,stmt).nombreCategoria);
	}

}

void modificarCategoria(char nomCat, sqlite3 *db,sqlite3_stmt *stmt) {

}

void eliminarCategoria(int idU, sqlite3 *db,sqlite3_stmt *stmt) {
	Categoria cat;
	int cant = 0, id;

	cargarCategoria(idU, db, stmt);
	printf("Introduce el nombre de la categoria que quieres borrar: "); fflush(stdout); fflush(stdin);
	scanf("%s",cat.nombreCategoria);

	id = buscarIDCategoria(cat, db, stmt);
	if (id != 0) {
		//Encuentro cuantas veces apareze la categoria en categoriasPorUsuario
		char buscarCantCat[] = "SELECT * FROM categoriasUsuario";
		sqlite3_prepare_v2(db, buscarCantCat, sizeof(buscarCantCat) + 1, &stmt, NULL);
		int resultCant = sqlite3_step(stmt) ;
		while (resultCant == SQLITE_ROW){
				cant++;
			resultCant = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		if(cant == 1) {
			char eliminarCat[] = "DELETE FROM categoriasUsuario WHERE id_c_cu = ?";
			sqlite3_prepare_v2(db, eliminarCat, sizeof(eliminarCat) + 1, &stmt, NULL);
			sqlite3_bind_int(stmt, 1, id);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);

			char eliminarCat2[] = "DELETE FROM Categorias WHERE id_c = ?";
			sqlite3_prepare_v2(db, eliminarCat2, sizeof(eliminarCat2) + 1, &stmt, NULL);
			sqlite3_bind_int(stmt, 1, id);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else {
			char eliminarCatU[] = "DELETE FROM categoriasUsuario WHERE id_c_cu = ? AND id_u_cu = ?";
			sqlite3_prepare_v2(db, eliminarCatU, sizeof(eliminarCatU) + 1, &stmt, NULL);
			sqlite3_bind_int(stmt, 1, id);
			sqlite3_bind_int(stmt, 2, idU);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
	} else {
		printf("ERROR: Esta categoria no existe!!\n"); fflush(stdout);
	}
}

