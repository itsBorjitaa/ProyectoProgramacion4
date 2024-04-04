#include "usuario.h"
#include <string.h>
#include <stdio.h>
#include "sqlite3.h"

void insertarUsuarioBD(sqlite3 *db,sqlite3_stmt *stmt) {
	int existe;
	char nombre[20],contrasenya[20];
	printf("Introduce tu nombre: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s", nombre);
	printf("Introduce tu contraseña: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",contrasenya);
	//Codigo para ejecutar el statement
	existe=existeUsuarioBD(nombre,db,stmt);
	if(existe>0){
		printf("ERROR! Este usuario ya existe!\n");
		fflush(stdout);
		escribirLog("ERROR! Este usuario ya existe");
	}else{
	char insertarUsuario[] = "INSERT INTO Usuario(usuarioNombre,contrasenya) VALUES(?, ?)";
	sqlite3_prepare_v2(db, insertarUsuario, sizeof(insertarUsuario) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, nombre, sizeof(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, contrasenya, sizeof(contrasenya), SQLITE_STATIC);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	printf("Se ha registrado correctamente!\n");
	escribirLog("Se ha registrado correctamente");
	}
}

int iniciarSesionBD(Usuario *u,sqlite3 *db,sqlite3_stmt *stmt){
	int result,id,existe;
	id=0;
	printf("Introduce tu nombre: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s", u->nombre);
	printf("Introduce tu contraseña: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",u->contrasenya);
	existe=existeUsuarioBD(u->nombre,db,stmt);
	if(existe>0){
	char conseguirID[]="SELECT * FROM usuario";
	sqlite3_prepare_v2(db, conseguirID, sizeof(conseguirID) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, u->nombre, sizeof(u->nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, u->contrasenya, sizeof(u->contrasenya), SQLITE_STATIC);


	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			if(strcmp(u->nombre,sqlite3_column_text(stmt,1))==0&&strcmp(u->contrasenya,sqlite3_column_text(stmt,2))==0){
				id=sqlite3_column_int(stmt,0);
		}
		}
	}while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
	if(id>1){
	}

	}
	return id;
}

int existeUsuarioBD(char nombre[],sqlite3 *db,sqlite3_stmt *stmt){
	int result,size=0;
		char existeUsuario[]="SELECT * FROM usuario";
		sqlite3_prepare_v2(db, existeUsuario, -1, &stmt, NULL);
		sqlite3_bind_text(stmt,1,nombre,-1,SQLITE_STATIC);
		result=sqlite3_step(stmt);
		while (result == SQLITE_ROW){
			if(strcmp(nombre,sqlite3_column_text(stmt,1))==0){
				size++;
			}
			result = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		return size;
}








