/*
 ============================================================================
 Name        : AbmPrimerParcial.c
 Author      : Bessio Rocio
 Division    : 1-A
 Fecha       : 11/05/22
 Tema        : MASCOTAS
 ============================================================================
 */
/* UNA VEZ QUE AGREGO LA ESTRUCTURA DEL RECUPERATORIO DE LA TENGO QUE PASAR A TODAS LAS FUNCIONES QUE TENGAN LA LISTA
 * (SORT, ALTA MASCOTA, MODIFICACION, BAJA, LISTAR MASCOTA, LISTAR UNICO)
 * DESPUES TENDRIA QUE EN ALTA MASCOTA LISTAR LA LISTA Y QUE INTRODUZCA A ID DEL DUE�O PARA ASIGNAR A LA MASCOTA
 * SI TIENE QUE APARECER EL NOMBRE DEL DUE�O SE DEBE DE CARGAR EL VECTOR, LO MISMO QUE CON LA DE SERVICIO
 * ESA ESTRUCTURA SE DEBE DE INICIALIZAR, BUSCAR REFERENCIA, BUSCAR LIBRE,LISTAR, HARCODEAR, ALTA Y CARGAR VECTOR
 *
 *
 */



#include <stdio.h>
#include <stdlib.h>

#include "eMascota.h"
#include  "utn.h"
#include "eFecha.h"
#include "eColor.h"
#include "tipo.h"

#include "trabajo.h"
#include "servicio.h"

#include "informes.h"


int menu();

int submenu(eMascota lista[],int tam,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo,eFecha fecha,eServicio servicioLista[],int tamServicio,eTrabajo listaTrabajo[],int tamTrabajo);

#define TAM 10 //TAM MASCOTAS

#define TAM_COLOR 5

#define TAM_TIPO 5

#define TAM_TRAB 10

#define TAM_SERV 3

int main(void) {
	setbuf(stdout,NULL);

	char salir = 'n';

	eMascota lista[TAM];

	eColor colorLista[TAM_COLOR] = {
			{5000,"NEGRO"},
			{5001,"BLANCO"},
			{5002,"ROJO"},
			{5003,"GRIS"},
			{5004,"AZUL"}
	};

	eTipo tipoLista[TAM_TIPO] ={
			{1000,"AVE"},
			{1001,"PERRO"},
			{1002,"ROEDOR"},
			{1003,"GATO"},
			{1004,"PEZ"},
	};

	eServicio servicioLista[TAM_SERV] = {
			{20000,"CORTE",450},
			{20001,"DESPARACITADO",800},
			{20002,"CASTRADO",600},

	};

	eTrabajo trabajoLista[TAM_TRAB];

	eFecha fecha;

	int idInicial = 1;

	int idTrabajoRandom = 2000;

	int bandera =1;

	//ACA VA LA INICIALIZACION
	inicializarEstructura(lista, TAM);
	inicializarEstructuraTrabajo(trabajoLista, TAM_TRAB);

	//HARDCODEOS
	hardcodeo(lista, TAM, &idInicial, 6);
	hardcodeoTrabajo(trabajoLista, TAM_TRAB, &idTrabajoRandom, 3);


	do
	{
		switch(menu())
		{
			case 1:
				//ALTA
				if(alta(lista, TAM,&idInicial, colorLista,TAM_COLOR,tipoLista,TAM_TIPO))
				{
					showMessage("\nALTA DE MASCOTA EXITOSA!");
					bandera=0;

				}
				else
				{
					showMessage("\nOCURRIO UN PROBLEMA CON EL SISTEMA!");
				}
			break;
			case 2:
				//BAJA
				if(bandera==1)
				{
					printf("NO HAY NINGUNA MASCOTA DENTRO DEL SISTEMA!");
				}
				else
				{
					baja(lista, TAM, &idInicial, colorLista,TAM_COLOR,tipoLista,TAM_TIPO);
				}
				system("Pause");
			break;
			case 3:
				//MODIFICACION
				if(bandera==1)
				{
					printf("NO HAY NINGUNA MASCOTA DENTRO DEL SISTEMA!");
				}
				else
				{
					modificacion(lista, TAM, &idInicial, colorLista,TAM_COLOR,tipoLista,TAM_TIPO);
				}
				system("Pause");
			break;
			case 4:
				sortByTipoYNombre(lista, TAM, &idInicial, colorLista, TAM_COLOR, tipoLista, TAM_TIPO);
				bandera=0;
				system("Pause");
			break;
			case 5:
				listarTipoMascota(tipoLista, TAM_TIPO);
				system("Pause");
			break;
			case 6:
				listarColor(colorLista, TAM_COLOR);
				system("Pause");
			break;
			case 7:
				listarServicio(servicioLista, TAM_SERV);
				system("Pause");
			break;
			case 8:
				//ALTA  TRABAJO
				if(bandera==1)
				{
					printf("\nNO SE DIO DE ALTA A NINGUNA MASCOTA!\n");
				}
				else
				{
					altaTrabajo(trabajoLista, TAM_TRAB, &idTrabajoRandom, lista, TAM, colorLista, TAM_COLOR, tipoLista, TAM_TIPO, servicioLista, TAM_SERV);
					showMessage("\nALTA DE TRABAJO EXITOSA!\n");
				}
				system("Pause");
			break;
			case 9:
				//LISTAR TRABAJO
				if(bandera==1)
				{
					printf("\nNO SE PUEDE LISTAR NO SE DIO DE ALTA AUN!\n");
				}
				else
				{
					listarTrabajos(trabajoLista, TAM_TRAB, lista, TAM, colorLista, TAM_COLOR, tipoLista, TAM_TIPO, servicioLista, TAM_SERV);
				}
				system("Pause");
			break;
			case 10:
				submenu(lista, TAM, colorLista, TAM_COLOR, tipoLista, TAM_TIPO, fecha, servicioLista, TAM_SERV, trabajoLista, TAM_TRAB);
			break;
			case 11:
				getUserConfirmation(&salir, "\nDESEA FINALIZAR EL PROGRAMA (S/N)?", "\nERROR, INGRESE UN VALOR VALIDO (S/N): ");
				if(salir=='s')
				{
					showMessage("\nPROGRAMA FINALIZADO....\n");
				}
				else
				{
					showMessage("\nFINALIZACION CANCELADA....\n");
				}
				system("Pause");
			break;
		}
	}while(salir!='s');

	return EXIT_SUCCESS;
}


int menu()
{
	int opcion;
	printf("\n\n\n\n");
	printf("\n____________________________________________________________");
	printf("\n                                                            |");
	printf("\n                VETERINARIA    MASCOTAS                     |\n");
	printf("____________________________________________________________|\n");
	printf("____________________________");
	printf("\n|1)ALTA MASCOTA            |\n|"
			"2)BAJA MASCOTA            |\n|"
			"3)MODIFICACION  MASCOTA   |\n|"
			"4)MOSTRAR LISTA MASCOTAS  |\n|"
			"5)LISTAR TIPOS            |\n|"
			"6)LISTAR COLORES          |\n|"
			"7)LISTAR SERVICIOS        |\n|"
			"8)ALTA TRABAJO            |\n|"
			"9)LISTAR TRABAJOS         |\n|"
			"10)INFORMES               |\n|"
			"11)SALIR                  |\n");
	printf("|__________________________|\n");
	getValidInt("INGRESE UN NUMERO: ", "\nERROR, REINGRESE UN NUMERO VALIDO.", "\nUNICAMENTE NUMEROS.", 1, 11, &opcion);


	return opcion;
}

int submenu(eMascota lista[],int tam,eColor colorMascota[],int tamColor,eTipo tipoLista[],int tamTipo,eFecha fecha,eServicio servicioLista[],int tamServicio,eTrabajo listaTrabajo[],int tamTrabajo)
{
	int todoOk =-1;
	int opcion;

	if(lista!=NULL && tam>0 && colorMascota!=NULL && tamColor>0 && tipoLista!=NULL && tamTipo>0 && servicioLista!=NULL && tamServicio>0 && listaTrabajo!=NULL && tamTrabajo>0)
	{
		printf("\n\n\n\n");
		printf("\n____________________________________________________________");
		printf("\n                                                            |");
		printf("\n       INFORMES    VETERINARIA    MASCOTAS                  |\n");
		printf("____________________________________________________________|\n");
		printf("____________________________");
		printf("\n|1)                        |\n|"
				"2)                        |\n|"
				"3)                        |\n|"
				"4)                        |\n|"
				"5)                        |\n|"
				"6)                        |\n|"
				"7)                        |\n|"
				"8)                        |\n|"
				"9)                        |\n|"
				"10)                       |\n|"
				"11)SALIR                  |\n");
		printf("|__________________________|\n");
		getValidInt("INGRESE UN NUMERO: ", "\nERROR, REINGRESE UN NUMERO VALIDO.", "\nUNICAMENTE NUMEROS.", 1, 11, &opcion);

		switch(opcion)
		{
			case 1:

				system("Pause");
			break;
			case 2:

				system("Pause");
			break;
			case 3:

				system("Pause");
			break;
			case 4:

				system("Pause");
			break;
			case 5:

				system("Pause");
			break;
			case 6:

				system("Pause");
			break;
			case 7:

				system("Pause");
			break;
			case 8:

				system("Pause");
			break;
			case 9:

				system("Pause");
			break;
			case 10:

				system("Pause");
			break;
			case 11:
				showMessage("\nSALIO DE INFORMES....\n");
				system("Pause");
			break;
		}
		todoOk=1;
	}

	return todoOk;
}
