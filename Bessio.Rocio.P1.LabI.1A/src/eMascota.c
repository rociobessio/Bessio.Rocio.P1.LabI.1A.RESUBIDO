
#include "eMascota.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utn.h"
#include"eFecha.h"
#include "eColor.h"
#include "tipo.h"




int mostrarUnico(eMascota lista,int tam,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo)
{
	int todoOk =-1;

	char descripcionColor[50];
	char descripcionTipo[50];

	if(tam>0)
	{
		cargarVectorMascotaColor(colorMascota, tamColor, lista.idColor, descripcionColor);
		cargarTipoMascota(tipoLista, tamTipo, lista.idTipo, descripcionTipo);

		//EN CASO DE TENER OTRAS ENTIDAD SE DEBE DE HACER SU CARGA!
		printf("|%4d | %10s |  %10s    |%10s|         %c       | %2d     | \n",lista.id,
																							lista.nombre,
																							descripcionTipo,
																							descripcionColor,
																							lista.vacunado,
																							lista.edad);
		todoOk = 1;
	}

	return todoOk;
}


int listar(eMascota lista[],int tam,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo)
{
	int todoOk = -1;

	int bandera =0;

	if(lista!=NULL && tam>0)
	{
		printf("\n\n");
		showMessage("--------------------------------------------------------------------------|");
		showMessage("			 ***LISTADO DE MASCOTAS***                        | ");
		printf("|-------------------------------------------------------------------------|\n");
		showMessage("|  ID |	 NOMBRE    |	TIPO        |   COLOR  |      VACUNADO   | EDAD   |");
		printf("|-------------------------------------------------------------------------|\n");

		for(int i = 0;i<tam;i++)
		{
			if(!lista[i].isEmpty)
			{
				mostrarUnico(lista[i], tam,colorMascota,tamColor,tipoLista,tamTipo);
				bandera=1;
			}
		}
		printf("|-------------------------------------------------------------------------|\n");
		if(bandera==0)
		{
			showMessage("\nNO HAY MASCOTAS EN EL SISTEMA!");
		}

		todoOk = 0;
	}
	return todoOk;
}



int inicializarEstructura(eMascota lista[],int tam)
{
	int todoOk = -1;

	if(lista!=NULL && tam>0)
	{
		for(int i=0;i<tam;i++)
		{
			lista[i].isEmpty = 1;

			todoOk = 1;
		}
	}
	return todoOk;
}


int buscarLibre(eMascota lista[],int tam,int* pIndex)
{
	int todoOk = -1;

	if(lista!=NULL && tam>0 && pIndex!=NULL)
	{
		*pIndex= -1;
		for(int i=0;i<tam;i++)
		{
			if(lista[i].isEmpty)
			{
				*pIndex = i;
				break;
			}
			todoOk = 1;
		}
	}
	return todoOk;
}

int buscarReferencia(eMascota lista[],int tam,int* pIndex,int id)
{
	int todoOk = -1;

	if(lista!=NULL && tam>0 && pIndex!=NULL && id>0)
	{
		*pIndex= -1;
		for(int i=0;i<tam;i++)
		{
			if(!lista[i].isEmpty && lista[i].id == id)
			{
				*pIndex = i;
				break;
			}
			todoOk = 1;
		}
	}
	return todoOk;
}


int cargarNombreMascota(eMascota vec[],int tam,int id, char descripcion[])
{
	int todoOk =-1;

	int indice;
	//ACA SE LLAMA A BUSCAR: Y SE PASA EL INDICE
	buscarReferencia(vec, tam, &indice, id);

	if(vec!=NULL && tam>0 && descripcion!=NULL && indice!=-1)
	{
		for(int i=0;i<tam;i++)
		{
			strcpy(descripcion,vec[indice].nombre);
			todoOk =0;
		}
	}
	return todoOk;
}


int alta(eMascota lista[],int tam,int* pId,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo)
{
	int todoOk = 0;

	int indice;

	char auxCad[50];
	int auxInt;

	char confirmacion;

	eMascota auxMascota; //PONER BIEN EL NOMBRE


	//SE CREA UNA VARIABLE AUXILIAR

	if(lista!=NULL && tam>0 && pId!=NULL && colorMascota!=NULL && tamColor>0 && tipoLista!=NULL && tamTipo>0)
	{
		printf("\n____________________________________________________________");
		printf("\n                                                            |");
		printf("\n               ALTA     MASCOTAS                            |\n");
		printf("____________________________________________________________|\n");
		if(buscarLibre(lista, tam, &indice))
		{
			if(indice==-1)
			{
				showMessage("\nNO HAY MAS ESPACIO EN EL SISTEMA!");
			}
			else
			{
				//ENTRO Y CARGO
				getValidString("\nINGRESE NOMBRE DE LA MASCOTA: ", "\nERROR UNICAMENTE LETRAS: ", "\nINGRESE EN UN RANGO VALIDO: ", auxCad, 2, 20);
				strcpy(auxMascota.nombre,auxCad);

				listarColor(colorMascota, tamColor);
				getValidInt("\nINGRESE EL COLOR DE LA MASCOTA: ", "\nINGRESE UNA ID VALIDA.", "\nINGRESE UNICAMENTE NUMEROS: ", 5000, 5004, &auxInt);
				auxMascota.idColor = auxInt;

				listarTipoMascota(tipoLista, tamTipo);
				getValidInt("\nINGRESE EL TIPO DE MASCOTA: ", "\nESA ID NO ES VALIDA.", "\nINGRESE NUMEROS UNICAMENTE: ", 1000, 1004, &auxInt);
				auxMascota.idTipo = auxInt;

				getUserConfirmation(&confirmacion, "\nESTA VACUNADO (S/N): ", "\nVALOR INVALIDO,INGRESE (S/N): ");
				auxMascota.vacunado = confirmacion;

				getValidInt("\nINGRESE LA EDAD DE LA MASCOTA: ", "\nINGRESE UN VALOR VALIDO ", "\nINGRESE NUMEROS UNICAMENTE: ", 1, 20, &auxInt);
				auxMascota.edad = auxInt;

					//CAMBIO EL VALOR DE IS EMPTY
			         auxMascota.isEmpty = 0;

					//AUMENTO SU ID:
					auxMascota.id = *pId;
					*pId = (*pId)+1;

					//ACA VOY A COPIAR TODO LO DEL AUXILIR EN LA ORIGINAL
					lista[indice] = auxMascota;

				todoOk = 1;
			}
		}
		else
		{
			showMessage("\nOCURRIO UN PROBLEMA CON EL SISTEMA!!");
		}
	}
	return todoOk;
}

int baja(eMascota lista[],int tam,int* pId,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo)
{
	int todoOk;

	int indice;
	int idBuscada; //LUEGO SACAR EL 0

	char confirmacion;

	if(lista!=NULL && tam>0 && pId!=NULL)
	{
		printf("\n____________________________________________________________");
		printf("\n                                                            |");
		printf("\n               BAJA         MASCOTAS                        |\n");
		printf("____________________________________________________________|\n");
		//SE MUESTRA LA LISTA
		listar(lista, tam,colorMascota,tamColor,tipoLista,tamTipo);
		// SE PIDE LA ID A BUSCAR
		getValidInt("\nINGRESE LA ID A BUSCAR: ", "\nINGRESE UN VALOR VALIDO: ", "\nINGRESE NUMEROS UNICAMENTE: ", 1, 2000, &idBuscada);

		if(buscarReferencia(lista, tam, &indice, idBuscada))
		{
			if(indice==-1)
			{
				printf("\nNO SE ENCONTRO A NINGUNA MASCOTA CON ID Nº%d",idBuscada);
			}
			else
			{
				printf("\n\n");
				showMessage("--------------------------------------------------------------------------|");
				showMessage("			 ***LISTADO DE MASCOTAS***                        | ");
				printf("|-------------------------------------------------------------------------|\n");
				showMessage("|  ID |	 NOMBRE    |	TIPO        |   COLOR  |      VACUNADO   | EDAD   |");
				printf("|-------------------------------------------------------------------------|\n");
				mostrarUnico(lista[indice], tam,colorMascota,tamColor,tipoLista,tamTipo);
				printf("|-------------------------------------------------------------------------|\n");

				getUserConfirmation(&confirmacion, "\nDESEA DAR DE BAJA A LA MASCOTA (S/N)? ", "\nINGRESE VALOR VALIDO (S/N)? ");
				if(confirmacion =='s')
				{
					lista[indice].isEmpty = 1; //DEBE DE ESTAR EN 1
					printf("\nBAJA REALIZADA CON EXITO!\n");
				}
				else
				{
					printf("\nBAJA CANCELADA!");
				}
				todoOk=1;
			}
		}
	}
	return todoOk;
}

int modificacion(eMascota lista[],int tam,int* pId,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo)
{
	int todoOk;

	int indice;

	int idBuscada; //LUEGO SACAR EL 0

	char confirma;

	char opcion;

	int auxiliarMasco;

	if(lista!=NULL && tam>0 && pId!=NULL)
	{
		printf("\n____________________________________________________________");
		printf("\n                                                            |");
		printf("\n               MODIFICACION       MASCOTAS                  |\n");
		printf("____________________________________________________________|\n");
		//SE MUESTRA LA LISTA
		listar(lista, tam,colorMascota,tamColor,tipoLista,tamTipo);
		// SE PIDE LA ID A BUSCAR
		getValidInt("\nINGRESE LA ID A BUSCAR: ", "\nINGRESE UN VALOR VALIDO: ", "\nINGRESE NUMEROS UNICAMENTE: ", 1, 2000, &idBuscada);

		if(buscarReferencia(lista, tam, &indice, idBuscada))
		{
			if(indice==-1)
			{
				printf("\nNO SE ENCONTRO A NINGUNA MASCOTA CON ID Nº%d\n",idBuscada);
			}
			else
			{
				printf("\n\n\n\n");
				showMessage("--------------------------------------------------------------------------|");
				showMessage("			 ***LISTADO DE MASCOTAS***                        | ");
				printf("|-------------------------------------------------------------------------|\n");
				showMessage("|  ID |	 NOMBRE    |	TIPO        |   COLOR  |      VACUNADO   | EDAD   |");
				printf("|-------------------------------------------------------------------------|\n");
				mostrarUnico(lista[indice], tam,colorMascota,tamColor,tipoLista,tamTipo);
				printf("|-------------------------------------------------------------------------|\n");
				printf("\n\n");
				printf("____________________________");
				printf("\n|A)TIPO                    |\n|"
						"B)VACUNADO                |\n");
				printf("|__________________________|");
				printf("\nINGRESE QUE DESEA MODIFICAR: ");
				fflush(stdin);
				scanf("%c",&opcion);
				opcion= toupper(opcion);
				while(opcion!='A' && opcion!='B')
				{
					printf("\nERROR INGRESE UN VALOR VALIDO A/B: ");
					scanf("%c",&opcion);

				}
				switch(opcion)
				{
					case 'A':
						listarTipoMascota(tipoLista, tamTipo);
						getValidInt("\nINGRESE EL TIPO DE MASCOTA: ", "\nINGRESE UN NUMERO VALIDO: ", "\nINGRESE NUMEROS UNICAMENTE: ", 1000, 10004, &auxiliarMasco);
						getUserConfirmation(&opcion, "\nDESEA REALIZAR LA MODIFICACION DE LA MASCOTA? (S/N): ", "\nINGRESE VALOR VALIDO (S/N): ");
						if(opcion=='s')
						{
							lista[indice].idTipo = auxiliarMasco;
							printf("\nMODIFICACION DE MASCOTA REALIZADA CON EXITO!\n");
						}
						else
						{
							printf("\nMODIFICACION DE MASCOTA CANCELADA!\n");
						}
					break;
					case 'B':
						getUserConfirmation(&confirma, "\nESTA VACUNADO (S/N)?: ", "\nVALOR INVALIDO,INGRESE (S/N): ");

						getUserConfirmation(&opcion, "\nDESEA REALIZAR LA MODIFICACION DE LA MASCOTA? (S/N): ", "\nINGRESE VALOR VALIDO (S/N): ");
						if(opcion=='s')
						{
							lista[indice].vacunado = confirma;
							printf("\nMODIFICACION DE MASCOTA REALIZADA CON EXITO!\n");
						}
						else
						{
							printf("\nMODIFICACION DE MASCOTA CANCELADA!\n");
						}
					break;
				}
			todoOk=1;
			}
		}
	}
	return todoOk;
}

int hardcodeo(eMascota lista[],int tam,int* pId,int cant)
{
	int todoOk = -1;

	eMascota auxHarcodeo [] = {
			{000,1000,5002,"Salchicha",'s',5,0},//ID, TIPO, COLOR,NOMBRE,VACUNADO,EDAD,ISEMPTY
			{000,1001,5001,"Michi",'n',11,0},
			{000,1002,5000,"Nacho",'s',9,0},
			{000,1004,5003,"Lola",'n',7,0},
			{000,1000,5001,"Sasha",'s',8,0},
			{000,1001,5000,"Puddle",'n',4,0},
			{000,1004,5003,"Rocco",'s',1,0},
			{000,1002,5001,"Charly",'n',13,0},
			{000,1004,5002,"Almendra",'s',8,0}
	};


	if(lista!=NULL && tam>0 && pId!=NULL && cant>0 && cant<=tam )
	{
		for(int i=0;i<cant;i++)
		{
			lista[i] = auxHarcodeo[i];
			lista[i].id = *pId;
			*pId = *pId+1;
		}
		todoOk = 0;
	}


	return todoOk;
}

int sortByTipoYNombre(eMascota lista[],int tam,int* pId,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo)
{
	int todoOk = 0;
	eMascota auxMascota;


	if(lista!=NULL && tam>0)
	{
		for(int i = 0; i<tam;i++)
		{
			for(int j = i;j<tam;j++)
			{
				if(strcmp(lista[i].nombre,lista[j].nombre)>0)//ASC Z-A
				{
					auxMascota = lista[i];
					lista[i] = lista[j];
					lista[j] = auxMascota;
				}
				else if(strcmp(lista[i].nombre,lista[j].nombre)==0 && lista[i].idTipo>lista[j].idTipo)
				{
					auxMascota = lista[i];
					lista[i] = lista[j];
					lista[j] = auxMascota;
				}
			}
		}
	}
	listar(lista, tam, colorMascota, tamColor, tipoLista, tamTipo);

	return todoOk;
}

