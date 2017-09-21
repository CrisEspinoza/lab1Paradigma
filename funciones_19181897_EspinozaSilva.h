#include <stdio.h>

typedef struct{

	int fila;
	int columna;
	int barcoUs;

}Position;

typedef struct
{
	Position *posicionBarco;
	int vidaBarco;
	int nivel;

}Dueno;

typedef struct{

int municion;
int ataque;
int vida;
char *nombre;
char *sigla;
char *arma;
Position *posUs;
Position *posCp;

}Ship;

typedef struct{

    Ship *barco;

}Params;

typedef struct {

    int fila;
    int columna;
    int nivel;
    char **matriz;
    int cantBarcosUs;
    Ship barco;
    Params para;
    Dueno *dueCp;
    Dueno *dueUs;

}Board;

typedef struct {

	Ship barco;
	Position posicion;

}Game;

typedef struct{

	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;

}tm;

typedef enum code { OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM, IMPOSSIBLE_VALID_BOARD, FAIL } code;

Params escogerBarcosUs (Board *matriz,Ship *infor, int dificultad);
int dificultad();
Ship* leerArchivo();
void print(Board *matriz,int showComplete, code *statusCode);
Board *loadBoard(int id, code *statusCode);
int play (Board *matriz,Ship *barcoUs,Position *posiciones,code *statusCode);
void playCp (Board *matriz);
void posicinoesCp(Board *matriz, Params infor);
int putShip(Board *matriz ,Position pos,Ship barco,code *statusCode);
void saveBoard (Board *matriz,int *id,code *statusCode);
Params cargarBarcos(Ship *infor, int dificultad);
int checkBoard(Board *matriz,code *statusCode);
Board* createBoard(int fila,int columna,Params barcos,code *statusCode);
