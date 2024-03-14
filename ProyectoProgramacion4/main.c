#include "menus.h"
#include "listaUsuarios.h"
#include <stdio.h>

#define NOMFICH "Usuarios.txt"
int main(){
	ListaUsuarios lu;
	Usuario u;
	int pos;
	char opcion,opcionU;

	volcarFicheroAListaUsuarios(&lu, NOMFICH);
	do{
		opcion = menuLogin();
		switch(opcion){
			case '0': printf("Saliendo de la aplicación...\n");fflush(stdout);break;
			case '1': u = pedirUsuario();
					  pos = buscarUsuario(lu, u.nombre);
					  if(pos==-1){
						  printf("Lo sentimos! No estás registrado\n");
					  }else{
						  if(contrasenyaCorrecta(lu.aUsuarios[pos].contrasenya, u.contrasenya)){
							  printf("Bienvenido!\n"); fflush(stdout);
							  do{
								  opcionU = menuPrincipal();
								  switch(opcionU){
									  case '0': printf("Volviendo atrás...\n"); fflush(stdout);
										  break;
									  case '1': break;
									  case '2': break;
									  case '3': break;
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
