
#include "eColor.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int listarColor(eColor vec[],int tam)
{
	int todoOk =-1;

	if(vec!=NULL && tam>0)
	{
		printf("\n\n");
		//ACA SE PUEDE HACER UNA TABLITA O LISTA
		printf("\n------------------|");
		printf("\nLISTA DE COLORES  |\n");
		printf("------------------|\n");
		printf("ID    |DESCRIPCION|");
		printf("\n------------------|\n");
		for(int i=0;i<tam;i++)
		{
			printf(" %d | %10s|\n",vec[i].idColor, vec[i].descripcion);
		}
		printf("------------------|\n");
		todoOk = 0;
	}
	return todoOk;
}

int buscarIndice(eColor vec[],int tam,int id, int* pIndex)
{
	int todoOk = -1;

	if(vec!=NULL && tam>0 && pIndex !=NULL)
	{
		*pIndex = -1;

		for(int i=0;i<tam;i++)
		{
			if(vec[i].idColor == id)
			{
				*pIndex = i;
				break;
			}
		}
		todoOk=0;
	}

	return todoOk;
}


int cargarVectorMascotaColor(eColor vec[],int tam,int id, char descripcion[])
{
	int todoOk =-1;

	int indice;
	//ACA SE LLAMA A BUSCAR: Y SE PASA EL INDICE
	buscarIndice(vec, tam, id, &indice);

	if(vec!=NULL && tam>0 && descripcion!=NULL && indice!=-1)
	{
		for(int i=0;i<tam;i++)
		{
			strcpy(descripcion,vec[indice].descripcion);
			todoOk =0;
		}
	}
	return todoOk;
}


int validarColor(eColor vec[], int tam, int id)
{
	int indice;
	int esValido=0;

	buscarIndice(vec, tam, id, &indice);

	if(indice != -1) //SE FIJA SI ES VALIDO
	{
		esValido = 1;
	}

	return esValido;
}
