#ifndef SOFTWARE_H
#define SOFTWARE_H

#include "Material.h"

class Software:public Material
{
public:
	Software();
	Software(int, string, string);

	void setSistemaOper(string);

	string getSistemaOper();

	void muestra();
	int cantidadDeDiasDePrestamo();
private:
	string sistemaOper;
};

Software::Software():Material()
{
	sistemaOper = "\0";
}
Software::Software(int id, string nom, string os):Material(id, nom)
{
	sistemaOper = os;
}

void Software::setSistemaOper(string os)
{
	sistemaOper = os;
}

string Software::getSistemaOper()
{
	return sistemaOper;
}

void Software::muestra()
{
	std::cout << "Software: "
		  << idMaterial << ' '
		  << titulo << ' '
		  << sistemaOper << endl;
}
int Software::cantidadDeDiasDePrestamo()
{
	return 1;
}


#endif /* SOFTWARE_H */
