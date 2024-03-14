#ifndef LISTAUSUARIOS_H_
#define LISTAUSUARIOS_H_

#include "usuario.h"
#include <stdlib.h>
typedef struct listaUsuarios{
	Usuario * aUsuarios;
	int tam;
	int numU;
}ListaUsuarios;

void volcarFicheroAListaUsuarios(ListaUsuarios *lu, char *nomfich);
int buscarUsuario(ListaUsuarios lu, char *nom);
void anyadirUsuario(ListaUsuarios *lu, Usuario u);
void volcarListaUsuariosAFichero(ListaUsuarios lu, char *nomfich);

#endif /* LISTAUSUARIOS_H_ */
