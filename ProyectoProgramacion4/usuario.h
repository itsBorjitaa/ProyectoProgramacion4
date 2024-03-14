#ifndef USUARIO_H_
#define USUARIO_H_

typedef struct usuario{
	char nombre[20];
	char contrasenya[20];
}Usuario;

Usuario pedirUsuario();
int contrasenyaCorrecta(char *conU, char *con);

#endif /* USUARIO_H_ */
