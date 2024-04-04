#include "usuario.h"
#include <string.h>
#include <stdio.h>
#include "sqlite3.h"

Usuario pedirUsuario(){
	Usuario u;

	printf("Introduce tu nombre: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",u.nombre);

	printf("Introduce tu contraseña: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",u.contrasenya);
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

Usuario buscarUsuarioBD(Usuario u, sqlite3 *db,sqlite3_stmt *stmt){
	int result;
	Usuario usuario;
	char buscarContrasenya[]="SELECT * FROM Usuario WHERE usuario=?";
	sqlite3_prepare_v2(db, buscarContrasenya, sizeof(buscarContrasenya) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, u.nombre, sizeof(u.nombre), SQLITE_STATIC);

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(usuario.nombre,(char*)sqlite3_column_text(stmt, 0));
			strcpy(usuario.contrasenya,(char*)sqlite3_column_text(stmt, 1));
		}
		} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
	return usuario;
}










