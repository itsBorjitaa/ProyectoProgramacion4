#ifndef LISTACATEGORIAS_H_
#define LISTACATEGORIAS_H_
#include "categoria.h"
#include "sqlite3.h"

typedef struct listaCategorias{
	Categoria * aCategoria;
	int tam;
	int numCat;
}ListaCategoria;

ListaCategoria cargarCategoria(Usuario u, sqlite3 *db,sqlite3_stmt *stmt);
void imprimirLista(ListaCategoria lc);

#endif /* LISTACATEGORIAS_H_ */
