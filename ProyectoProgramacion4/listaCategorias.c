#include "listaCategorias.h"
#include <stdio.h>
#include <stdlib.h>

ListaCategoria cargarCategoria(Usuario u, sqlite3 *db,sqlite3_stmt *stmt) {
	ListaCategoria lc;
	int resultCant, resultadoId, i, cantId = 0;

	//Consigo el numero de categorias que hay en la BD
	char buscarCantCat[] = "SELECT COUNT id_c_cu FROM categoriasUsuario WHERE usuario_cu = ?";
	sqlite3_prepare_v2(db, buscarCantCat, sizeof(buscarCantCat) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, u.nombre, sizeof(u.nombre), SQLITE_STATIC);
	do {
		resultCant = sqlite3_step(stmt) ;
	        if (resultCant == SQLITE_ROW) {
	            lc.tam = sqlite3_column_int(stmt, 0);
	        }
	        } while (resultCant == SQLITE_ROW);
	sqlite3_finalize(stmt);

	int array[lc.tam];
	char buscarIdCat[] = "SELECT id_c_cu FROM categoriasUsuario WHERE usuario_cu = ?";
		sqlite3_prepare_v2(db, buscarIdCat, sizeof(buscarIdCat) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, u.nombre, sizeof(u.nombre), SQLITE_STATIC);
		do {
			resultadoId = sqlite3_step(stmt);
		        if (resultadoId == SQLITE_ROW) {
		        	array[cantId] = resultadoId;
		        	cantId++;
		        }
		    } while (resultadoId == SQLITE_ROW);
		sqlite3_finalize(stmt);


	lc.aCategoria = (Categoria*)malloc(lc.tam*sizeof(Categoria));

	for(i=0;i<=cantId;i++) {
		lc.aCategoria[lc.numCat] = buscarCategoriaPorId(array[i],db, stmt);
		lc.numCat++;
	}

	return lc;
}
void imprimirLista(ListaCategoria lc) {
	int i;
	for(i=0;i<lc.numCat;i++){
		printf("%s", lc.aCategoria[i]); fflush(stdout);
	}
}
