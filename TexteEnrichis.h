#ifndef TEXTEENRICHIS_H
#define TEXTEENRICHIS_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

class TexteEnrichis
{

private:
	size_t nbLigne;
	std::vector<std::string> TabStr;
	std::vector<std::string> OldColor;
	char* NomFichier;
	std::string Texte;
	size_t _n;

	

public:
	TexteEnrichis();
	TexteEnrichis(char*, size_t);
	TexteEnrichis(std::string, size_t);
	std::vector<std::string> getTab();
	size_t getNbLigne();
	
	void TraitementBalise();
private:
	void TraitementBaliseOuvrante(std::string&, std::string&, bool&);
	//void TraitementBaliseFermante(std::string&, std::string&, bool&);
	
	void TraitementBaliseCouleur(std::string&, std::string&);


};

void affiche(std::ostream&, TexteEnrichis&);

#endif
