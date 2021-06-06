#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "hashmap.h"
#include "entregas.h"


typedef struct Direccion {
    int cordX;   //Posciciones x e y de la direccion
    int cordY;
    int identificador;  //"Numero" de la direccion segun el archivo .txt
    int visitada;       //const value 0
    double distancia; //Distancia desde la direccion anterior
    double distanciaTotal;
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
    if (aux1 == NULL || aux2 == NULL ) return 0;
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
        printf(" Id no valida, por favor ingrese una id de la lista: ");
        scanf("%s",&entrada1);
        Direccion * aux1 = searchMap(direcciones,entrada1);
    }

    printf(" Entrega 2: ");
    scanf("%s",&entrada2);
    Direccion * aux2 = searchMap(direcciones,entrada2);
    if(aux2 == NULL){
        printf(" Id no valida, por favor ingrese una id de la lista: ");
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
            pushBack(list,node);
        }
        aux = nextMap(direcciones);
    }
    return list;
}

void * copiarHashmap(HashMap * direcciones){
    //copia del mapa
    HashMap * copiaMapa = createMap(100);

    //nodo que se desea copiar
    Direccion * aux = firstMap(direcciones);

    //copia del nodo
    Direccion * copia;

    char * auxKey;

    while(aux != NULL){
        auxKey = (char*)malloc(sizeof(char)*5);
        copia = copy(aux);
        sprintf(auxKey,"%d",copia->identificador);
        insertMap(copiaMapa,auxKey,copia);
        aux = nextMap(direcciones);
    }
    return copiaMapa;
}

void mostrarDireccionesPorDistancia(List * list){
    Direccion ** auxList = (Direccion**) malloc(sizeof(Direccion * )*get_size(list));

    int largo = get_size(list);

    Direccion * node = first(list);
    for(int i = 0;node != NULL;i++){
        auxList[i] = node;
        node = next(list);
    }

    bubbleSortDistancia(auxList,largo);

    for(int i = 0;i < largo;i++){
        printf(" Distancia: %.2lf - ID: %d - Coordenada X: %d - Coordenada Y: %d\n",auxList[i]->distancia,auxList[i]->identificador,auxList[i]->cordX,auxList[i]->cordY);
    }
}

void mostrarRuta(List * ruta){
    double distanciaRuta = 0.0;
    Direccion * aux = first(ruta);
    int flag = 0;
    while(aux != NULL){
        if(flag == 0){
            printf(" %d ",aux->identificador);
            flag = 1;
        }
        else printf("- %d ",aux->identificador);
        aux = next(ruta);
        if(aux != NULL) distanciaRuta += aux->distancia;
    }
    printf("\n Distancia ruta: %.2lf\n",distanciaRuta);
    aux = first(ruta);
    aux->distanciaTotal = distanciaRuta;    //Almacenada en el primer nodo de la ruta
    printf(" Distancia desde la direccion inicial hasta la ultima: %.2lf\n",aux->distancia);
}

void * buscarLista(List * list,int key){
    Direccion * aux = first(list);
    while(aux != NULL){
        if(aux->identificador == key) return aux;
        aux = next(list);
    }
    return NULL;
}

void crearRuta(HashMap * direcciones,HashMap * rutasCreadas){
    int cordX;
    int cordY;
    printf(" Ingrese sus cordenadas actuales:\n");
    printf(" Coordenada X: ");
    scanf("%d",&cordX);
    printf(" Coordenada Y: ");
    scanf("%d",&cordY);

    Direccion * direccionInicial = (Direccion *)malloc(sizeof(Direccion));
    direccionInicial->cordX = cordX;
    direccionInicial->cordY = cordY;
    direccionInicial->identificador = 0;
    direccionInicial->visitada = 1;

    Direccion * actual = direccionInicial;
    Direccion * auxDireccion;

    List * ruta = createList();
    pushBack(ruta,direccionInicial);

    HashMap * auxDirecciones = copiarHashmap(direcciones);

    int entrada = 0;
    char auxId[5];
    List * auxAdjNodes = get_adj_nodes(auxDirecciones,actual);

    while(first(auxAdjNodes) != NULL){
        printf(" Seleccione la entrega que desea entregar(ingrese ID)\n");
        mostrarDireccionesPorDistancia(auxAdjNodes);
        printf(" Entrega: ");
        scanf("%d",&entrada);
        actual = buscarLista(auxAdjNodes,entrada);
        while(actual == NULL){
            printf(" ID no valida, por favor ingrese una ID de la lista: ");
            scanf("%d",&entrada);
            actual = buscarLista(auxAdjNodes,entrada);
        }
        pushBack(ruta,actual);
        sprintf(auxId,"%d",entrada);
        auxDireccion = searchMap(auxDirecciones,auxId);
        auxDireccion->visitada = 1;
        auxAdjNodes = get_adj_nodes(auxDirecciones,actual);
    }
    direccionInicial = first(ruta);
    direccionInicial->distancia = calcularDistancia(direccionInicial,actual);
    mostrarRuta(ruta);
    printf(" Ingrese un nombre para la ruta: ");
    char * nombreRuta = (char*)malloc(sizeof(char)*50);
    while(getchar()!='\n');
    gets(nombreRuta);
    insertMap(rutasCreadas,nombreRuta,ruta);
} 

void crearRutaAleatoria(HashMap * direcciones,HashMap * rutasCreadas){
    Direccion * direccionInicial = (Direccion *)malloc(sizeof(Direccion));
    direccionInicial->cordX = 0;
    direccionInicial->cordY = 0;
    direccionInicial->identificador = 0;
    direccionInicial->visitada = 1;

    Direccion * actual = direccionInicial;
    Direccion * auxDireccion;

    List * ruta = createList();

    HashMap * auxDirecciones = copiarHashmap(direcciones);

    int entrada = 0;
    char auxId[5];
    List * auxAdjNodes = get_adj_nodes(auxDirecciones,actual);
    int largo = get_size(auxAdjNodes);

    while(first(auxAdjNodes) != NULL){
        entrada = rand() % (largo + 1);
        actual = buscarLista(auxAdjNodes,entrada);
        while(actual == NULL){
            entrada = rand() % (largo + 1);
            actual = buscarLista(auxAdjNodes,entrada);

        }
        pushBack(ruta,actual);
        sprintf(auxId,"%d",entrada);
        auxDireccion = searchMap(auxDirecciones,auxId);
        auxDireccion->visitada = 1;
        auxAdjNodes = get_adj_nodes(auxDirecciones,actual);
    }
    direccionInicial = first(ruta);
    direccionInicial->distancia = calcularDistancia(direccionInicial,actual);
    mostrarRuta(ruta);
    printf(" Ingrese un nombre para la ruta: ");
    char * nombreRuta = (char*)malloc(sizeof(char)*50);
    gets(nombreRuta);
    insertMap(rutasCreadas,nombreRuta,ruta);
}

void mejorarRuta (HashMap * rutasCreadas)
{
    printf(" Ingrese un nombre para la ruta a mejorar: ");
    char * nombreRuta = (char*)malloc(sizeof(char)*50);
    gets(nombreRuta);

    List * ruta = searchMap(rutasCreadas, nombreRuta);
    List * auxList;
    Direccion * auxiliarDireccion;
    Direccion * aux2;

    mostrarRuta (ruta);
    printf ("Ingrese 1 para cambio manual, 0 para automatico: ");
    int op,id1, id2;
    double distanciaRuta = 0.0;
    scanf ("%d", &op);

    if (op == 1) {
        printf ("ingrese la direccion 1 a intercambiar :\n");
        scanf ("%d", &id1);
        printf ("ingrese la direccion 2 a intercambiar :\n");
        scanf ("%d", &id2);
        auxiliarDireccion = first(ruta);
        while (auxiliarDireccion != NULL) {
           if ((auxiliarDireccion->identificador == id1) || (auxiliarDireccion->identificador == id2) )
           {
               if (auxiliarDireccion->identificador == id1)
               {
                   aux2 = buscarLista(ruta, id2);
                   //aux2->distancia = calcularDistancia(aux2, last(aux));
                   pushBack(auxList, aux2);
               }
               else if (auxiliarDireccion->identificador == id2) {
                   aux2 = buscarLista(ruta, id1);
                   //aux2->distancia = calcularDistancia(aux2, last(aux));
                   pushBack(auxList, aux2);
               }
           }
           if ((auxiliarDireccion->identificador != id1) && (auxiliarDireccion->identificador != id2) )
           {
               pushBack(auxList, auxiliarDireccion);
           }
           if(aux2 != NULL) distanciaRuta += aux2->distancia;
           auxiliarDireccion = next(ruta);     
        }
    }
    if (op == 2) {

        List * auxList;
        auxiliarDireccion = first(ruta);
        while (auxiliarDireccion != NULL)
        {
            pushBack(auxList, auxiliarDireccion);

            auxiliarDireccion = next(ruta);
        }
        mostrarRuta(auxList);
    }


    //ruta = (rutasCreadas);
    //mostrarRuta(ruta);
}

 
void mostrarTodo (HashMap * rutasCreadas){
  
    List * ruta = firstMap(rutasCreadas);
    HashMap * rutasOrdenadas;
    int i,j;


    List ** auxList = (List**) malloc(sizeof(List * )*get_size(ruta));

    int largo = get_size(ruta);

    List * node = firstMap(rutasCreadas);
    for( i = 0;node != NULL;i++){
        auxList[i] = node;
        node = nextMap(rutasCreadas);
    }

    //bubbleSortRutas(auxList,largo);
    List * aux;
    for ( i = 0; i < largo - 1; i++)
    {   
        Direccion * auxDireccion = first(auxList[i]);
        Direccion * auxDireccion2 = first(auxList[i+1]);
        
        for(j = 0;j < largo - i - 1;j++){
            if(auxDireccion->distanciaTotal > auxDireccion2->distanciaTotal){
                aux = auxList[j+1];
                auxList[j+1] = auxList[j];
                auxList[j] = aux;
            }
        }
        
        
    }
    /**for (i = 0; i < largo; i++)
    {

    }
    
}
/** 
 void bubbleSortRutas(Direccion ** Array, int largo){
    int i,j;
    //List * ruta = firstMap(rutasCreadas);
    //Direccion * auxDireccion = first(ruta);
    //int largo = get_size(ruta);
    Direccion * aux;


    for(i = 0;i < largo - 1;i++){
        for(j = 0;j < largo - i - 1;j++){
            if(Array[j]->distanciaTotal > Array[j+1]->distanciaTotal){
                aux = Array[j+1];
                Array[j+1] = Array[j];
                Array[j] = aux;
            }
        }
    }
} **/