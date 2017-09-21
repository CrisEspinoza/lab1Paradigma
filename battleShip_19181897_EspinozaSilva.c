#include <stdio.h>
#include "funciones_19181897_EspinozaSilva.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

Board *loadBoard(int id, code *statusCode)
{
	FILE *archivo;

	char nombre[20];
    sprintf(nombre,"%05d",id);

	archivo = fopen (nombre, "r");

    Board *tablero;
	int fila,columna;
	Params barco;

    if( archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        *statusCode = ERR_FILE_NOT_FOUND;
        return 0;
    }

	fscanf(archivo,"%d %d",&fila,&columna);
	int dia, mes, anio, hora, min, seg;
	fscanf(archivo, "%d/%d/%d %d:%d:%d", &dia, &mes, &anio, &hora, &min, &seg);

    tablero = createBoard(fila,columna,barco,statusCode);
    while(getc(archivo) != '\n');
    int i,j;
    for(i = 0; i < fila; i++)
    {
		for(j = 0; j < columna; j++)
		{
			tablero[0].matriz[i][j] = getc(archivo);
		}
    }

    *statusCode = OK;

    print(tablero,1,statusCode);

	fclose(archivo);
	return tablero;
}

void saveBoard (Board *b,int *id,code *statusCode)
{
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);

    char output[128];

    strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);

	FILE *txt;
	Board *tablero;
    tablero = (Board*)malloc(sizeof(Board));
    tablero = b;

    char nombre[20];
    sprintf(nombre,"%05d",*id);

	txt = fopen(nombre, "wt");
	fprintf(txt,"%i %i\n", tablero[0].fila, tablero[0].columna);
	fprintf(txt,"%s\n",output);
	int i,j;
	for (i=0;i<tablero[0].fila;i++)
	{
		for(j=0;j<tablero[0].columna;j++)
		{
			fprintf(txt,"%c",tablero[0].matriz[i][j]);
		}
	}
	*statusCode = OK;
	fclose(txt);
}

int dificultad()
{
    char nivel[20];
    char f[15] = "facil";
    char m[15] = "medio";
    char d[15] = "dificil";
    int i = 0 ;
    for (i=0;i<1000;i++)
    {
		if (i==0)
		{
			printf("Ingrese nivel que desea jugar (facil/medio/dificil): ");
			scanf("%s",nivel);
		}
		else
		{
			printf("Ingrese un nivel valido (facil/medio/dificil): ");
			scanf("%s",nivel);
		}

		if(strcmp(nivel,f) == 0)
			{
				printf("facil \n");
				return 0;
			}
		else if (strcmp(nivel,m) == 0)
			{
				printf("medio \n");
				return 1;
			}
		else if(strcmp(nivel,d) == 0)
			{
				printf("dificil \n");
				return 2;
			}
	}
	return 8;
}


Ship* leerArchivo()
{
    Ship *lectura;
    int atak,hp,municion;
    char name[20];
    char sgl[20];
    char arm[20];
    lectura = (Ship*)malloc(10*sizeof(Ship));
    FILE *archivo;
    archivo = fopen("barcos.txt", "r" );

    if( archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }
    int i = 0 ;

    while(!feof(archivo))
    {
        fscanf(archivo,"%[a-z]:%[a-z]:%d:%d:%[a-z]:%d \n",name,sgl,&hp,&atak,arm,&municion);
        lectura[i].nombre = (char*)malloc(sizeof(char)*50);
        strcpy(lectura[i].nombre,name);
        lectura[i].sigla = (char*)malloc(sizeof(char)*50);
        strcpy(lectura[i].sigla,sgl);
        lectura[i].arma = (char*)malloc(sizeof(char)*50);
        strcpy(lectura[i].arma,arm);
        lectura[i].ataque = atak;
        lectura[i].vida = hp;
        lectura[i].municion = municion;
        i++;
    }
    fclose(archivo);
    return lectura;
}

void print(Board *b,int showComplete, code *statusCode)
{
    int n,h,j;
    int q = 1;
    char letras[30] = "abcdefghijklmnopqrstuvwxyz";
    Board *tablero;
    tablero = (Board*)malloc(sizeof(Board));
    tablero = b;
    printf("     ");
    for(h=1;h<=tablero[0].columna;h++)
    {
        printf("%2d",h);
        printf("   ");
        if (h==tablero[0].columna/2)
        {
            printf("   ");
        }
    }
    printf("\n");
    printf(" ");
    for (n=0; n<tablero[0].fila ;n++)
    {
        printf("%2d ",q);
        q++;
        for (j=0; j<tablero[0].columna ;j++)
        {
            int dividir = (tablero[0].columna/2);
            if (dividir == j)
            {
                printf(" | ");
            }
            if (showComplete == 0 && j<tablero[0].columna/2)
            {
				if(tablero[0].matriz[n][j] != '-' && tablero[0].matriz[n][j] != 'X')
				{
					printf(" - ");
				}
				else printf("  %c  ",tablero[0].matriz[n][j]);
			}
            else if(showComplete == 0 && j>=tablero[0].columna/2)
				printf("  %c  ",tablero[0].matriz[n][j]);

            else if(showComplete == 1)
				printf("  %c  ",tablero[0].matriz[n][j]);

        }
        printf(" \n ");
    }
    *statusCode = OK;
}

int putShip(Board *b ,Position p,Ship s,code *statusCode)
{
	Board *tablero;
    tablero = (Board*)malloc(sizeof(Board));
    tablero = b;

		if(s.vida == 3)
		{
			if(p.columna > (tablero[0].columna/2) && p.fila <= tablero[0].fila && tablero[0].matriz[p.fila-1][p.columna-1] == '-')
			{
				if((p.columna+1) <= tablero[0].columna)
				{
					if(tablero[0].matriz[p.fila-1][p.columna] == '-' && tablero[0].matriz[p.fila-1][(p.columna+1)] == '-')
					{
						tablero[0].matriz[p.fila-1][p.columna-1] = s.sigla[0];
						tablero[0].matriz[p.fila-1][(p.columna)] = s.sigla[1];
						tablero[0].matriz[p.fila-1][(p.columna+1)] = s.sigla[2];
						tablero[0].dueUs[p.barcoUs].posicionBarco = (Position*)malloc(3*sizeof(Position));
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].fila = (p.fila-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].columna = (p.columna-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].fila = (p.fila-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].columna = p.columna;
						tablero[0].dueUs[p.barcoUs].posicionBarco[2].fila = (p.fila-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[2].columna = (p.columna+1);
						*statusCode = OK;
						return 1;
					}
					else
						{
							*statusCode = FAIL;
							return 0;
						}
				}

				else if((p.fila+1) <= tablero[0].fila)
				{
					if(tablero[0].matriz[(p.fila)][p.columna-1] == '-' && tablero[0].matriz[(p.fila+1)][p.columna-1] == '-')
					{
						tablero[0].matriz[p.fila-1][p.columna-1] = s.sigla[0];
						tablero[0].matriz[(p.fila)][p.columna-1] = s.sigla[1];
						tablero[0].matriz[(p.fila+1)][p.columna-1] = s.sigla[2];
						tablero[0].dueUs[p.barcoUs].posicionBarco = (Position*)malloc(3*sizeof(Position));
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].fila = (p.fila-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].columna = (p.columna-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].fila = p.fila;
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].columna = (p.columna-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[2].fila = (p.fila+1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[2].columna = (p.columna-1);
						*statusCode = OK;
						return 1;
					}
					else
						{
							*statusCode = FAIL;
							return 0;
						}
				}

				else
				{
					*statusCode = FAIL;
					return 0;
				}
			}
			else
				{
					*statusCode = FAIL;
					return 0;
				}
		}

		else if (s.vida == 2)
		{
			if(p.columna > (tablero[0].columna/2) && p.fila <= tablero[0].fila && tablero[0].matriz[p.fila-1][p.columna-1] == '-')
			{
				if(p.columna >= (tablero[0].columna/2))
				{
					if(tablero[0].matriz[p.fila-1][(p.columna)] == '-')
					{
						tablero[0].matriz[p.fila-1][p.columna-1] = s.sigla[0];
						tablero[0].matriz[p.fila-1][p.columna] = s.sigla[1];
						tablero[0].dueUs[p.barcoUs].posicionBarco = (Position*)malloc(3*sizeof(Position));
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].fila = (p.fila-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].columna = (p.columna-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].fila = (p.fila-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].columna = p.columna;
						*statusCode = OK;
						return 1;
					}
					else
						{
							*statusCode = FAIL;
							return 0;
						}
				}

				else if(p.fila <= tablero[0].fila)
				{
					if(tablero[0].matriz[p.fila][p.columna-1] == '-')
					{
						tablero[0].matriz[p.fila-1][p.columna-1] = s.sigla[0];
						tablero[0].matriz[p.fila][p.columna-1] = s.sigla[1];
						tablero[0].dueUs[p.barcoUs].posicionBarco = (Position*)malloc(3*sizeof(Position));
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].fila = (p.fila-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[0].columna = (p.columna-1);
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].fila = p.fila;
						tablero[0].dueUs[p.barcoUs].posicionBarco[1].columna = (p.columna-1);
						*statusCode = OK;
						return 1;
					}
					else
						{
							*statusCode = FAIL;
							return 0;
						}
				}

				else
				{
					*statusCode = FAIL;
					return 0;
				}

			}
			else
				{
					*statusCode = FAIL;
					return 0;
				}
		}

		else if (s.vida == 1)
		{
			if(p.columna > (tablero[0].columna/2) && p.fila <= tablero[0].fila && tablero[0].matriz[p.fila-1][p.columna-1] == '-')
			{
				if ((p.columna-1) >= (tablero[0].columna/2))
				{
					tablero[0].matriz[p.fila-1][p.columna-1] = s.sigla[0];
					tablero[0].dueUs[p.barcoUs].posicionBarco = (Position*)malloc(3*sizeof(Position));
					tablero[0].dueUs[p.barcoUs].posicionBarco[0].fila = (p.fila-1);
					tablero[0].dueUs[p.barcoUs].posicionBarco[0].columna = (p.columna-1);
					*statusCode = OK;
					return 1;
				}
				else
					{
						*statusCode = FAIL;
						return 0;
					}
			}
			else
				{
					*statusCode = FAIL;
					return 0;
				}
		}
	return 9;
}

void posicinoesCp(Board *matriz, Params infor)
{
	Board *tablero;
    tablero = (Board*)malloc(4*sizeof(Board));
    tablero = matriz;

    Params informacion;
    informacion = infor;

    int orientacion,filax,colum,cantidadBarcos;
    srand(time(NULL));

    if (tablero[0].nivel == 0)
    {
		cantidadBarcos = 3;
		tablero[0].dueCp = (Dueno*)malloc(3*sizeof(Dueno));
    }
    else if (tablero[0].nivel == 1)
    {
		cantidadBarcos = 4;
		tablero[0].dueCp = (Dueno*)malloc(4*sizeof(Dueno));
	}
	else if (tablero[0].nivel == 2)
	{
		cantidadBarcos = 5;
		tablero[0].dueCp = (Dueno*)malloc(5*sizeof(Dueno));
	}

    int i = 0;
    for(i=0;i<cantidadBarcos;i++)
    {
		if(informacion.barco[i].vida == 3)
		{
			orientacion = rand()%2;
			filax = rand()%tablero[0].fila;
			colum = rand()%(tablero[0].columna/2);

			if(tablero[0].matriz[filax][colum] == '-')
			{
				if(orientacion == 0 && (colum+2) < (tablero[0].columna/2))
				{
					if(tablero[0].matriz[filax][(colum+1)] == '-' && tablero[0].matriz[filax][(colum+2)] == '-')
					{
						tablero[0].matriz[filax][colum] = informacion.barco[i].sigla[0];
						tablero[0].matriz[filax][(colum+1)] = informacion.barco[i].sigla[1];
						tablero[0].matriz[filax][(colum+2)] = informacion.barco[i].sigla[2];
						tablero[0].dueCp[i].nivel = 3;
						tablero[0].dueCp[i].vidaBarco = 3;
						tablero[0].dueCp[i].posicionBarco = (Position*)malloc(3*sizeof(Position));
						tablero[0].dueCp[i].posicionBarco[0].fila = filax;
						tablero[0].dueCp[i].posicionBarco[0].columna = colum;
						tablero[0].dueCp[i].posicionBarco[1].fila = filax;
						tablero[0].dueCp[i].posicionBarco[1].columna = (colum+1);
						tablero[0].dueCp[i].posicionBarco[2].fila = filax;
						tablero[0].dueCp[i].posicionBarco[2].columna = (colum+2);
					}
					else
						{i--;}
				}
				else if(orientacion == 1 && ((filax+2) < tablero[0].fila))
				{
					if(tablero[0].matriz[(filax+1)][colum] == '-' && tablero[0].matriz[(filax+2)][colum] == '-')
					{
						tablero[0].matriz[filax][colum] = informacion.barco[i].sigla[0];
						tablero[0].matriz[(filax+1)][colum] = informacion.barco[i].sigla[1];
						tablero[0].matriz[(filax+2)][colum] = informacion.barco[i].sigla[2];
						tablero[0].dueCp[i].nivel = 3;
						tablero[0].dueCp[i].vidaBarco = 3;
						tablero[0].dueCp[i].posicionBarco = (Position*)malloc(3*sizeof(Position));
						tablero[0].dueCp[i].posicionBarco[0].fila = filax;
						tablero[0].dueCp[i].posicionBarco[0].columna = colum;
						tablero[0].dueCp[i].posicionBarco[1].fila = (filax+1);
						tablero[0].dueCp[i].posicionBarco[1].columna = colum;
						tablero[0].dueCp[i].posicionBarco[2].fila = (filax+2);
						tablero[0].dueCp[i].posicionBarco[2].columna = colum;
					}
					else
						{i--;}
				}
				else
					{i--;}
			}
			else
				{i--;}
		}

		else if (informacion.barco[i].vida == 2)
		{
			orientacion = rand()%2;
			filax = rand()%tablero[0].fila;
			colum = rand()%(tablero[0].columna/2);

			if(tablero[0].matriz[filax][colum] == '-')
			{
				if(orientacion == 0 && (colum+1) < (tablero[0].columna/2))
				{
					if(tablero[0].matriz[filax][(colum+1)] == '-')
					{
						tablero[0].matriz[filax][colum] = informacion.barco[i].sigla[0];
						tablero[0].matriz[filax][(colum+1)] = informacion.barco[i].sigla[1];
						tablero[0].dueCp[i].nivel = 2;
						tablero[0].dueCp[i].vidaBarco = 2;
						tablero[0].dueCp[i].posicionBarco = (Position*)malloc(2*sizeof(Position));
						tablero[0].dueCp[i].posicionBarco[0].fila = filax;
						tablero[0].dueCp[i].posicionBarco[0].columna = colum;
						tablero[0].dueCp[i].posicionBarco[1].fila = filax;
						tablero[0].dueCp[i].posicionBarco[1].columna = (colum+1);
					}
					else
						{i--;}
				}
				else if(orientacion == 1 && ((filax+1) < tablero[0].fila))
				{
					if(tablero[0].matriz[(filax+1)][colum] == '-')
					{
						tablero[0].matriz[filax][colum] = informacion.barco[i].sigla[0];
						tablero[0].matriz[(filax+1)][colum] = informacion.barco[i].sigla[1];
						tablero[0].dueCp[i].nivel = 2;
						tablero[0].dueCp[i].vidaBarco = 2;
						tablero[0].dueCp[i].posicionBarco = (Position*)malloc(2*sizeof(Position));
						tablero[0].dueCp[i].posicionBarco[0].fila = filax;
						tablero[0].dueCp[i].posicionBarco[0].columna = colum;
						tablero[0].dueCp[i].posicionBarco[1].fila = (filax+1);
						tablero[0].dueCp[i].posicionBarco[1].columna = colum;
					}
					else
						{i--;}
				}
			else
				{i--;}

			}
			else
				{i--;}
		}

		else if (informacion.barco[i].vida == 1)
		{
			filax = rand()%tablero[0].fila;
			colum = rand()%(tablero[0].columna/2);

			if(tablero[0].matriz[filax][colum] == '-')
			{
				tablero[0].matriz[filax][colum] = informacion.barco[i].sigla[0];
				tablero[0].dueCp[i].nivel = 1;
				tablero[0].dueCp[i].vidaBarco = 1;
				tablero[0].dueCp[i].posicionBarco = (Position*)malloc(sizeof(Position));
				tablero[0].dueCp[i].posicionBarco[0].fila = filax;
				tablero[0].dueCp[i].posicionBarco[0].columna = colum;
			}
			else
				{i--;}
		}

	}
}

Board* createBoard(int n,int m,Params params,code *statusCode)
{
	// Creamos el tablero
    int i,j;
    Board *tablero;
    tablero = (Board*)malloc(4*sizeof(Board));

    tablero[0].matriz = (char**)malloc((n+1)*sizeof(char*));
    tablero[0].fila = n;
    tablero[0].columna = m;

    for (i=0; i<n ;i++)
    {
        tablero[0].matriz[i] = (char*)malloc((m+1)*sizeof(char));
        for (j=0; j<m ;j++)
        {
            tablero[0].matriz[i][j] = '-';
        }
    }

	*statusCode = OK;

    return tablero;
}

Params cargarBarcos(Ship *infor, int dificultad)
{

	Ship *informacion;
    informacion = (Ship*)malloc(10*sizeof(Ship));
    informacion = infor;

    int nave,barco1,barco2,barco3,n;

    if (dificultad == 0)
    {
		n=3;
		barco1 = 1;
		barco2 = 1;
		barco3 = 1;
    }
    else if (dificultad == 1)
    {
		n=4;
		barco1 = 1;
		barco2 = 1;
		barco3 = 2;
	}
	else if (dificultad == 2)
	{
		n=5;
		barco1 = 1;
		barco2 = 2;
		barco3 = 2;
	}

    Params barcos;
    barcos.barco = (Ship*)malloc((n+1)*sizeof(Ship));


    int i = 0;
    for(i=0;i<barco1;i++)
    {
		nave = rand()%3;
		barcos.barco[i] = informacion[nave];
	}

	int z = 0;
    for(z=0;z<barco2;z++)
    {
		nave = 3+rand()%3;
		barcos.barco[1+z] = informacion[nave];
	}

	int y = 0;
    for(y=0;y<barco3;y++)
    {
		nave = 6+rand()%2;
		if(dificultad==1 || dificultad == 0)
		{
			barcos.barco[2+y] = informacion[nave];
		}
		else if (dificultad==2)
		{
			barcos.barco[3+y] = informacion[nave];
		}

	}

	return barcos;
}

int checkBoard(Board *b,code *statusCode)
{
	Board *tablero;
    tablero = (Board*)malloc(sizeof(Board));
    tablero = b;

    int cantLargo;

     if (tablero[0].nivel == 0)
    {
		cantLargo = 9;
    }
    else if (tablero[0].nivel == 1)
    {
		cantLargo = 11;
	}
	else if (tablero[0].nivel == 2)
	{
		cantLargo = 13;
	}

    if ((tablero[0].columna)%2==0 && tablero[0].fila>0 && tablero[0].columna>0 )
    {
		printf("Columnas bien definidas \n");

		if (((tablero[0].columna)*(tablero[0].fila)/2) >= cantLargo)
		{
			printf("mayor o igual el largo del tablero \n");
			return 1;
		}
		else
		{
			return 0;
			*statusCode = IMPOSSIBLE_VALID_BOARD;
		}
	}
	else
	{
		return 0;
		*statusCode = IMPOSSIBLE_VALID_BOARD;
	}

return 9;
}

Params escogerBarcosUs (Board *matriz,Ship *infor, int dificultad)
{
	Ship *informacion;
    informacion = (Ship*)malloc(10*sizeof(Ship));
    informacion = infor;

    Board *tablero;
    tablero = (Board*)malloc(sizeof(Board));
    tablero = matriz;

	int barco1,barco2,barco3,opcion,opcion1;
	int l=0;

	if (dificultad == 0)
    {
		printf("El enemigo tiene 3 barcos colocados en su tablero!! \n");
		printf("--------------------------°°°----------------------------");
		printf("\n");
		printf("seleccione la cantidad de barcos que va a colocar en su tablero, puede ser +/- 1 que el enemigo \n");
		printf("Ingrese numero de barcos: ");
		scanf("%i",&tablero[0].cantBarcosUs);
		printf("\n\n");
		tablero[0].dueUs = (Dueno*)malloc(tablero[0].cantBarcosUs*sizeof(Dueno));
		barco1 = 1;
		barco2 = 0;
		barco3 = 0;
		printf("Usted puede tener solamente un barco de nivel 1, procederemos a escoger los siguientes barcos! \n");

		do
		{
			printf("Ingrese opcion del barco que desea tener en su campo \n ");
			printf(" 1. si desea colocar que su barco numero %i sea nivel 1 \n",(l+1));
			printf(" 2. si desea colocar que su barco numero %i sea nivel 2 \n",(l+1));
			printf("Ingrese su opcion: ");
			scanf("%i",&opcion1);

			switch (opcion1)
			{
				case 1 : barco3++;
						 l++;
						 break;
				case 2 : barco2++;
						 l++;
						 break;
		    }
		}while(l!=(tablero[0].cantBarcosUs-1));
    }

    else if (dificultad == 1)
     {
		printf("El enemigo tiene 4 barcos colocados en su tablero!! \n");
		printf("--------------------------°°°----------------------------");
		printf("\n");
		printf("seleccione la cantidad de barcos que va a colocar en su tablero, puede ser +/- 1 que el enemigo \n");
		printf("Ingrese numero de barcos: ");
		scanf("%i",&tablero[0].cantBarcosUs);
		printf("\n\n");
		tablero[0].dueUs = (Dueno*)malloc(tablero[0].cantBarcosUs*sizeof(Dueno));
		barco1 = 1;
		barco2 = 0;
		barco3 = 0;
		printf("Usted puede tener solamente un barco de nivel 1, procederemos a escoger los siguientes barcos! \n");

		do
		{
			printf("Ingrese opcion del barco que desea tener en su campo \n ");
			printf(" 1. si desea colocar que su barco numero %i sea nivel 1 \n",(l+1));
			printf(" 2. si desea colocar que su barco numero %i sea nivel 2 \n",(l+1));
			printf("Ingrese su opcion: ");
			scanf("%i",&opcion1);

			switch (opcion1)
			{
				case 1 : barco3++;
						 l++;
						 break;
				case 2 : barco2++;
						 l++;
						 break;
		    }
		}while(l!=(tablero[0].cantBarcosUs-1));
    }

	else if (dificultad == 2)
	{
		printf("El enemigo tiene 5 barcos colocados en su tablero!! \n");
		printf("--------------------------°°°----------------------------");
		printf("\n");
		printf("seleccione la cantidad de barcos que va a colocar en su tablero, puede ser +/- 1 que el enemigo \n");
		printf("Ingrese numero de barcos: ");
		scanf("%i",&tablero[0].cantBarcosUs);
		printf("\n\n");
		tablero[0].dueUs = (Dueno*)malloc(tablero[0].cantBarcosUs*sizeof(Dueno));
		barco1 = 1;
		barco2 = 0;
		barco3 = 0;
		printf("Usted puede tener solamente un barco de nivel 1, procederemos a escoger los siguientes barcos! \n");

		do
		{
			printf("Ingrese opcion del barco que desea tener en su campo \n ");
			printf(" 1. si desea colocar que su barco numero %i sea nivel 1 \n",(l+1));
			printf(" 2. si desea colocar que su barco numero %i sea nivel 2 \n",(l+1));
			printf("Ingrese su opcion: ");
			scanf("%i",&opcion1);

			switch (opcion1)
			{
				case 1 : barco3++;
						 l++;
						 break;
				case 2 : barco2++;
						 l++;
						 break;
		    }
		}while(l!=(tablero[0].cantBarcosUs-1));
    }

	Params barcoEscogido;
	barcoEscogido.barco = (Ship*)malloc(6*sizeof(Ship));

	int i = 0;

		while(i<barco1)
		{
			printf("Escoga el barco de nivel 3: \n");
			printf("1.- %s \n",informacion[0].nombre);
			printf("2.- %s \n",informacion[1].nombre);
			printf("3.- %s \n",informacion[2].nombre);
			printf("Ingrese opcion: ");
			scanf("%i",&opcion);

			switch (opcion)
			{
				case 1 : 	barcoEscogido.barco[i] = informacion[opcion-1];
							tablero[0].dueUs[i].nivel = 3;
							tablero[0].dueUs[i].vidaBarco = 3;
							i++;
							break;
				case 2 : 	barcoEscogido.barco[i] = informacion[opcion-1];
							tablero[0].dueUs[i].nivel = 3;
							tablero[0].dueUs[i].vidaBarco = 3;
							i++;
							break;
				case 3 : 	barcoEscogido.barco[i] = informacion[opcion-1];
							tablero[0].dueUs[i].nivel = 3;
							tablero[0].dueUs[i].vidaBarco = 3;
							i++;
							break;

			}
		}

	int y = 0;

		while(y<barco2)
		{
			printf("Escoga el barco de nivel 2: \n");
			printf("1.- %s \n",informacion[3].nombre);
			printf("2.- %s \n",informacion[4].nombre);
			printf("3.- %s \n",informacion[5].nombre);
			printf("Ingrese opcion: ");
			scanf("%i",&opcion);

			switch (opcion)
			{
				case 1 : 	barcoEscogido.barco[1+y] = informacion[3+opcion-1];
							tablero[0].dueUs[i+y].nivel = 2;
							tablero[0].dueUs[i+y].vidaBarco = 2;
							y++;
							break;
				case 2 : 	barcoEscogido.barco[1+y] = informacion[3+opcion-1];
							tablero[0].dueUs[i+y].nivel = 2;
							tablero[0].dueUs[i+y].vidaBarco = 2;
							y++;
							break;
				case 3 : 	barcoEscogido.barco[i+y] = informacion[3+opcion-1];
							tablero[0].dueUs[i+y].nivel = 2;
							tablero[0].dueUs[i+y].vidaBarco = 2;
							y++;
							break;
			}
		}

	int z = 0;

		while(z<barco3)
		{
			printf("Escoga el barco de nivel 1: \n");
			printf("1.- %s \n",informacion[6].nombre);
			printf("2.- %s \n",informacion[7].nombre);
			printf("Ingrese opcion: ");
			scanf("%i",&opcion);

			switch (opcion)
			{
				case 1 : 	barcoEscogido.barco[y+1+z] = informacion[6+opcion-1];
							tablero[0].dueUs[y+1+z].nivel = 1;
							tablero[0].dueUs[y+1+z].vidaBarco = 1;
							z++;
							break;

				case 2 : 	barcoEscogido.barco[y+1+z] = informacion[6+opcion-1];
							tablero[0].dueUs[y+1+z].nivel = 1;
							tablero[0].dueUs[y+1+z].vidaBarco = 1;
							z++;
							break;

			}
		}

return barcoEscogido;
}

void playCp (Board *matriz)
{
	Board *tablero;
    tablero = (Board*)malloc(sizeof(Board));
    tablero = matriz;

	int barcoCp,cantBarco,filaCp,columnaCp;
	srand(time(NULL));

    if (tablero[0].nivel == 0)
    {
		cantBarco = tablero[0].cantBarcosUs;
    }
    else if (tablero[0].nivel == 1)
    {
		cantBarco = tablero[0].cantBarcosUs;
	}
	else if (tablero[0].nivel  == 2)
	{
		cantBarco = tablero[0].cantBarcosUs;
	}

	filaCp = rand()%tablero[0].fila;
	columnaCp = (tablero[0].columna/2)+rand()%(tablero[0].columna/2);
	barcoCp = 1+rand()%3;

    int i,z,j;

    for(z=1;z<4;z++)
    {

		printf("el numero de fila es: %i\n ",filaCp+1);
		printf("El numero de columna es :%i\n \n",columnaCp+1);

		if (barcoCp == z )
		{
			if (tablero[0].matriz[filaCp][columnaCp] == '-')
			{
				tablero[0].matriz[filaCp][columnaCp] = 'X';
				break;
			}

			else if (tablero[0].matriz[filaCp][columnaCp]  != '-' && tablero[0].matriz[filaCp][columnaCp] != 'X')
			{
				for(i=0;i<cantBarco;i++)
				{
					for (j=0;j<3;j++)
					{
						if (tablero[0].dueUs[i].posicionBarco[j].fila == filaCp && tablero[0].dueUs[i].posicionBarco[j].columna == columnaCp)
						{
							if (tablero[0].dueUs[i].nivel == 1)
							{
								tablero[0].dueUs[i].vidaBarco--;
								printf("Entramos al 3 :Le quitamos vida al barco numero 1 \n ");
								if (tablero[0].dueUs[i].vidaBarco == 0)
								{
									printf("Entre al 4: Barco nivel 1 derrotado por completo  \n");
									tablero[0].matriz[filaCp][columnaCp] = 'X';
									tablero[0].cantBarcosUs--;
									printf("\n");
									printf("\n");
									printf("%i",tablero[0].cantBarcosUs);
									printf("\n");
									printf("\n");
									break;
								}
							}

							else if (tablero[0].dueUs[i].nivel == 2)
							{
								tablero[0].dueUs[i].vidaBarco--;
								printf("Entramos al 3 :Le quitamos vida al barco numero 2 \n ");
								if (tablero[0].dueUs[i].vidaBarco == 0)
								{
									printf("Entre al 4: Barco nivel 2 derrotado por completo \n");
									tablero[0].matriz[filaCp][columnaCp] = 'X';
									tablero[0].cantBarcosUs--;
									printf("\n");
									printf("\n");
									printf("%i",tablero[0].cantBarcosUs);
									printf("\n");
									printf("\n");
									break;
								}
							}

							else if (tablero[0].dueUs[i].nivel == 3)
							{
								tablero[0].dueUs[i].vidaBarco--;
								printf("Entramos al 3 :Le quitamos vida al barco numero 3 \n ");
								if (tablero[0].dueUs[i].vidaBarco == 0)
								{
									printf("Entre al 4: Barco nivel 3 derrotado por completo \n");
									tablero[0].matriz[filaCp][columnaCp] = 'X';
									tablero[0].cantBarcosUs--;
									printf("\n");
									printf("\n");
									printf("%i",tablero[0].cantBarcosUs);
									printf("\n");
									printf("\n");
									break;
								}
							}

						}
					}
				}
			tablero[0].matriz[filaCp][columnaCp] = 'X';
			}

			else if (tablero[0].matriz[filaCp][columnaCp] == 'X')
			{
				z=0;
				filaCp = rand()%tablero[0].fila;
				columnaCp = (tablero[0].columna/2)+rand()%(tablero[0].columna-columnaCp);
			}
		}
	}
}

int play (Board *b,Ship *ship,Position *pArray,code *statusCode)
{
	Board *tablero;
    tablero = (Board*)malloc(sizeof(Board));
    tablero = b;

    Ship *barco;
    barco = (Ship*)malloc(sizeof(Ship));
    barco = ship;

    Position *posUs;
    posUs = (Position*)malloc(sizeof(Position));
    posUs = pArray;

    int cantBarco;

    if (tablero[0].nivel == 0)
    {
		cantBarco = 3;
    }
    else if (tablero[0].nivel == 1)
    {
		cantBarco = 4;
	}
	else if (tablero[0].nivel  == 2)
	{
		cantBarco = 5;
	}

    int i,z,j;

    for(z=1;z<4;z++)
    {
		if (barco[0].vida == z )
		{
			if (tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1] == '-')
			{
				tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1] = 'X';
				playCp (tablero);
				*statusCode = OK;
				return 0;
			}

			else if (tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1]  != '-' && tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1] != 'X')
			{;
				for(i=0;i<cantBarco;i++)
				{
					for (j=0;j<3;j++)
					{
						if (tablero[0].dueCp[i].posicionBarco[j].fila == (posUs[0].fila-1) && tablero[0].dueCp[i].posicionBarco[j].columna == (posUs[0].columna-1))
						{
							if (tablero[0].dueCp[i].nivel == 1)
							{
								tablero[0].dueCp[i].vidaBarco--;
								printf("Entramos al 3 :Le quitamos vida al barco numero 1 \n ");
								if (tablero[0].dueCp[i].vidaBarco == 0)
								{
									printf("Entre al 4: Barco nivel 1 derrotado por completo  \n");
									tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1] = 'X';
									playCp (tablero);
									*statusCode = OK;
									return 2;
								}
							}

							else if (tablero[0].dueCp[i].nivel == 2)
							{
								tablero[0].dueCp[i].vidaBarco--;
								printf("Entramos al 3 :Le quitamos vida al barco numero 2 \n ");
								if (tablero[0].dueCp[i].vidaBarco == 0)
								{
									printf("Entre al 4: Barco nivel 2 derrotado por completo \n");
									tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1] = 'X';
									playCp (tablero);
									*statusCode = OK;
									return 2;
								}
							}

							else if (tablero[0].dueCp[i].nivel == 3)
							{
								tablero[0].dueCp[i].vidaBarco--;
								printf("Entramos al 3 :Le quitamos vida al barco numero 3 \n ");
								if (tablero[0].dueCp[i].vidaBarco == 0)
								{
									printf("Entre al 4: Barco nivel 3 derrotado por completo \n");
									tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1] = 'X';
									playCp (tablero);
									*statusCode = OK;
									return 2;
								}
							}

						tablero[0].matriz[posUs[0].fila-1][posUs[0].columna-1] = 'X';
						playCp (tablero);
						*statusCode = OK;
						return 1;

						}
					}
				}
			}

		}

	}
return 9 ;
}
