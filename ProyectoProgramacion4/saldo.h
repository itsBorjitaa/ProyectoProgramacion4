/*
 * saldo.h
 *
 *  Created on: 8 abr 2024
 *      Author: Sergio
 */
#include "sqlite3.h"
#ifndef SALDO_H_
#define SALDO_H_

void mostrarSaldo(int idU,sqlite3 *db,sqlite3_stmt *stmt);
void crearSaldo(int idU,sqlite3 *db,sqlite3_stmt *stmt);
void modificarSaldo(int idU,sqlite3 *db,sqlite3_stmt *stmt);
void restarSaldo(double coste,int idU,sqlite3 *db,sqlite3_stmt *stmt);

#endif /* SALDO_H_ */
