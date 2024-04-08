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
		}
		result=sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
}
void modificarSaldo(int idU,sqlite3 *db,sqlite3_stmt *stmt){
	double nuevoSaldo;
	mostrarSaldo(idU,db,stmt);
	printf("Nuevo saldo?");
	fflush(stdout);
	fflush(stdin);
	scanf("%lf",&nuevoSaldo);
	char modificarSaldo[]="UPDATE Saldos SET saldo=? WHERE id_u_s=?";
	sqlite3_prepare_v2(db,modificarSaldo, sizeof(modificarSaldo)+1, &stmt, NULL);
	sqlite3_bind_double(stmt,1,nuevoSaldo);
	sqlite3_bind_int(stmt,2,idU);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	printf("Saldo modificado correctamente!\n");fflush(stdout);
	escribirLog("Saldo modificado correctamente!");
}
void restarSaldo(double coste,int idU,sqlite3 *db,sqlite3_stmt *stmt){
		char restarSaldo[]="UPDATE Saldos SET saldo=saldo-? WHERE id_u_s=?";
		sqlite3_prepare_v2(db,restarSaldo, sizeof(restarSaldo)+1, &stmt, NULL);
		sqlite3_bind_double(stmt,1,coste);
		sqlite3_bind_int(stmt,2,idU);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
}
