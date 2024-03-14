#include "listaUsuarios.h"
#include <stdio.h>
#include <string.h>
void volcarFicheroAListaUsuarios(ListaUsuarios *lu, char *nomfich){
	FILE *pf;
	Usuario u;
	pf = fopen(nomfich,"r");
	if(pf!=(FILE*)NULL){
		fscanf(pf,"%d",&lu->tam);
		lu->aUsuarios = (Usuario*)malloc(lu->tam * sizeof(Usuario));
		lu->numU = 0;
		while(fscanf(pf,"%s %s",u.nombre,u.contrasenya) != EOF){
			lu->aUsuarios[lu->numU] = u;
			lu->numU++;
		}
		fclose(pf);
	}
}

int buscarUsuario(ListaUsuarios lu, char *nom){
	int pos=0,enc=0;
	while(!enc && pos<lu.numU){
		if(strcmp(lu.aUsuarios[pos].nombre,nom)==0){
			enc = 1;
		}else{
			pos++;
		}
	}
	if(enc){
		return pos;
	}else{
		return -1;
	}
}

void anyadirUsuario(ListaUsuarios *lu, Usuario u){
	if(lu->numU < lu->tam){
		lu->aUsuarios[lu->numU] = u;
		lu->numU++;
		printf("Usuario añadido correctamente\n");
	}else{
		printf("Lo sentimos! La lista está completa\n");
	}
	fflush(stdout);
}

void volcarListaUsuariosAFichero(ListaUsuarios lu, char *nomfich){
	FILE *pf;
	int i;
	pf = fopen(nomfich,"w");
	if(pf != (FILE*)NULL){
		fprintf(pf,"%d\n",lu.tam);
		for(i=0;i<lu.numU;i++){
			fprintf(pf,"%s %s\n",lu.aUsuarios[i].nombre,lu.aUsuarios[i].contrasenya);
		}
		fclose(pf);
	}
}








