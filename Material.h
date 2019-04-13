#ifndef MATERIAL_H
#define MATERIAL_H

#include<iostream>
#include<string>
using namespace std;

class Material
{
public:
	Material();
	Material(int, string);

	void setIDMaterial(int);
	void setTitulo(string);

	int getIDMaterial();
	string getTitulo();

	virtual void muestra() = 0;
	virtual int cantidadDeDiasDePrestamo() = 0;
	
protected:
	int idMaterial;
	string titulo;
};

Material::Material()
{
	idMaterial = 0;
	titulo = "\0";
}
Material::Material(int id, string nom)
{
	idMaterial = id;
	titulo = nom;
}

void Material::setIDMaterial(int id)
{
	idMaterial = id;
}
void Material::setTitulo(string nom)
{
	titulo = nom;
}

int Material::getIDMaterial()
{
	return idMaterial;
}

string Material::getTitulo()
{
	return titulo;
}
#endif /* MATERIAL_H */
