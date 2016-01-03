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
	size_t CptChar;
	size_t TailleMot;
	bool balise_b, balise_i, balise_u, balise_verb, balise_blink, balise_rever;
	std::string ligne;
    std::string phrase;
    std::string MotDuTexte;
    std::string motBalise;
    bool Interrupt, FinLigne, FinFinal;

	

public:
	TexteEnrichis();
	TexteEnrichis(char*, size_t);
	TexteEnrichis(std::string, size_t);
	std::vector<std::string> getTab();
	size_t getNbLigne();
	
	void TraitementTexte();
private:
	void TraitementBaliseOuvrante();
	void TraitementBaliseFermante();
	
	void TraitementBaliseCouleur();

	void AnalyseString();

	//void LastVerifAvantTabStr(std::string&, size_t, const bool, const bool, const bool, const bool);

	void RajoutPhrase();

	//void Init_style();


};

void affiche(std::ostream&, TexteEnrichis&);

#endif
