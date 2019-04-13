#include <iostream>
#include <fstream>
using namespace std;

#include "Fecha.h"
#include "Reserva.h"
#include "Material.h"
#include "Libro.h"
#include "Disco.h"
#include "Software.h"

/* cargaMateriales
   Lee información de materiales de Material.txt
   Input: El arreglo de materiales y su tamaño
   Output: Escribe al arreglo de materiales y modifica su tamaño
   Regresa falso si no encuentra el archivo de los materiales
*/
bool cargaMateriales(Material *materiales[20], unsigned char &cant)
{
	ifstream inFile;
	cant = 0;
	inFile.open("Material.txt");
	if (!inFile.is_open())
	{
		return false;
	}
	int id;
	string tit;
	char type;
	while (inFile >> id)
	{
		inFile >> tit;
		inFile >> type;

		if (type == 'L')
		{
			int pgs;
			string aut;
			inFile >> pgs;
			inFile >> aut;

			Libro *temp;
			temp = new Libro(id, tit, pgs, aut);
			materiales[cant++] = temp;
		}
		else if (type == 'D')
		{
			int dur;
			inFile >> dur;
			Disco *temp;
			temp = new Disco(id, tit, dur);
			materiales[cant++] = temp;
		}
		else if (type == 'S')
		{
			string os;
			inFile >> os;
			Software *temp;
			temp = new Software(id, tit, os);
			materiales[cant++] = temp;
		}
	}

	inFile.close();
	return true;
}

/* cargaReservas
   Lee de y guarda información de reservas de Reservas.txt
   Input: arreglo de reservas y su tamaño
   Output: Escribo al arreglo de reservas y su tamaño.
   Regresa falso si no se encuentra el archivo
*/
bool cargaReservas(Reserva reservas[50], unsigned char &cant)
{
	ifstream inFile;
	cant = 0;
	inFile.open("Reserva.txt");
	if (!inFile.is_open())
	{
		return false;
	}

	int d, m, a;
	int idMat;
	int idCli;
	while (inFile >> d >> m >> a >> idMat >> idCli)
	{
		Fecha f(d, m, a);
		reservas[cant].setFechaReservacion(f);
		reservas[cant].setIDCliente(idCli);
		reservas[cant++].setIDMaterial(idMat);
	}
	
	inFile.close();
	return true;
}

/* menu
   Ofrece las opciones al usuario en la consola, y realiza las acciones apropiadas
   Input: El arreglo de materiales y reserva, con sus tamaños
   Output: Puede modificar los arreglos
*/
void menu(Material *materiales[20], unsigned char cantMat, Reserva reservas[50], unsigned char cantRes)
{
	char option;

	do 
	{
		cout << "(a) Consultar Materiales\n"
		     << "(b) Consultar lista de Reservaciones\n"
		     << "(c) Consultar reservaciones de un material\n"
		     << "(d) Consutlar la reservacion de una fecha\n"
		     << "(e) Hacer una reservación\n"
		     << "(f) Terminar";
		cin >> option;
		tolower(option);
		switch (option)
		{
		case 'a':
			cout << "Materiales" << endl;
			for (unsigned char i = 0; i < cantMat; ++i)
			{
				materiales[i]->muestra();
			}
			cout <<  endl;
			break;
		case 'b':
			cout << "Reservas" << endl;
			cout << "Material ID\tClienteID\tFecha" << endl;
			for (unsigned char i = 0; i < cantRes; ++i)
			{
				cout << reservas[i].getIDMaterial() << '\t'
				     << reservas[i].getIDCliente() << '\t'
				     << reservas[i].getFechaReservacion() << endl;
			}
			break;
		case 'c':
		break;
	case 'd':
		break;
	case 'e':
		break;
	default:
		cout << "Porfavor, entre una opción válida\n";
		break;
	}
	} while(option !='f');
}
int main()
{
	Material *materiales[20];
	unsigned char cantidadMateriales;
	Reserva reservas[50];
	unsigned char cantidadReservas;

	//Input
	if(!cargaMateriales(materiales, cantidadMateriales))
	{
		cout << "No se encontro el archivo de materiales" << endl;
		return 0;
	}

	if(!cargaReservas(reservas, cantidadReservas))
	{
		cout << "No se encontro el archvo de reservas" << endl;
		return 0;
	}

	menu(materiales, cantidadMateriales, reservas, cantidadReservas);
	
	return 0;
}
