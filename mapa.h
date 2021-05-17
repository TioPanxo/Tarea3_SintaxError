#ifndef mapa_h
#define mapa_h


typedef struct direccion {
    int cordX;   //Posciciones x e y de la direccion
    int cordY;
    int identificador;  //"Numero" de la direccion segun el archivo .txt
    HashMap * distancia;
} Direccion;

void importarArchivo (HashMap * direcciones);
char * txt (char * temp, int pos );
Direccion * crearDireccion (int );
void agregarMapa(HashMap * direcciones,char * x, char * y,int id);

#endif /** mapa.h **/