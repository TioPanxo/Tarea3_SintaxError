#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashmap.h"
#include "list.h"
#include "entregas.h"


typedef struct Direccion {
    int cordX;   //Posciciones x e y de la direccion
    int cordY;
    int identificador;  //"Numero" de la direccion segun el archivo .txt
    int visitada;       //const value 0
    double distancia; //Distancia hcaia la siguiente Direccion /const value 0
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
    FILE * archivo;
    char nombreArchivo[50];
    int cantidadDirecciones;

    printf(" Ingrese el nombre del archivo: ");
    gets(nombreArchivo);
    archivo = fopen(nombreArchivo,"r");
    if(archivo == NULL){
        printf(" El archivo no existe\n");
        return;
    }

    printf(" Ingrese la cantidad de direcciones que desea importar: ");
    scanf("%d", &cantidadDirecciones);

    char * linea = (char*)malloc(1024*sizeof(char));
    char * x, *y;
    int id = 1;

    Direccion * newAdress;

    int aux = 0;

    while(fgets(linea, 1023, archivo) != NULL && cantidadDirecciones > aux)
    {
       newAdress = (Direccion *)malloc(sizeof(Direccion));

        x = txt(linea, 0);
        y = txt(linea, 1);

        //newAdress->cordX = atoi(x);
        //newAdress->cordY = atoi(y);
        //newAdress->identificador = id;
        
        agregarMapa(direcciones, x, y, id);
        id++;

        //printf ("X: %d - Y: %d - ID: %d\n",newAdress->cordX,newAdress->cordY, newAdress->identificador );
        aux ++;
    }
    printf(" Archivo importado correctamente\n");
}


void agregarMapa(HashMap * direcciones,char * x, char * y,int id) {
    Direccion * entrega = (Direccion *)malloc(sizeof(Direccion));
    entrega->cordX = atoi(x);
    entrega->cordY = atoi(y);
    entrega->identificador = id;
    char * auxId = (char *)malloc(sizeof(char) * 5);
    sprintf(auxId,"%d",id);
    entrega->visitada = 0;
    insertMap(direcciones, auxId, entrega);
    
}

void bubbleSortId(Direccion ** array,int largo){
    int i,j;
    Direccion * aux;


    for(i = 0;i < largo - 1;i++){
        for(j = 0;j < largo - i - 1;j++){
            if(array[j]->identificador > array[j+1]->identificador){
                aux = array[j+1];
                array[j+1] = array[j];
                array[j] = aux;
            }
        }
    }
}

void mostrarDireccionesPorId(HashMap * direcciones){
    List * list = createList();

    Direccion * aux = firstMap(direcciones);
    Direccion * node;
    while(aux != NULL){
        node = copy(aux);
        pushBack(list,node);
        aux = nextMap(direcciones);
    }

    Direccion ** auxList = (Direccion**) malloc(sizeof(Direccion * )*get_size(list));

    int largo = get_size(list);

    node = first(list);
    for(int i = 0;node != NULL;i++){
        auxList[i] = node;
        node = next(list);
    }

    bubbleSortId(auxList,largo);

    for(int i = 0;i < largo;i++){
        printf(" ID: %d - Cordenada X: %d - Cordenada Y: %d\n",auxList[i]->identificador,auxList[i]->cordX,auxList[i]->cordY);
    }
    free(list);
}

double calcularDistancia(Direccion * aux1,Direccion * aux2){
    double dist;
    dist = pow(aux2->cordX - aux1->cordX,2.0) + pow(aux2->cordY - aux1->cordY,2.0);
    dist = sqrt(dist);
    return dist;
}

void distancia2Entregas(HashMap * direcciones){
    char entrada1[50];
    char entrada2[50];
    printf(" Que entregas desea calcular?(ingrese id de las entregas)\n");
    mostrarDireccionesPorId(direcciones);

    printf(" Entrega 1: ");
    scanf("%s",&entrada1);
    Direccion * aux1 = searchMap(direcciones,entrada1);
    if(aux1 == NULL){
        printf(" Id no valida, por favor ingrese una id de la lista");
        scanf("%s",&entrada1);
        Direccion * aux1 = searchMap(direcciones,entrada1);
    }

    printf(" Entrega 2: ");
    scanf("%s",&entrada2);
    Direccion * aux2 = searchMap(direcciones,entrada2);
    if(aux2 == NULL){
        printf(" Id no valida, por favor ingrese una id de la lista");
        scanf("%s",&entrada2);
        Direccion * aux2 = searchMap(direcciones,entrada2);
    }

    double distancia = calcularDistancia(aux1,aux2);
    printf(" La distancia entre las entregas %s - %s es %.2lf\n",entrada1,entrada2,distancia);
}



void bubbleSortDistancia(Direccion ** Array,int largo){
    int i,j;
    Direccion * aux;


    for(i = 0;i < largo - 1;i++){
        for(j = 0;j < largo - i - 1;j++){
            if(Array[j]->distancia > Array[j+1]->distancia){
                aux = Array[j+1];
                Array[j+1] = Array[j];
                Array[j] = aux;
            }
        }
    }
}

void mostrar3EntregasCercanas(HashMap * direcciones){
    int cordX;
    int cordY;
    printf(" Ingrese sus cordenadas actuales:\n");
    printf(" Coordenada X: ");
    scanf("%d",&cordX);
    printf(" Coordenada Y: ");
    scanf("%d",&cordY);

    Direccion * aux = (Direccion *)malloc(sizeof(Direccion));
    aux->cordX = cordX;
    aux->cordY = cordY; 

    List * list = get_adj_nodes(direcciones,aux);

    Direccion ** auxList = (Direccion**) malloc(sizeof(Direccion * )*get_size(list));

    int largo = get_size(list);

    Direccion * node = first(list);
    for(int i = 0;node != NULL;i++){
        auxList[i] = node;
        node = next(list);
    }

    bubbleSortDistancia(auxList,largo);
    printf(" 3 Entregas mas cercanas a tu Direccion:\n");
    for(int j = 0;j < 3;j++){
        printf(" X: %d - Y: %d - Distancia: %.2lf\n",auxList[j]->cordX,auxList[j]->cordY,auxList[j]->distancia);
        
    }
}



Direccion* copy(Direccion* n){
    Direccion* new=(Direccion*) malloc(sizeof(Direccion));
    *new = *n;
    return new;
}

void * get_adj_nodes(HashMap * direcciones,Direccion * n){
    List * list = createList();
    
    //recorre el mapa
    Direccion * aux = firstMap(direcciones);

    //copia que se almacena en la lista
    Direccion * node;

    while(aux != NULL){
        if(aux->visitada == 0){
            node = copy(aux);
            node->distancia = calcularDistancia(aux,n);
            printf("%.2lf\n",node->distancia);
            pushBack(list,node);
        }
        aux = nextMap(direcciones);
    }
    return list;
}

