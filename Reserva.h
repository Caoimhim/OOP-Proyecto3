#ifndef RESERVA_H
#define RESERVA_H

#include "Fecha.h"

class Reserva
{
public:
	//Constructores
	Reserva();
	Reserva(int, int, Fecha);

	//setters
	void setIDMaterial(int);
	void setIDCliente(int);
	void setFechaReservacion(Fecha);
	
	//getters
	int getIDMaterial();
	int getIDCliente();
	Fecha getFechaReservacion();

	// otros metodos
	Fecha calculaFechaFinReserva(int);

	
private:
	int idMaterial;
	int idCliente;
	Fecha fechaReservacion;
	
};

//constructores
Reserva::Reserva()
{
	idMaterial = 0;
	idCliente = 0;
	fechaReservacion.setFecha(1, 1, 2000);
}

Reserva::Reserva(int idMat, int idCli, Fecha f)
{
	idMaterial = idMat;
	idCliente = idCli;
	fechaReservacion = f;
}

//setters
void Reserva::setIDMaterial(int id)
{
	idMaterial = id;
}
void Reserva::setIDCliente(int id)
{
	idCliente = id;
}
void Reserva::setFechaReservacion(Fecha f)
{
	fechaReservacion = f;
}

//getters
int Reserva::getIDMaterial()
{
	return idMaterial;
}
int Reserva::getIDCliente()
{
	return idCliente;
}
Fecha Reserva::getFechaReservacion()
{
	return fechaReservacion;
}

//otros metodos
Fecha Reserva::calculaFechaFinReserva(int cantDias)
{
	return fechaReservacion + cantDias;
}

#endif /* RESERVA_H */
