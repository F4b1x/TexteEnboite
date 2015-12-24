#ifndef TEXTE_EN_BOITE
#define TEXTE_EN_BOITE

#include <iostream>
#include <string>

class TexteEnBoite
{
public:
	TexteEnBoite();

	//Setters
	void setAngle(char,char,char,char);
	void setBordure(char,char,char,char);
	void setSeparateur(char,char,char);
	void setSize(unsigned int, unsigned int);
	void setMarge(unsigned int,unsigned int);

	void affiche(std::ostream& )const;
	


private:
	std::string _texte;
	std::string _angleHG, _angleHD, _angleBD, _angleBG;
	std::string _bordH, _bordD, _bordB, _bordG;
	std::string _separateur, _angleSeparateurG, _angleSeparateurD;
	unsigned int _largeur, _hauteur, _margeIntG, _margeIntD;

};

std::ostream& operator<<(std::ostream&, TexteEnBoite const&);



#endif