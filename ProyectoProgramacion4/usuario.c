#include "usuario.h"
#include <string.h>
#include <stdio.h>

Usuario pedirUsuario(){
	Usuario u;

	printf("Introduce tu nombre: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.nombre);

	printf("Introduce tu contraseña: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.contrasenya);
	return u;
}

int contrasenyaCorrecta(char *conU,char *con){
	int correcta = 0;
	if(strcmp(conU, con)==0){
		correcta = 1;
	}
	return correcta;
}










