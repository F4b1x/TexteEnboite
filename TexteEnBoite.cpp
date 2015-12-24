#include <sys/ioctl.h>
#include <cstdlib>
#include <iostream>

#include "TexteEnBoite.h"

TexteEnBoite::TexteEnBoite() : 
_margeIntG(1), _margeIntD(1),
_angleHG("/"), _angleHD("\\"), _angleBD("/"), _angleBG("\\"),
_bordH("-"), _bordD("|"), _bordB("-"), _bordG("|"), 
_separateur("-"), _angleSeparateurG("+"), _angleSeparateurD("+")
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	_largeur = w.ws_col;
	_hauteur = w.ws_row-1;
	std::cout<<"Hauteur :"<<w.ws_row<<"  Largeur :"<<w.ws_col<<std::endl;
}

void TexteEnBoite::affiche(std::ostream& flux)const
{
	system("cls");
	flux<<_angleHG;
	for (int i = 1; i < (_largeur-1); ++i)
	{
		flux<<_bordH;
	}
	flux<<_angleHD;
	for (int j = 1; j < (_hauteur-1); j++)
	{
		flux<<_bordG;
		for (int l = 1; l < (_largeur-1); l++)
		{
			flux<<" ";
		}
		flux<<_bordD<<std::endl;
	}
	flux<<_angleBG;
	for (int k = 1; k < (_largeur-1); k++)
	{
		flux<<_bordB;
	}
	flux<<_angleBD;
}


/*
TexteEnBoite::setAngle(char,char,char,char)
{

}

TexteEnBoite::setBordure(char,char,char,char)
{

}

TexteEnBoite::setSeparateur(char,char,char)
{

}

TexteEnBoite::setSize(unsigned int, unsigned int)
{

}

TexteEnBoite::setMarge(unsigned int,unsigned int)
{

}
*/


std::ostream& operator<<(std::ostream& flux, TexteEnBoite const& boite)
{
	boite.affiche(flux);
	return flux;
}