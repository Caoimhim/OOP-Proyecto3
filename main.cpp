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

/* mostrarMaterias
   Muestra una lista de todas las materias en un arreglo
   Input: Un arreglo de materias y su tamaño
   Output: NONE
*/
void mostrarMaterias(Material *materiales[20], unsigned char cant)
{
	for (unsigned char i = 0; i < cant; ++i)
	{
		materiales[i]->muestra();
	}
	cout <<  endl;
}

/* getMaterialByID
   regresa pointer a material dada una ID
   Asume que la ID es valida
   Input: Un arreglo de materias con su tamaño
   Output: La materia con la ID especificada
*/
Material *getMaterialByID(int id, Material *materiales[20], unsigned char size)
{
	for (unsigned char i = 0; i < size; ++i)
	{
		if (id == materiales[i]->getIDMaterial())
		{
			return materiales[i];
		}
	}
	return nullptr;
}

/* mostrarReservas
   Muestra una lista de reservas
   Input: Un arreglo de reservas y materiales con sus tamaños
   Output: NONE
*/
void mostrarReservas(Reserva reservas[50], unsigned char cantRes, Material *materiales[20], unsigned char cantMat)
{
	for (unsigned char i = 0; i < cantRes; ++i)
	{
		cout << "Fecha de inicio: " << reservas[i].getFechaReservacion() << endl
		     << "Fecha de fin: " <<  reservas[i].calculaFechaFinReserva(
			     getMaterialByID(
				     reservas[i].getIDMaterial(), materiales, cantMat)->cantidadDeDiasDePrestamo()) << endl
		     << "Nombre: " << getMaterialByID(reservas[i].getIDMaterial(), materiales, cantMat)->getTitulo() << endl
		     << "ID de Cliente: " << reservas[i].getIDCliente() << endl;
		cout << endl;
	}
	cout << endl;
}
/* verifyID
   verifica que el ID de una materia existe
   Input: el ID a revisar, y el arreglo de materiales con su tamaño
   Output: Verdadero si lo encuentra, de lo contrario, falso
*/
bool verifyID(int id, Material *materiales[20], unsigned char cant)
{
	for (unsigned char i = 0; i < cant; ++i)
	{
		if (id == materiales[i]->getIDMaterial())
		{
			return true;
		}
	}
	return false;
}

/* mostrarReservasPorMaterial
   Muestra todas las reservas dados la id de un material
   Asume que la ID es válida
   Inputs: La ID del materia, el arreglo de reservas y de materiales con sus tamaños
   Output: NONE
*/
void mostrarReservasPorMaterial(int id, Reserva reservas[50], unsigned char cantRes, Material *materiales[20], unsigned char cantMat)
{
	bool found = false;
	for (unsigned char i = 0; i < cantRes; ++i)
	{
		if (id == reservas[i].getIDMaterial())
		{
			found = true;
			cout << "Nombre de material: "
			     << getMaterialByID(id, materiales, cantMat)->getTitulo() << endl
			     << "Fecha de inicio: "
			     << reservas[i].getFechaReservacion() << endl
			     << "Fecha de fin: " <<
				reservas[i].calculaFechaFinReserva(
					getMaterialByID(
						reservas[i].getIDMaterial(), materiales, cantMat)->cantidadDeDiasDePrestamo()) << endl;
					
		}
	}
	if (!found)
	{
		cout << "No se encontro ninguna reserva con ese material" << endl;
	}
}

/* validarFecha
   Revisa si en una fecha dada existe una reservacion por un material dado
   Inputs: La fecha a consutlar, la reserva a revisar, el arreglo de materiales y su tamaño
   Output: Verdadero of falso
*/
bool validarFecha(Fecha consulta, Reserva reserva, Material *materiales[20], unsigned char cantMat)
{
	
	Fecha revisando = reserva.getFechaReservacion();
	Fecha fin = reserva.calculaFechaFinReserva(getMaterialByID(reserva.getIDMaterial(), materiales, cantMat)->cantidadDeDiasDePrestamo());
	while (!(revisando == fin))
	{
		if (revisando == consulta)
		{
			return true;
		}
		revisando = revisando + 1;
	}

	return false;
}

/* mostrarMaterialPorFecha
   Muestra a la pantalla todos los materiales reservados en una fecha dada
   Input: La fecha a consultar, el arreglo de reservas y materiales con sus tamaños
   Output: NONE
*/
void mostrarMaterialesPorFecha(Fecha consulta, Reserva reservas[50], unsigned char cantRes, Material *materiales[20], unsigned char cantMat)
{
	bool found = false;
	for (unsigned char i = 0; i < cantRes; ++i)
	{
		if(validarFecha(consulta, reservas[i], materiales, cantMat))
		{
			found = true;
			cout << "Nombre: " << getMaterialByID(reservas[i].getIDMaterial(), materiales, cantMat)->getTitulo() << endl
			     << "ID de Cliente: " << reservas[i].getIDCliente();
		}
	}
	if (!found)
	{
		cout << "No hay reservas en esta fecha" << endl;
	}
}

/* crearReserva
   Pide al usuario los datos para crear una nueva reserva, y valida los datos
   Inputs: arreglos de materiales, y reservas con sus tamaños
   Outputs: Modifica el arreglo de reservas y su tamaño
*/
void crearReserva(Material *materiales[20], unsigned char cantMat, Reserva reservas[50], unsigned char &cantRes)
{
	int idCliente;
	int idMaterial;
	Fecha fecha;
	bool valido = false;
	cout << "Ente su ID de cliente: ";
	cin >> idCliente;
	cout << "Entre la ID del material que desea reservar: ";
	cin >> idMaterial;
	while (!verifyID(idMaterial, materiales, cantMat))
	{
		cout << "Este material no existe. Porfavor, entre in ID váldo: ";
		cin >> idMaterial;
	}
	
	cout << "Entre la fecha en la que desea reservar" << endl
	     << "DD MM AAAA" << endl;
	cin >> fecha; 

	while (!valido)
	{
		for (unsigned char i = 0; i < cantRes; ++i)
		{
			if (reservas[i].getIDMaterial() == idMaterial)
			{
				if (validarFecha(fecha, reservas[i], materiales, cantMat))
				{
					cout << "Este material ya esta reservado en esta fecha"	 << endl
					     << "Porfavor, entre otra fecha" << endl
					     << "DD MM AAAA" << endl;
					cin >> fecha;
				}
				else
				{
					valido = true;
				}
			}
		}
	}

	Reserva nuevaReserva(idMaterial, idCliente, fecha);
	reservas[cantRes++] = nuevaReserva;
}
/* menu
   Ofrece las opciones al usuario en la consola, y realiza las acciones apropiadas
   Input: El arreglo de materiales y reserva, con sus tamaños
   Output: Puede modificar los arreglos
*/
void menu(Material *materiales[20], unsigned char cantMat, Reserva reservas[50], unsigned char cantRes)
{
	Fecha consulta;
	char option;

	do 
	{
		cout << "(a) Consultar Materiales\n"
		     << "(b) Consultar lista de Reservaciones\n"
		     << "(c) Consultar reservaciones de un material\n"
		     << "(d) Consutlar la reservacion de una fecha\n"
		     << "(e) Hacer una reservación\n"
		     << "(f) Terminar" << endl;
		cin >> option;
		option = tolower(option);
		switch (option)
		{
		case 'a':
			cout << "Materiales" << endl;
			mostrarMaterias(materiales, cantMat);
			break;
		case 'b':
			cout << "Reservas" << endl;
			mostrarReservas(reservas, cantRes, materiales, cantMat);
			break;
		case 'c':
			int id;
			cout << "¿Qué material quisiera consultar?" << endl;
			cin >> id;
			while(!verifyID(id, materiales, cantMat))
			{
				cout <<  "La ID no es válida" << endl
				     << "Porfavor, entre una ID válido: ";
				cin >> id;
			}
			mostrarReservasPorMaterial(id, reservas, cantRes, materiales, cantMat);
			break;
		case 'd':
			cout << "¿Qué fecha quiera consultar?" << endl
			     << "DD MM AAAA" << endl;
			cin >> consulta;
			mostrarMaterialesPorFecha(consulta, reservas, cantRes, materiales, cantMat);
			
			break;
		case 'e':
			crearReserva(materiales, cantMat, reservas, cantRes);
			break;
		default:
		cout << "Porfavor, entre una opción válida\n";
		break;
	}
		cout << endl;
	} while(option !='f');
}

void actualizaReservas(Reserva reservas[50], unsigned char cant)
{
	ofstream fOut;
	fOut.open("Reserva.txt");

	for (unsigned char i = 0; i < cant; ++i)
	{
		fOut << reservas[i].getFechaReservacion().getDia() << ' '
		     << reservas[i].getFechaReservacion().getMes() << ' '
		     << reservas[i].getFechaReservacion().getAnno() << ' '
		     << reservas[i].getIDMaterial() << ' '
		     << reservas[i].getIDCliente() << endl;
	}
	fOut.close();
}
/* main
   LLama a las otras funciones
   Input: NONE
   Output: 0
*/
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

	//processing
	menu(materiales, cantidadMateriales, reservas, cantidadReservas);

	//output
	actualizaReservas(reservas, cantidadReservas);
	
	return 0;
}
