#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "entregas.h"

typedef struct direccion {
    int cordX;   //Posciciones x e y de la direccion
    int cordY;
    int identificador;  //"Numero" de la direccion segun el archivo .txt
    int visitada;
} Direccion;

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
    Direccion * entrega = (Direccion *)malloc(sizeof(Direccion));
    entrega->cordX = atoi(x);
    entrega->cordY = atoi(y);
    entrega->identificador = id;
    char auxId[5];
    sprintf(auxId,"%d",id);
    entrega->visitada = 0;
    insertMap(direcciones, auxId, entrega);
    
}
