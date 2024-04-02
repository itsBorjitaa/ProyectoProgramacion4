#include "menus.h"
#include "listaUsuarios.h"
#include <stdio.h>
#include <time.h>
#include "gasto.h"
#include "sqlite3.h"

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
	sqlite3_open(DB_FILE, &db);

	//Crear tablas si no existen:

	//Tabla Usuarios
	char crearUsuario[] ="CREATE TABLE IF NOT EXISTS Usuario (usuario VARCHAR(255) NOT NULL,"
			"contrasenya VARCHAR(255) NOT NULL,PRIMARY KEY(usuario))";//Statement crear usuario
	sqlite3_prepare_v2(db, crearUsuario, strlen(crearUsuario) + 1, &stmt, NULL);//Cargamos el stmt
	sqlite3_step(stmt);//Ejecutamos el statement

	//Tabla Gastos
	char crearGasto[]="CREATE TABLE IF NOT EXISTS Gastos "
			"(codigo INTEGER NOT NULL DEFAULT 0, usuarioF TEXT NOT NULL, "
			"fecha TEXT NOT NULL, concepto TEXT NOT NULL, "
			"coste REAL NOT NULL, categoria TEXT NOT NULL,PRIMARY KEY(codigo), "
			"FOREIGN KEY(usuarioF) REFERENCES Usuario(usuario) ON DELETE CASCADE)";
	sqlite3_prepare_v2(db, crearGasto, strlen(crearGasto) + 1, &stmt, NULL);
	sqlite3_step(stmt);

	//Tabla Categorias
	char crearCategoria[]="CREATE TABLE IF NOT EXISTS Categorias (id_c INTEGER NOT NULL, "
			"categoria STRING NOT NULL, PRIMARY KEY(id_c))";
	sqlite3_prepare_v2(db, crearCategoria, strlen(crearCategoria) + 1, &stmt, NULL);
	sqlite3_step(stmt);

	//Tabla CategoriasUsuario
	char crearCategoriasUsuario[]="CREATE TABLE IF NOT EXISTS categoriasUsuario (usuario_cu String NOT NULL, "
			"id_c_cu INTEGER NOT NULL,PRIMARY KEY(usuario_cu, id_c_cu), "
			"FOREIGN KEY(usuario_cu) REFERENCES Usuario(usuario) "
			"ON DELETE CASCADE, FOREIGN KEY(id_c_cu) REFERENCES  Categorias(id_c) ON DELETE CASCADE)";
	sqlite3_prepare_v2(db, crearCategoriasUsuario, strlen(crearCategoriasUsuario) + 1, &stmt, NULL);
	sqlite3_step(stmt);
}

int main(){
	sqlite3 *db;//
	sqlite3_stmt *stmt;
	ListaUsuarios lu;
	Usuario u;
	int pos;
	char opcion,opcionU;
	InicializarBD(db,stmt);
	volcarFicheroAListaUsuarios(&lu, NOMFICH);

	escribirLog("Prueba de inicio");

	do{
		opcion = menuLogin();
		switch(opcion){
			case '0': printf("Saliendo de la aplicación...\n"); fflush(stdout);break;
			case '1': u = pedirUsuario();
					  pos = buscarUsuario(lu, u.nombre);
					  if(pos==-1){
						  printf("Lo sentimos! No estás registrado\n");
					  }else{
						  if(contrasenyaCorrecta(lu.aUsuarios[pos].contrasenya, u.contrasenya)){
							  printf("Bienvenido, %s!\n", u.nombre); fflush(stdout);
							  do{
								  opcionU = menuPrincipal();
								  switch(opcionU){
									  case '0': printf("Cerrando sesión...\n"); fflush(stdout);
										  break;
									  case '1':
										  do{
											  opcion = menuGastos();
											  switch(opcion){
											  case '0': printf("Volviendo atrás...\n"); fflush(stdout);break;
											  case '1': printf("AÑADIR GASTO:\n"); fflush(stdout);break;
											  case '2': printf("MODIFICAR GASTO:\n"); fflush(stdout);break;
											  case '3': printf("ELIMINAR GASTO:\n"); fflush(stdout);break;
											  case '4': printf("VER GASTOS DEL USUARIO:\n"); fflush(stdout);break;
											  default: printf("ERROR! La opción seleccionada no es correcta\n");fflush(stdout);
											  }
										  }while(opcion!='0'); break;
									  case '2':
										  do{
											  opcion = menuCategorias();
											  switch(opcion){
											  case '0': printf("Volviendo atrás...\n"); fflush(stdout);break;
											  case '1': printf("AÑADIR CATEGORÍA:\n"); fflush(stdout);break;
											  case '2': printf("MODIFICAR CATEGORÍA:\n"); fflush(stdout);break;
											  case '3': printf("ELIMINAR CATEGORÍA:\n"); fflush(stdout);break;
											  case '4': printf("VER CATEGORÍAS DEL USUARIO:\n"); fflush(stdout);break;
											  default: printf("ERROR! La opción seleccionada no es correcta\n");fflush(stdout);
											  }
										  }while(opcion!='0'); break;
									  case '3':
										  do{
											  opcion = menuSaldo();
											  switch(opcion){
											  case '0': printf("Volviendo atrás...\n"); fflush(stdout);break;
											  case '1': printf("MODIFICAR SALDO:\n"); fflush(stdout);break;
											  default: printf("ERROR! La opción seleccionada no es correcta\n");fflush(stdout);
											  }
										  }while(opcion!='0'); break;
									  default: printf("ERROR! La opción seleccionada no es correcta\n");fflush(stdout);
								  }
							  }while(opcionU != '0');
						  }else{
							  printf("Lo sentimos! La contraseña no es correcta\n");fflush(stdout);
						  }
					  }
				break;
			case '2': u = pedirUsuario();
					  pos = buscarUsuario(lu, u.nombre);
					  if(pos!=-1){
						  printf("Lo sentimos! Ese nombre de usuario ya existe\n");
					  }else{
						  anyadirUsuario(&lu, u);
					  }
				break;
			default: printf("ERROR! La opción seleccionada no es correcta\n");fflush(stdout);
		}
	}while(opcion!='0');
	volcarListaUsuariosAFichero(lu, NOMFICH);
	free(lu.aUsuarios);
}
