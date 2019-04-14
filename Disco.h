#ifndef DISCO_H
#define DISCO_H

#include "Material.h"

class Disco:public Material
{
public:
	Disco();
	Disco(int, string, int);

	void setDuracion(int);
	
	int getDuracion();

	void muestra();
	int cantidadDeDiasDePrestamo();
private:
	int duracion;
	
};

Disco::Disco():Material()
{
	duracion = 0;
}
Disco::Disco(int id, string nom, int dur):Material(id, nom)
{
	duracion = dur;
}

void Disco::setDuracion(int dur)
{
	duracion = dur;
}
int Disco::getDuracion()
{
	return duracion;
}

void Disco::muestra()
{
	std::cout << "Disco: "
		  << idMaterial << ' '
		  << titulo << ' '
		  << duracion << endl;
}
int Disco::cantidadDeDiasDePrestamo()
{
	return 3;
}

#endif /* DISCO_H */
