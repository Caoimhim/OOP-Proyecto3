#include <iostream>
using namespace std;

#include "Fecha.h"
#include "Reserva.h"
#include "Material.h"
#include "Libro.h"
#include "Disco.h"
#include "Software.h"

int main()
{
	Material *materiales[20];
	unsigned char cantidadMateriales;
	Reserva *reservas[50];
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
	
	return 0;
}
