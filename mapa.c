#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "mapa.h"

/** https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
 * Reciclado un poco del get_csv_field (o la logica mas que nada de las posiciones de la "," en este caso, son " ") **/
char * txt (char * temp, int pos )
{
    char s[2] = " ";
    char * token = (char *) malloc (20 * sizeof(char));
    char * auxTemp = strdup(temp);
    int i = 0;

    token = strtok(auxTemp, s);
    while (token != NULL && i < pos)
    {
        token = strtok(NULL, s);
        i++;
    }
    return token;
}


void importarArchivo (HashMap * direcciones) {
    //char nombreArchivo[50];

    //printf ("Ingrese el nombre del archivo: ");
    FILE * archivo;

    do {
        fflush(stdin);
        //gets(nombreArchivo);

        archivo = fopen("tarea3_tsp.txt","r");  //Arreglar para que lea archivo con nombre ingresado por el usuario
        if (archivo == NULL) {
            printf ("Hubo un problema con el archivo, intente importarlo nuevamente o intente importar un archivo diferente");
        }
    }
    while (archivo == NULL);

    char * linea = (char*)malloc(1024*sizeof(char));
    char * x, *y;
    int id = 0;

    //linea = fgets(linea, 1024, archivo);
    Direccion * newAdress;

    while(fgets(linea, 1023, archivo) != NULL)
    {
       newAdress = (Direccion *)malloc(sizeof(Direccion));

        x = txt(linea, 0);
        y = txt(linea, 1);

        /** newAdress->cordX = atoi(x);
        newAdress->cordY = atoi(y);
        newAdress->identificador = id; **/
        
        agregarMapa(direcciones, x, y, id);
        id++;

        printf ("X: %d - Y: %d - ID: %d\n",newAdress->cordX,newAdress->cordY, newAdress->identificador );
    }
}


void agregarMapa(HashMap * direcciones,char * x, char * y,int id) {
    Direccion * entrega;
    if (searchMap(direcciones, id) == NULL)
    {
        entrega = crearDireccion(id);
        entrega->cordX = atoi(x);
        entrega->cordY = atoi(y);
        insertMap(direcciones, id, entrega);
    }
}

Direccion * crearDireccion (int id) 
{
    Direccion * newAdress = (Direccion *) malloc (sizeof(Direccion));
    newAdress->identificador = id;
    newAdress->distancia = createMap(100);
    return newAdress;
}