#include "usuario.h"
#include <string.h>
#include <stdio.h>
#include "sqlite3.h"

Usuario pedirUsuario(){
	Usuario u;

	printf("Introduce tu nombre: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.nombre);

	printf("Introduce tu contraseña: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.contrasenya);
	return u;
}

int contrasenyaCorrecta(char *conU,char *con){
	int correcta = 0;
	if(strcmp(conU, con)==0){
		correcta = 1;
	}
	return correcta;
}

void insertarUsuarioBD(Usuario usuario, sqlite3 *db,sqlite3_stmt *stmt) {
	Usuario nuevoUsuario;
	//Codigo para ejecutar el statement
	char insertarUsuario[] = "INSERT INTO Usuario VALUES(?, ?)";
	sqlite3_prepare_v2(db, insertarUsuario, sizeof(insertarUsuario) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, nuevoUsuario.nombre, sizeof(nuevoUsuario.nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, nuevoUsuario.contrasenya, sizeof(nuevoUsuario.contrasenya), SQLITE_STATIC);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

Usuario buscarUsuarioBD(char nombre, sqlite3 *db,sqlite3_stmt *stmt) {
	Usuario usuario;
	int result;
	//Codigo para ejecutar los statements
	char buscarUsuario[] = "SELECT usuario FROM Usuario WHERE usuario = ?";
	sqlite3_prepare_v2(db, buscarUsuario, sizeof(buscarUsuario) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, nombre, sizeof(nombre), SQLITE_STATIC);
	result=sqlite3_step(stmt);
	strcpy(usuario.nombre,(char) result);
	sqlite3_finalize(stmt);

	char buscarContra[] = "SELECT contrasenya FROM Usuario WHERE usuario = ?";
	sqlite3_prepare_v2(db, buscarContra, sizeof(buscarContra) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, nombre, sizeof(nombre), SQLITE_STATIC);
	result=sqlite3_step(stmt);
	strcpy(usuario.contrasenya,(char) result);
	sqlite3_finalize(stmt);
	return usuario;
}










