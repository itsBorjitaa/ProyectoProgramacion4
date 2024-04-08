#ifndef PROPERTIES_H
#define PROPERTIES_H

typedef struct {
    char app_nombre[100];
    char app_version[10];
    char ultima_actualizacion[20];
    char db_file[100];
    char logfile[100];
} Properties;

Properties leerPropiedades(const char *filename);

#endif /* PROPERTIES_H */
