/*
 * saldo.c
 *
 *  Created on: 8 abr 2024
 *      Author: Sergio
 */

#include "saldo.h"
#include "sqlite3.h"
#include <string.h>
#include <stdio.h>
void crearSaldo(int idU,sqlite3 *db,sqlite3_stmt *stmt){
	char crearSaldo[]="INSERT INTO Saldos(id_u_s,saldo) VALUES(?,0)";
	sqlite3_prepare_v2(db, crearSaldo, sizeof(crearSaldo) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt,1,idU);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}
void mostrarSaldo(int idU,sqlite3 *db,sqlite3_stmt *stmt){
	int result;
	char mostrarSaldo[]="SELECT * FROM Saldos";
	sqlite3_prepare_v2(db,mostrarSaldo, sizeof(mostrarSaldo)+1, &stmt, NULL);
	result=sqlite3_step(stmt);
	while(result==SQLITE_ROW){
		if(idU==sqlite3_column_int(stmt,0)){
			printf("Saldo: %lf€\n",sqlite3_column_double(stmt,1));fflush(stdout);
			printf("Hola");fflush(stdout);
		}
		result=sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
}
void modificarSaldo(int idU,sqlite3 *db,sqlite3_stmt *stmt){
	mostrarSaldo(idU,db,stmt);
	char modificarSaldo[]="UPDATE Saldos SET saldo=? WHERE id_u_s=?";
	sqlite3_prepare_v2(db,modificarSaldo, sizeof(modificarSaldo)+1, &stmt, NULL);
}
