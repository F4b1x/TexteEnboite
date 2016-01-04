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
	std::vector<std::string> OldColorFG;
	std::vector<std::string> OldColorBG;
	std::vector<std::string> Hist_Color;
	char* NomFichier;
	std::string Texte;
	size_t _n;
	size_t CptChar;
	size_t TailleMot;
	bool balise_b, balise_i, balise_u, balise_verb, balise_blink, balise_rever;
	bool balise_b_init, balise_i_init, balise_u_init, balise_verb_init, balise_blink_init, balise_rever_init;
	bool balise_center, balise_justify, balise_left, balise_right;
	bool balise_center_excpt, balise_justify_excpt, balise_left_excpt, balise_right_excpt; // Gérer les exceptions si une de ces balises se trouve en bout de ligne
	std::string ligne;
    std::string phrase;
    std::string MotDuTexte;
    std::string motBalise;
    bool Interrupt, FinLigne, FinFinal, PeutJustify;
    size_t AncienneTailleColor;
    std::string DerniereColor;


	

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

	void LastVerifAvantTabStr();

	void RajoutPhrase();

	void Init_style();
	void Remise_style(); // après un </color> si il faut revenir aux couleurs de bases
	void Remise_bool_Egal();


};

void affiche(std::ostream&, TexteEnrichis&);

#endif
