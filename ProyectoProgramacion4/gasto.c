#include "gasto.h"
#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "sqlite3.h"

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
       scanf("%d", &nuevoGasto.fecha.dia);
     printf("Ingrese el mes: ");
           fflush(stdout);
           scanf("%d", &nuevoGasto.fecha.mes);
     printf("Ingrese el año: ");
        fflush(stdout);
        scanf("%d", &nuevoGasto.fecha.anyo);
        fflush(stdin);
     if(1<=nuevoGasto.fecha.dia&&nuevoGasto.fecha.dia<=31&&1<=nuevoGasto.fecha.mes&&nuevoGasto.fecha.mes<=12&&1<=nuevoGasto.fecha.anyo){
        sprintf(stringFecha,"%d/%d/%d",nuevoGasto.fecha.dia,nuevoGasto.fecha.mes,nuevoGasto.fecha.anyo);
        fflush(stdout);
    printf("Escribe el concepto:");
         fflush(stdout);
         scanf("%s", nuevoGasto.concepto);
    printf("Escribe el coste: ");
             fflush(stdout);
             scanf("%lf", &nuevoGasto.coste);
    if(&nuevoGasto.coste<0){
    imprimirCategoria(IdUsuario,db,stmt);
    printf("Escribe la categoría: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", nuevoGasto.categoria);

    strcpy(categoria.nombreCategoria,&nuevoGasto.categoria);

    if(buscarIDCategoria(categoria,db,stmt)>1){
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
