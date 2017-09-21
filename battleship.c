#include <stdio.h>
#include "battleShip_19181897_EspinozaSilva.c"
#include <time.h>

int main()
{
	code statusCode;
	int opcion,fila,columna,id,nombre,level,numBarco,opcion2,cantidadBarcos,p,valid;
	Board *campo;
	campo = NULL;
	Params barcoCargado;
	Ship *archivo;
	srand(time(NULL));
	Params barcoUs;
	Position *posUs;
	posUs = (Position*)malloc(sizeof(Position));
	Ship *barco1Cp;
	Ship *barco2Cp;
	Ship *barco3Cp;
	Ship *barco4Cp;
	Ship *barco5Cp;
	Ship *barco1Us;
	Ship *barco2Us;
	Ship *barco3Us;
	Ship *barco4Us;
	Ship *barco5Us;
	Ship *barco6Us;

	do
    {
        printf( "\n   1. Crear tablero");
        printf( "\n   2. Cargar tablero" );
        printf( "\n   3. Validar tablero " );
        printf( "\n   4. Imprimir tablero" );
        printf( "\n   5. Guardar tablero" );
        printf( "\n   6. Colocar las embarcaciones" );
        printf( "\n   7. Jugar");
        printf( "\n   8. Creditos");
        printf( "\n   9. Salir" );
        printf( "\n\n   Introduzca opcion (1-4): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
			case 1: level = dificultad();
					printf("Ingrese el numero de filas para el tablero: ");
					scanf("%i",&fila);
					printf("Ingrese el numero de columna para el tablero: ");
					scanf("%i",&columna);
					archivo = leerArchivo();
					barcoCargado = cargarBarcos(archivo,level);
					campo = createBoard(fila,columna,barcoCargado,&statusCode);
					campo[0].nivel = level;
					statusCode = OK;
					break;

			case 2: printf("Ingrese nombre del archivo que desea cargar: ");
					scanf("%i",&nombre);
					loadBoard(nombre,&statusCode);
					statusCode = OK;
					break;

			case 3: if (campo != NULL)
					{
						if(checkBoard(campo,&statusCode) == 1)
						{
							printf("TABLERO VALIDO \n");
							posicinoesCp(campo,barcoCargado);
							valid = 0;
							statusCode = OK;
						}

						else
						{
							statusCode = FAIL;
							printf("Tablero invalido \n");
							valid = 1;
						}
					}

					else
					{
						statusCode = FAIL;
						printf("No existe ningun tablero, primero crea su tablero opcion 1 \n");
					}
					break;

			case 4: if (campo != NULL && valid == 0)
					{
						print(campo,0,&statusCode);
						statusCode = OK;
					}
					else
					{
						statusCode = FAIL;
						printf("NO se encuentra ningun tablero para imprimir \n");
					}
					break;

			case 5: if(campo!=NULL && valid == 0)
					{
						id = rand()%9999;
						printf("%i",id);
						saveBoard (campo,&id,&statusCode);
						statusCode = OK;
					}
					else
					{
						statusCode = FAIL;
						printf("No existe un tablero creado \n");
					}
					break;

			case 6: if (campo!=NULL && valid == 0)
					{
					printf("Escoger los barcos que desea ocupar en este combate \n");
					barcoUs = escogerBarcosUs(campo,archivo,level);

					if (campo[0].nivel == 0)
					{
						Ship barco;
						numBarco = campo[0].cantBarcosUs;
						int x,a;
						for (x=0;x<numBarco;x++)
						{
							barco = barcoUs.barco[x];
							Position pos;
							pos.barcoUs = x;
							printf("Ingrese fila que desea colocar el barco numero %i: ",(x+1));
							scanf("%i",&pos.fila);
							printf("Ingrese columna que desea colocar el barco numero %i: ",(x+1));
							scanf("%i",&pos.columna);
							a = putShip(campo,pos,barco,&statusCode);
							printf("%i",pos.barcoUs);

							if (a == 1)
							{
								print(campo,1,&statusCode);
							}
							else
							{
								statusCode = FAIL;
								printf("Posiciones invalidas, ingrese nuevamente \n");
								x--;
							}
						}
					}

					else if (campo[0].nivel == 1)
					{
						Ship barco;
						numBarco = campo[0].cantBarcosUs;
						int x,a;
						for (x=0;x<numBarco;x++)
						{
							barco = barcoUs.barco[x];
							Position pos;
							pos.barcoUs = x;
							printf("Ingrese fila que desea colocar el barco numero %i: ",(x+1));
							scanf("%i",&pos.fila);
							printf("Ingrese columna que desea colocar el barco numero %i: ",(x+1));
							scanf("%i",&pos.columna);
							a = putShip(campo,pos,barco,&statusCode);

							if (a == 1)
							{
								print(campo,1,&statusCode);
							}
							else
							{
								statusCode = FAIL;
								printf("Posiciones invalidas, ingrese nuevamente \n");
								x--;
							}
						}
					}

					else if (campo[0].nivel == 2)
					{
						Ship barco;
						numBarco = campo[0].cantBarcosUs;
						int x,a;
						for (x=0;x<numBarco;x++)
						{
							barco = barcoUs.barco[x];
							Position pos;
							pos.barcoUs = x;
							printf("Ingrese fila que desea colocar el barco numero %i: ",(x+1));
							scanf("%i",&pos.fila);
							printf("Ingrese columna que desea colocar el barco numero %i: ",(x+1));
							scanf("%i",&pos.columna);
							a = putShip(campo,pos,barco,&statusCode);
							if (a == 1)
							{
								print(campo,1,&statusCode);
							}
							else
							{
								statusCode = FAIL;
								printf("Posiciones invalidas, ingrese nuevamente \n");
								x--;
							}
						}
					}
					statusCode = OK;
					}

					else
					{
						statusCode = FAIL;
						printf("Primero tiene que crear el tablero para ocupar esta opciones.!");
					}
					break;

			case 7: if(campo != NULL && valid == 0)
					{
					// cargando barcos de computadora para la batalla...

					barco1Cp = (Ship*)malloc(sizeof(Ship));
					barco1Cp[0] = barcoCargado.barco[0];
					barco2Cp = (Ship*)malloc(sizeof(Ship));
					barco2Cp[0] = barcoCargado.barco[1];
					barco3Cp = (Ship*)malloc(sizeof(Ship));
					barco3Cp[0] = barcoCargado.barco[2];
					barco4Cp = (Ship*)malloc(sizeof(Ship));
					barco4Cp[0] = barcoCargado.barco[1];
					barco5Cp = (Ship*)malloc(sizeof(Ship));
					barco5Cp[0] = barcoCargado.barco[2];

					// cargamos barcos de usuario para la batalla....

					barco1Us = (Ship*)malloc(sizeof(Ship));
					barco1Us[0] = barcoUs.barco[0];
					barco2Us = (Ship*)malloc(sizeof(Ship));
					barco2Us[0] = barcoUs.barco[1];
					barco3Us = (Ship*)malloc(sizeof(Ship));
					barco3Us[0] = barcoUs.barco[2];
					barco4Us = (Ship*)malloc(sizeof(Ship));
					barco4Us[0] = barcoUs.barco[3];
					barco5Us = (Ship*)malloc(sizeof(Ship));
					barco5Us[0] = barcoUs.barco[4];
					barco6Us = (Ship*)malloc(sizeof(Ship));
					barco6Us[0] = barcoUs.barco[5];


					if (campo[0].nivel == 0)
					{
						cantidadBarcos = 3;
						do
						{
							// Escogimos el barco que va a realizar el ataque.
							printf( " Ingrese la opcion del barco que desea que realize el ataque \n");
							printf( " 1. %s \n",barco1Us[0].nombre);
							printf( " 2. %s \n",barco2Us[0].nombre);
							if(campo[0].cantBarcosUs >= 3){printf( " 3. %s \n",barco3Us[0].nombre);}
							if(campo[0].cantBarcosUs >= 4){printf( " 4. %s \n",barco4Us[0].nombre);}

							scanf("%d",&opcion2);
							printf("\n");

							switch ( opcion2 )
							{
								case 1:	do
										{
											printf("Ingrese fila donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].fila);
											printf("Ingrese columna donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].columna);

										}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

										// Funcion de ataque:
										p = play (campo,barco1Us,posUs,&statusCode);
										if (p == 2)
										{
											cantidadBarcos--;
										}
										break;

								case 2:	do
										{
											printf("Ingrese fila donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].fila);
											printf("Ingrese columna donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].columna);

											}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

											// Funcion de ataque:
											p = play (campo,barco2Us,posUs,&statusCode);
											if (p == 2)
											{
													cantidadBarcos--;
											}
											break;

								case 3:	do
										{
											printf("Ingrese fila donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].fila);
											printf("Ingrese columna donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].columna);

											}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

											// Funcion de ataque:
											p = play (campo,barco3Us,posUs,&statusCode);
											if (p == 2)
											{
												cantidadBarcos--;
											}
											break;

								case 4:	do
										{
											printf("Ingrese fila donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].fila);
											printf("Ingrese columna donde desea realizar el ataque: ");
											scanf("%i",&posUs[0].columna);

										}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

										// Funcion de ataque:
											p = play (campo,barco4Us,posUs,&statusCode);
											if (p == 2)
											{
												cantidadBarcos--;
											}
										break;

							}
							print(campo,1,&statusCode);
						}while(cantidadBarcos!=0 && campo[0].cantBarcosUs!=0);

						if (cantidadBarcos == 0)
						{
							printf("\n");
							printf("\n");
							printf(" EL GANADOR ES USUARIO - FELICITACIONES !!! ");
							printf("\n");
							printf("\n");
						}

						if (campo[0].cantBarcosUs == 0)
						{
							printf("\n");
							printf("\n");
							printf(" EL GANADOR ES LA COMPUTADORA - VUELTA A INTENTARLO !!! ");
							printf("\n");
							printf("\n");
						}
					statusCode = OK;
					}

					else if(campo[0].nivel == 1)
					{
						cantidadBarcos = 4;
						do
						{
							// Escogimos el barco que va a realizar el ataque.
							printf( " Ingrese la opcion del barco que desea que realize el ataque \n");
							printf( " 1. %s \n",barco1Us[0].nombre);
							printf( " 2. %s \n",barco2Us[0].nombre);
							if(campo[0].cantBarcosUs >= 3){printf( " 3. %s \n",barco3Us[0].nombre);}
							if(campo[0].cantBarcosUs >= 4){printf( " 4. %s \n",barco4Us[0].nombre);}
							if(campo[0].cantBarcosUs >= 5){printf( " 5. %s \n",barco5Us[0].nombre);}

							scanf("%d",&opcion2);
							printf("\n");

							switch ( opcion2 )
							{
								case 1:	do
									{
										printf("Ingrese fila donde desea realizar el ataque: ");
										scanf("%i",&posUs[0].fila);
										printf("Ingrese columna donde desea realizar el ataque: ");
										scanf("%i",&posUs[0].columna);

									}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

									// Funcion de ataque:
									p = play (campo,barco1Us,posUs,&statusCode);
									if (p == 2)
									{
										cantidadBarcos--;
									}
									break;

								case 2:	do
									{
										printf("Ingrese fila donde desea realizar el ataque: ");
										scanf("%i",&posUs[0].fila);
										printf("Ingrese columna donde desea realizar el ataque: ");
										scanf("%i",&posUs[0].columna);

									}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

									// Funcion de ataque:
									p = play (campo,barco2Us,posUs,&statusCode);
									if (p == 2)
									{
										cantidadBarcos--;
									}
									break;

								case 3:	do
									{
										printf("Ingrese fila donde desea realizar el ataque: ");
										scanf("%i",&posUs[0].fila);
										printf("Ingrese columna donde desea realizar el ataque: ");
										scanf("%i",&posUs[0].columna);

									}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

									// Funcion de ataque:
									p = play (campo,barco3Us,posUs,&statusCode);
									if (p == 2)
									{
										cantidadBarcos--;
									}
									break;

								case 4:	do
								{
									printf("Ingrese fila donde desea realizar el ataque: ");
									scanf("%i",&posUs[0].fila);
									printf("Ingrese columna donde desea realizar el ataque: ");
									scanf("%i",&posUs[0].columna);

								}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

									// Funcion de ataque:
									p = play (campo,barco4Us,posUs,&statusCode);
									if (p == 2)
									{
										cantidadBarcos--;
									}
									break;

								case 5:	do
								{
									printf("Ingrese fila donde desea realizar el ataque: ");
									scanf("%i",&posUs[0].fila);
									printf("Ingrese columna donde desea realizar el ataque: ");
									scanf("%i",&posUs[0].columna);

								}while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

									// Funcion de ataque:
									p = play (campo,barco5Us,posUs,&statusCode);
									if (p == 2)
									{
										cantidadBarcos--;
									}
									break;

							}
						print(campo,1,&statusCode);
						}while(cantidadBarcos!=0 && campo[0].cantBarcosUs!=0);

						if (cantidadBarcos == 0)
						{
							printf("\n");
							printf("\n");
							printf(" EL GANADOR ES USUARIO - FELICITACIONES !!! ");
							printf("\n");
							printf("\n");
						}
						else if (campo[0].cantBarcosUs == 0)
						{
							printf("\n");
							printf("\n");
							printf(" EL GANADOR ES LA COMPUTADORA - VUELTA A INTENTARLO !!! ");
							printf("\n");
							printf("\n");
						}
					}

					else if (campo[0].nivel == 2)
                    {
                        do
                        {
                        // Escogimos el barco que va a realizar el ataque.
                        printf( " Ingrese la opcion del barco que desea que realize el ataque \n");
                        printf( " 1. %s \n",barco1Us[0].nombre);
                        printf( " 2. %s \n",barco2Us[0].nombre);
                        printf( " 3. %s \n",barco3Us[0].nombre);
                        if(campo[0].cantBarcosUs >= 4){printf( " 4. %s \n",barco4Us[0].nombre);}
                        if(campo[0].cantBarcosUs >= 5){printf( " 5. %s \n",barco5Us[0].nombre);}
                        if(campo[0].cantBarcosUs >= 6){printf( " 6. %s \n",barco6Us[0].nombre);}

                        scanf("%d",&opcion2);
                        printf("\n");

                        switch ( opcion2 )
                        {
                            case 1:	do
                                    {
                                        printf("Ingrese fila donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].fila);
                                        printf("Ingrese columna donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].columna);

                                    }while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

                                    // Funcion de ataque:
                                    p = play (campo,barco1Us,posUs,&statusCode);
                                    if (p == 2)
                                    {
                                        cantidadBarcos--;
                                    }
                                    break;

                            case 2:	do
                                    {
                                        printf("Ingrese fila donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].fila);
                                        printf("Ingrese columna donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].columna);

                                    }while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

                                    // Funcion de ataque:
                                    p = play (campo,barco2Us,posUs,&statusCode);
                                    if (p == 2)
                                    {
                                        cantidadBarcos--;
                                    }
                                    break;

                            case 3:	do
                                    {
                                        printf("Ingrese fila donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].fila);
                                        printf("Ingrese columna donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].columna);

                                    }while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

                                    // Funcion de ataque:
                                    p = play (campo,barco3Us,posUs,&statusCode);
                                    if (p == 2)
                                    {
                                        cantidadBarcos--;
                                    }
                                    break;
                            case 4:	do
                                    {
                                        printf("Ingrese fila donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].fila);
                                        printf("Ingrese columna donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].columna);

                                    }while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

                                    // Funcion de ataque:
                                    p = play (campo,barco4Us,posUs,&statusCode);
                                    if (p == 2)
                                    {
                                        cantidadBarcos--;
                                    }
                                    break;

                            case 5:	do
                                    {
                                        printf("Ingrese fila donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].fila);
                                        printf("Ingrese columna donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].columna);

                                    }while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

                                    // Funcion de ataque:
                                    p = play (campo,barco5Us,posUs,&statusCode);
                                    if (p == 2)
                                        {
                                            cantidadBarcos--;
                                        }
                                    break;

                            case 6:	do
                                    {
                                        printf("Ingrese fila donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].fila);
                                        printf("Ingrese columna donde desea realizar el ataque: ");
                                        scanf("%i",&posUs[0].columna);

                                    }while(posUs[0].fila > campo[0].fila || posUs[0].columna > (campo[0].columna/2) );

                                    // Funcion de ataque:
                                    p = play (campo,barco6Us,posUs,&statusCode);
                                    if (p == 2)
                                    {
                                        cantidadBarcos--;
                                    }
                                    break;
                        }
                        print(campo,1,&statusCode);
                        }while(cantidadBarcos!=0 && campo[0].cantBarcosUs!=0);

                        if (cantidadBarcos == 0)
                        {
                            printf("\n");
                            printf("\n");
                            printf(" EL GANADOR ES USUARIO - FELICITACIONES !!! ");
                            printf("\n");
                            printf("\n");
                        }
                        if (campo[0].cantBarcosUs == 0)
                        {
                            printf("\n");
                            printf("\n");
                            printf(" EL GANADOR ES LA COMPUTADORA - VUELTA A INTENTARLO !!! ");
                            printf("\n");
                            printf("\n");

                        }
                    }

					else
					{
						statusCode = FAIL;
						printf("No existe un tablero creado o cargado \n");
					}
					}

					break;


			case 8: printf(" * Autor: CRISTIAN EDUARDO ESPINOZA SILVA \n ");
					printf(" * Universidad santiago de chile \n");
					statusCode = OK;
					break;

		}
	}while(opcion!=9);

return 0;
}
