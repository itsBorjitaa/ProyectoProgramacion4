#ifndef GASTO_H_
#define GASTO_H_

#include <time.h>
#include "usuario.h"
#include "sqlite3.h"

typedef struct{
	int dia;
	int mes;
	int anyo;
}fecha;
typedef struct gasto{
	int idUsuario;
	fecha fecha;
	double coste;
	char concepto[30];
	char categoria[30];
}Gasto;

void crearGasto(int IdUsuario,sqlite3 *db,sqlite3_stmt *stmt);

#endif /* GASTO_H_ */
