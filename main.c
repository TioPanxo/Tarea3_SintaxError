#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"
#include "entregas.h"



int main ()
{
    HashMap * direcciones = createMap(100);
    HashMap * rutasCreadas = createMap(100);
    char poscicion[20]; //ASUMO que no tendra tantos digitos ...

    int flag = 0;
    int menu = 0;
    int op;

    while (menu >= 0 && menu <= 8) {
        menu = -1;
        printf("===============================================================\n");
        printf("                             RUTAS                             \n");
        printf("===============================================================\n");
        printf("|   1.- Importar archivo de coordenadas                       |\n");
        printf("|   2.- Distancia entre entregas                              |\n");
        printf("|   3.- Mostrar 3 entregas mas cercanas a las coordenadas     |\n");
        printf("|       ingresadas                                            |\n");
        printf("|   4.- Crea una ruta                                         |\n");
        printf("|   5.- Generar ruta aleatoria                                |\n");
        printf("|   6.- Mejorar ruta                                          |\n");
        printf("|   7.- Mostrar rutas                                         |\n");
        printf("|   8.- Mejor rutas                                           |\n");
        printf("|   0.- Salir del programa                                    |\n");
        printf("===============================================================\n");
        printf(" Ingrese un numero: ");
        scanf(" %d", &menu);

        while(menu < 0 || menu > 8){
            printf ("===============================================================\n");
            printf (" Por favor ingrese uno de los numeros anteriores: ");
            while(getchar()!='\n'); //limpiar buffer del teclado en caso de que el usuario ingrese una 
            //opcion no valida
            scanf (" %d", &menu);
            if(menu == 0 ) exit(0);
        }
        printf("===============================================================\n");
        fflush(stdin);
            
        switch(menu)
        {   
            //op = -1;
            case 1:
                importarArchivo (direcciones);
                flag = 1;
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;


            case 2:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Direcciones\n");
                    break;
                } 
                distancia2Entregas(direcciones);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;


            case 3:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Direcciones\n");
                    break;
                } 
                mostrar3EntregasCercanas(direcciones);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 4:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Direcciones\n");
                    break;
                } 
                crearRuta(direcciones,rutasCreadas);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                 break;

            case 5:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Direcciones\n");
                    break;
                } 
                //FUNCION***********************************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 6:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Direcciones\n");
                    break;
                } 
               //FUNCION***********************************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 7:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Direcciones\n");
                    break;
                } 
                //FUNCION***********************************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 8:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Direcciones\n");
                    break;
                } 
                //FUNCION***********************************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            
            case 0: 
                exit(0);
                break;
        }
    }


    return 0;
}