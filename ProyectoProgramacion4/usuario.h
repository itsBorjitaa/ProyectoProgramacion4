#ifndef USUARIO_H_
#define USUARIO_H_
#include "sqlite3.h"

typedef struct usuario{
	char nombre[20];
	char contrasenya[20];
}Usuario;

void insertarUsuarioBD(sqlite3 *db,sqlite3_stmt *stmt);
int iniciarSesionBD(Usuario *u,sqlite3 *db,sqlite3_stmt *stmt);
int existeUsuarioBD(char nombre[],sqlite3 *db,sqlite3_stmt *stmt);
#endif /* USUARIO_H_ */
