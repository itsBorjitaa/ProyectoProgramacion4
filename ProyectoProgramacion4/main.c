#include "menus.h"
#include "listaUsuarios.h"
#include <stdio.h>
#include <time.h>
#include "gasto.h"
#include "sqlite3.h"
#include "categoria.h"
#include "usuario.h"
#define NOMFICH "usuarios.txt"
#define LOGFILE "log.log"
#define DB_FILE "db.db"

void escribirLog(const char *log) {
    FILE *logFile = fopen(LOGFILE, "a");
    if (logFile != NULL) {
        time_t tiempo;
        struct tm *infoTiempo;
        time(&tiempo);
        infoTiempo = localtime(&tiempo);

        char marcaTiempo[20];
        if (strftime(marcaTiempo, sizeof(marcaTiempo), "%Y-%m-%d %H:%M:%S", infoTiempo) > 0) {
            fprintf(logFile, "[%s] %s\n", marcaTiempo, log);
            fclose(logFile);
        } else {
            printf("Error al formatear la marca de tiempo.\n");
            fclose(logFile);
        }
    } else {
        printf("Error al abrir el fichero de log.\n");
    }
}

void InicializarBD(sqlite3 *db,sqlite3_stmt *stmt){
	//Crear tablas si no existen:

	//Tabla Usuarios
	char crearUsuario[] ="CREATE TABLE IF NOT EXISTS Usuario (id_u INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,usuarioNombre STRING NOT NULL,"
			"contrasenya STRING NOT NULL)";//Statement crear usuario
	sqlite3_prepare_v2(db, crearUsuario, sizeof(crearUsuario) + 1, &stmt, NULL);//Cargamos el stmt
	sqlite3_step(stmt);//Ejecutamos el statement

	//Tabla Gastos
	char crearGasto[]="CREATE TABLE IF NOT EXISTS Gastos "
			"(codigo INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, id_u_c INTEGER NOT NULL, "
			"fecha TEXT NOT NULL, concepto TEXT NOT NULL, "
			"coste REAL NOT NULL, categoria STRING NOT NULL, "
			"FOREIGN KEY(id_u_c) REFERENCES Usuario(id_u) ON DELETE CASCADE)";
	sqlite3_prepare_v2(db, crearGasto, sizeof(crearGasto) + 1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Tabla Categorias
	char crearCategoria[]="CREATE TABLE IF NOT EXISTS Categorias (id_c INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
			"categoria STRING UNIQUE NOT NULL)";
	sqlite3_prepare_v2(db, crearCategoria, sizeof(crearCategoria) + 1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Tabla CategoriasUsuario
	char crearCategoriasUsuario[]="CREATE TABLE IF NOT EXISTS categoriasUsuario (id_u_cu INTEGER NOT NULL, "
			"id_c_cu INTEGER NOT NULL,PRIMARY KEY(id_u_cu, id_c_cu), "
			"FOREIGN KEY(id_u_cu) REFERENCES Usuario(id_u) "
			"ON DELETE CASCADE, FOREIGN KEY(id_c_cu) REFERENCES  Categorias(id_c) ON DELETE CASCADE)";
	sqlite3_prepare_v2(db, crearCategoriasUsuario, sizeof(crearCategoriasUsuario) + 1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	char crearSaldo[]="CREATE TABLE IF NOT EXISTS Saldos (id_u_s INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
				"saldo REAL NOT NULL, "
				"FOREIGN KEY(id_u_s) REFERENCES Usuario(id_u) "
				"ON DELETE CASCADE)";
		sqlite3_prepare_v2(db, crearSaldo, sizeof(crearSaldo) + 1, &stmt, NULL);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
}

int main(){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	Usuario *u;
	int temp,idActual;
	char opcion,opcionU;

	sqlite3_open(DB_FILE, &db);
	InicializarBD(db,stmt);

	do{
		opcion = menuLogin();
		switch(opcion){
			case '0':
				printf("Saliendo de la aplicación...\n");
				fflush(stdout);
				escribirLog("Saliendo de la aplicación");
				break;
			case '1':
				idActual=iniciarSesionBD(u,db,stmt);
				if(idActual>0){
					printf("Bienvenido, %s!\n", u->nombre); fflush(stdout);escribirLog("Sesión iniciada");fflush(stdout);
					int *arrayCodigosGastos=cargarGastosUsuario(idActual,db,stmt);
						do{
							opcionU = menuPrincipal();
							switch(opcionU){
								case '0':
									printf("Cerrando sesión...\n");
									sqlite3_close(db);
									fflush(stdout);
									escribirLog("Cerrando sesión");
									break;
								case '1':
									do{
										opcion = menuGastos();
										switch(opcion){
											case '0':
												printf("Volviendo atrás...\n");
												fflush(stdout);
												break;
											case '1':
												printf("AÑADIR GASTO:\n");
												crearGasto(idActual,db,stmt);
												arrayCodigosGastos=cargarGastosUsuario(idActual,db,stmt);
												fflush(stdout);
												break;
										    case '2':
										    	printf("MODIFICAR GASTO:\n");
										    	arrayCodigosGastos=cargarGastosUsuario(idActual,db,stmt);
										    	imprimirListaGastos(idActual,db,stmt);
										    	modificarGasto(arrayCodigosGastos, idActual, db, stmt);
										    	fflush(stdout);
										    	break;
										    case '3':
										    	printf("ELIMINAR GASTO:\n");
										    	arrayCodigosGastos=cargarGastosUsuario(idActual,db,stmt);
										    	imprimirListaGastos(idActual,db,stmt);
										    	fflush(stdout);
										    	eliminarGasto(arrayCodigosGastos,db,stmt);
										    	break;
										    case '4':
										    	printf("VER GASTOS DEL USUARIO:\n");
										    	imprimirListaGastos(idActual,db,stmt);
										    	fflush(stdout);
										    	break;
										    default:
										    	printf("ERROR! La opción seleccionada no es correcta\n");
										    	fflush(stdout);
										    	escribirLog("ERROR! La opción seleccionada no es correcta");
										}
									}while(opcion!='0');
									break;
								case '2':
									do{
										opcion = menuCategorias();
										switch(opcion){
											case '0':
												printf("Volviendo atrás...\n");
												fflush(stdout);
												break;
										    case '1':
										    	printf("AÑADIR CATEGORÍA:\n");
										    	fflush(stdout);
										    	crearCategoria(idActual,db,stmt);
										    	break;
										    case '2':
										    	printf("MODIFICAR CATEGORÍA:\n");
										    	fflush(stdout);
										    	modificarCategoria(idActual,db,stmt);
										    	break;
										    case '3':
										    	printf("ELIMINAR CATEGORÍA:\n");
										    	fflush(stdout);
										    	eliminarCategoria(idActual, db, stmt);
										    	break;
										    case '4':
										    	printf("VER CATEGORÍAS DEL USUARIO:\n");
										    	imprimirCategoria(idActual,db,stmt);
										    	fflush(stdout);
										    	break;
										    default:
										    	printf("ERROR! La opción seleccionada no es correcta\n");
										    	fflush(stdout);
										    	escribirLog("ERROR! La opción seleccionada no es correcta");
										}
									}while(opcion!='0');
									break;
								case '3':
									do{
										opcion = menuSaldo();
										switch(opcion){
											case '0':
												printf("Volviendo atrás...\n");
												fflush(stdout);
												break;
										    case '1':
										    	printf("MODIFICAR SALDO:\n");
										    	fflush(stdout);
										    	break;
										    default:
										    	printf("ERROR! La opción seleccionada no es correcta\n");
										    	fflush(stdout);
										    	escribirLog("ERROR! La opción seleccionada no es correcta");
										}
									}while(opcion!='0');
									break;
								default:
									printf("ERROR! La opción seleccionada no es correcta\n");
									fflush(stdout);
									escribirLog("ERROR! La opción seleccionada no es correcta");
							}
						}while(opcionU != '0');
					}else{
						printf("ERROR! La contraseña no es correcta\n");
						fflush(stdout);
						escribirLog("ERROR! La contraseña no es correcta");
					}
				break;
			case '2':
				insertarUsuarioBD(db,stmt);
		}
	}while(opcion!='0');
}
