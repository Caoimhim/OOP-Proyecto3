#include <iostream>
#include <fstream>
using namespace std;

#include "Fecha.h"
#include "Reserva.h"
#include "Material.h"
#include "Libro.h"
#include "Disco.h"
#include "Software.h"

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

	// menu();
	
	return 0;
}
