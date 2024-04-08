#include "gasto.h"
#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "sqlite3.h"
#include <stdlib.h>

//función para pedir al usuario que ingrese una fecha en el formato "dd/mm/aa"


void crearGasto(int IdUsuario,sqlite3 *db,sqlite3_stmt *stmt) {
    Gasto nuevoGasto;
    Categoria categoria;
    char stringFecha[100];
    //utiliza el id de usuario del usuario que ha iniciado sesión
    nuevoGasto.idUsuario=IdUsuario;

    //se le pide al usuario que ingrese la fecha
    printf("Ingrese el día: ");
       	fflush(stdout);
       	fflush(stdin);
        scanf("%d", &nuevoGasto.fecha.dia);
     printf("Ingrese el mes: ");
        fflush(stdout);
        fflush(stdin);
        scanf("%d", &nuevoGasto.fecha.mes);
     printf("Ingrese el año: ");
        fflush(stdout);
        fflush(stdin);
        scanf("%d", &nuevoGasto.fecha.anyo);
     if(1<=nuevoGasto.fecha.dia&&nuevoGasto.fecha.dia<=31&&1<=nuevoGasto.fecha.mes&&nuevoGasto.fecha.mes<=12&&1<=nuevoGasto.fecha.anyo){
        sprintf(stringFecha,"%d/%d/%d",nuevoGasto.fecha.dia,nuevoGasto.fecha.mes,nuevoGasto.fecha.anyo);
        fflush(stdin);
    printf("Escribe el concepto: ");
        fflush(stdout);
        scanf("%s", nuevoGasto.concepto);
    printf("Escribe el coste:");
        fflush(stdout);
        fflush(stdin);
        scanf("%lf", &nuevoGasto.coste);
    if(nuevoGasto.coste>0){
    imprimirCategoria(IdUsuario,db,stmt);
    printf("Escribe la categoría: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", nuevoGasto.categoria);

    strcpy(categoria.nombreCategoria,&nuevoGasto.categoria);

    if(buscarIDCategoria(categoria,db,stmt)>=1){
    char insertarGasto[] = "INSERT INTO Gastos(id_u_c,fecha,concepto,coste,categoria) VALUES(?,?,?,?,?)";
        sqlite3_prepare_v2(db, insertarGasto, sizeof(insertarGasto) + 1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, IdUsuario);
        sqlite3_bind_text(stmt, 2, stringFecha, sizeof(stringFecha), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, nuevoGasto.concepto, -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt,4,nuevoGasto.coste);
        sqlite3_bind_text(stmt, 5, nuevoGasto.categoria, -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

   printf("Gasto creado exitosamente!\n");fflush(stdout);
    }
    else{
    	printf("Esta categoria no existe!\n");fflush(stdout);
    }
     }
     else{
    	 printf("Ingrese un coste mayor que 0!\n");fflush(stdout);
     }
     }
     else{
    	 printf("Ingrese una fecha valida!\n");fflush(stdout);
     }

}
int *cargarGastosUsuario(int IdUsuario,sqlite3 *db,sqlite3_stmt *stmt){
	int result,tam=0,i=0;
	char seleccionarTodo[] = "SELECT * FROM Gastos";
	sqlite3_prepare_v2(db, seleccionarTodo, sizeof(seleccionarTodo) + 1, &stmt, NULL);
	result=sqlite3_step(stmt);
	while(result==SQLITE_ROW){
		if(IdUsuario==sqlite3_column_int(stmt,1)){
			tam++;
		}
		result=sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	int *arr;
	arr=malloc(tam*sizeof(int));
	result=sqlite3_prepare_v2(db, seleccionarTodo, sizeof(seleccionarTodo) + 1, &stmt, NULL);
	result=sqlite3_step(stmt);
	while(result==SQLITE_ROW){
		if(IdUsuario==sqlite3_column_int(stmt,1)){
			arr[i]=sqlite3_column_int(stmt,0);
			i++;
		}
		result=sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	return arr;
}
void imprimirListaGastos(int IdUsuario,sqlite3 *db,sqlite3_stmt *stmt){
	int result,i=1;
	char seleccionarTodo[] = "SELECT * FROM Gastos";
	sqlite3_prepare_v2(db, seleccionarTodo, sizeof(seleccionarTodo) + 1, &stmt, NULL);
	result=sqlite3_step(stmt);
	while(result==SQLITE_ROW){
			if(IdUsuario==sqlite3_column_int(stmt,1)){
				printf("%i. %s, %s, %lf€, %s\n",i,sqlite3_column_text(stmt,2),sqlite3_column_text(stmt,3),sqlite3_column_double(stmt,4)
						,sqlite3_column_text(stmt,5));fflush(stdout);
				i++;
			}
			result=sqlite3_step(stmt);
	}
}

void eliminarGasto(int array[],sqlite3 *db,sqlite3_stmt *stmt){
	int numeroGas;

	printf("Introduce el numero de el gasto que quieres borrar: "); fflush(stdout); fflush(stdin);
	scanf("%d",&numeroGas);

	char eliminarGas[] = "DELETE FROM Gastos WHERE codigo = ?";
	sqlite3_prepare_v2(db, eliminarGas, sizeof(eliminarGas) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, array[numeroGas-1]);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}
void eliminarGastoCategoria(int idU,Categoria cat,sqlite3 *db,sqlite3_stmt *stmt){
	char eliminarGastoCategoria[] = "DELETE FROM Gastos WHERE categoria=? AND id_u_c=?";
	sqlite3_prepare_v2(db, eliminarGastoCategoria, sizeof(eliminarGastoCategoria) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, cat.nombreCategoria, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, idU);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}
void modificarGastoCategoria(int idU,Categoria cat,Categoria cat2,sqlite3 *db,sqlite3_stmt *stmt){
	char modificarGastosMul[] = "UPDATE gastos SET categoria=? WHERE categoria=? AND id_u_c =?";
	sqlite3_prepare_v2(db, modificarGastosMul, sizeof(modificarGastosMul) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, cat2.nombreCategoria, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, cat.nombreCategoria, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt,3, idU);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}
