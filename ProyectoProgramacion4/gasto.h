#ifndef GASTO_H_
#define GASTO_H_

#include <time.h>
#include "usuario.h"

typedef struct gasto{
	int idGasto;
	char nombreUsuario[20];
	int idCategoria;
	double cantidad;
	struct tm fecha;
}Gasto;

void pedirFecha(struct tm *fecha);
Gasto pedirGasto(Usuario usuario);

#endif /* GASTO_H_ */
