#ifndef entregas_h
#define entregas_h


typedef struct Direccion Direccion;

void importarArchivo (HashMap * direcciones);

char * txt (char * temp, int pos );

void agregarMapa(HashMap * direcciones,char * x, char * y,int id);

void mostrarDireccionesPorId(HashMap * direcciones);

double calcularDistancia(Direccion * aux1,Direccion * aux2);

void distancia2Entregas(HashMap * direcciones);

void bubbleSortDistancia(Direccion ** Array,int largo);

void mostrar3EntregasCercanas(HashMap * direcciones);

Direccion* copy(Direccion* n);

void * get_adj_nodes(HashMap * direcciones,Direccion * n);

void * copiarHashmap(HashMap * direcciones);

void mostrarDireccionesPorDistancia(List * list);

void mostrarRuta(List * ruta);

void * buscarLista(List * list,int key);

void crearRuta(HashMap * direcciones,HashMap * rutasCreadas,List * listaDeNombres);

void crearRutaAleatoria(HashMap * direcciones,HashMap * rutasCreadas,List * listaDeNombres);

double calcularDistanciaRuta(List * ruta);

List * copiarRuta(List * ruta);

void mejorarRuta (HashMap * rutasCreadas);

void mostarRutas(HashMap * rutasCreadas,List * listaDeNombres);

#endif /** entregas.h **/