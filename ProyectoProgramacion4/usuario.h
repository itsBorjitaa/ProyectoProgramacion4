#ifndef USUARIO_H_
#define USUARIO_H_
#include "sqlite3.h"
typedef struct usuario{
	char nombre[20];
	char contrasenya[20];
}Usuario;

Usuario pedirUsuario();
int contrasenyaCorrecta(char *conU, char *con);
void insertarUsuario(Usuario usuario, sqlite3 *db,sqlite3_stmt *stmt);
//Usuario buscarUsuario(char nombre, sqlite3 *db,sqlite3_stmt *stmt);

#endif /* USUARIO_H_ */
