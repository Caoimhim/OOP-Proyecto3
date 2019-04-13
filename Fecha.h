#ifndef FECHA_H
#define FECHA_H

#include <iostream>
using namespace std;

class Fecha
{
	friend ostream& operator<<(ostream &out, const Fecha &f);
	friend istream& operator>>(istream &in, Fecha &f);
public:
	//Constructores
	Fecha();
	Fecha(int, int, int);

	//setters
	void setDia(int);
	void setMes(int);
	void setAnno(int);

	//getters
	int getDia();
	int getMes();
	int getAnno();

	// Otros metodos
	void setFecha(int, int, int);

	//operadores
	Fecha operator+(int); //Suma días a la fecha
	bool operator>=(Fecha);
	bool operator<=(Fecha);
	bool operator>(Fecha);
	bool operator<(Fecha);
	bool operator==(Fecha);
	
	
private:
	int dd, mm, aa;

	string nombreMes() const;
	bool esBisiesto();
	bool diaValido(int);
	int maxDiaValido();
	
};

//Constructores
Fecha::Fecha()
{
	dd = 0;
	mm = 0;
	aa = 0;
}
Fecha::Fecha(int d, int m, int a)
{
	dd = d;
	mm = m;
	aa = a;
}

//setters
void Fecha::setDia(int d)
{
	dd = d;
}
void Fecha::setMes(int m)
{
	mm = m;
}
void Fecha::setAnno(int a)
{
	aa = a;
}

//getters
int Fecha::getDia()
{
	return dd;
}
int Fecha::getMes()
{
	return mm;
}
int Fecha::getAnno()
{
	return aa;
}

//other methods
void Fecha::setFecha(int d, int m, int a)
{
	dd = d;
	mm = m;
	aa = a;
}
string Fecha::nombreMes() const
{
	switch (mm)
	{
	case 1:
		return "Ene";
	case 2:
		return "Feb";
	case 3:
		return "Mar";
	case 4:
		return "Abr";
	case 5:
		return "May";
	case 6:
		return "Jun";
	case 7:
		return "Jul";
	case 8:
		return "Ago";
	case 9:
		return "Sep";
	case 10:
		return "Oct";
	case 11:
		return "Nov";
	case 12:
		return "Dec";
	}
	return "NULL";
}
bool Fecha::esBisiesto()
{
	if ((aa % 4 == 0 && (aa % 10 != 0)) || (aa % 400 == 0))
	{
		return true;
	}
	return false;
}

bool Fecha::diaValido(int d)
{
	switch (mm)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31 >= d;
	case 2:
		if (this->esBisiesto())
		{
			return 29 >= d;
		}
		return 28 >= d;
	default:
		return 30 >= d;
	}
}

int Fecha::maxDiaValido()
{
	switch (mm)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 2:
		if (this->esBisiesto())
		{
			return 29;
		}
		return 28;
	default:
		return 30;
	}
}
//operadores
Fecha Fecha::operator+(int i)
{
	int newDay = dd + i;
	Fecha ans = *this;
	while (!ans.diaValido(newDay))
	{
		newDay -= ans.maxDiaValido();
		ans.mm++;
		if (ans.mm == 13)
		{
			ans.mm = 1;
			ans.aa++;
		}
	}

	ans.dd = newDay;
	return ans;
}

bool Fecha::operator>=(Fecha other)
{
	return (*this > other || *this == other);
}

bool Fecha::operator<=(Fecha other)
{
	return (*this < other || *this == other);
}

bool Fecha::operator>(Fecha other)
{
	if (this->aa > other.aa)
	{
		return true;
	}
	else if (this->aa == other.aa)
	{
		if (this->mm > other.mm)
		{
			return true;
		}
		else if (this->mm == other.mm)
		{
			if(this->dd > other.dd)
			{
				return true;
			}
		}
	}
	return false;
}
		
bool Fecha::operator<(Fecha other)
{
	return !(*this > other);
}

bool Fecha::operator==(Fecha other)
{
	if (this->aa == other.aa &&
		this->mm == other.mm &&
		this->dd == other.dd)
	{
		return true;
	}
	return false;
}

ostream& operator<<(ostream &out, const Fecha &f)
{
	out << f.dd << '/' << f.nombreMes() << '/' << f.aa;
	return out;
}

istream& operator>>(istream &in, Fecha &f)
{
	in >> f.dd >> f.mm >> f.aa;
	return in;
}

#endif /* FECHA_H */
