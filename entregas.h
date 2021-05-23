#ifndef entregas_h
#define entregas_h


typedef struct direccion Direccion;

void importarArchivo (HashMap * direcciones);
char * txt (char * temp, int pos );
void agregarMapa(HashMap * direcciones,char * x, char * y,int id);

#endif /** entregas.h **/