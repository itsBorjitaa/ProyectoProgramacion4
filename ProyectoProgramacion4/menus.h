#ifndef MENUS_H_
#define MENUS_H_

#include "sqlite3.h"
char menuLogin();
char menuPrincipal(int idU,sqlite3 *db,sqlite3_stmt *stmt);
char menuGastos();
char menuCategorias();
char menuSaldo();

#endif /* MENUS_H_ */
