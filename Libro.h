#ifndef LIBRO_H
#define LIBRO_H

#include "Material.h"

class Libro : public Material
{
public:
	Libro();
	Libro(int, string, int, string);

	void setNumPag(int);
	void setAutor(string);

	int getNumPag();
	string getAutor();

	void muestra();
	int cantidadDeDiasDePrestamo();
private:
	int numPag;
	string autor;
};

Libro::Libro():Material()
{
	numPag = 0;
	autor = "\0";
}
Libro::Libro(int id, string nom, int pgs, string aut):Material(id, nom)
{
	numPag = pgs;
	autor = aut;
}

void Libro::setNumPag(int pgs)
{
	numPag = pgs;
}
void Libro::setAutor(string aut)
{
	autor = aut;
}

int Libro::getNumPag()
{
	return numPag;
}
string Libro::getAutor()
{
	return autor;
}

void Libro::muestra()
{
	cout << "Libro: "
	     << idMaterial << " "
	     << titulo << " "
	     << numPag << " "
	     << autor << endl;
}

int Libro::cantidadDeDiasDePrestamo()
{
	return 10;
}

#endif /* LIBRO_H */
