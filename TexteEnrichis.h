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

public:
	TexteEnrichis();
	TexteEnrichis(const char*, size_t);
	TexteEnrichis(const std::string, size_t);
	std::vector<std::string> getTab();
	size_t getNbLigne();
	



};

void affiche(std::ostream&, TexteEnrichis&);

#endif
