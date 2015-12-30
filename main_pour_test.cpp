#include <iostream>
#include <string>
#include "TexteEnrichis.h"


int main(int argc, char const *argv[])
{
	//std::string test=argv[1];
	TexteEnrichis Text(argv[1], 10);
	affiche(std::cout, Text);


	return 0;
}
