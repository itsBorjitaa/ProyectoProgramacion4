#include "properties.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Properties leerPropiedades(const char *filename) {
    Properties prop;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de propiedades.\n");
        exit(1);
    }
    char linea[100];
    while (fgets(linea, sizeof(linea), file)) {
        char *clave = strtok(linea, "=");
        char *valor = strtok(NULL, "=");
        if (clave != NULL && valor != NULL) {
            if (strcmp(clave, "APP_NOMBRE") == 0) {
                strcpy(prop.app_nombre, valor);
            } else if (strcmp(clave, "APP_VERSION") == 0) {
                strcpy(prop.app_version, valor);
            } else if (strcmp(clave, "ULTIMA_ACTUALIZACION") == 0) {
                strcpy(prop.ultima_actualizacion, valor);
            } else if (strcmp(clave, "DB_FILE") == 0) {
                strcpy(prop.db_file, valor);
            } else if (strcmp(clave, "LOGFILE") == 0) {
                strcpy(prop.logfile, valor);
            }
        }
    }
    fclose(file);
    return prop;
}
