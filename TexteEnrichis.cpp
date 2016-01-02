#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include "TexteEnrichis.h"





TexteEnrichis::TexteEnrichis(): nbLigne(0), TabStr(0), OldColor(0), NomFichier(NULL), Texte(""), _n(0) {}
TexteEnrichis::TexteEnrichis(char* arg, size_t n): nbLigne(0), TabStr(0), OldColor(0), _n(n)
{
    std::ifstream fich(arg);

    if (!fich.is_open())
    {
        Texte = arg;
        std::cout<<"Texte : "<<Texte<<std::endl;
        NomFichier=NULL;
    }
    else
    {    
        NomFichier = arg;
        std::cout<<"NomFichier : "<<NomFichier<<std::endl;
        Texte="";
        fich.close();
    }
}

TexteEnrichis::TexteEnrichis(const std::string arg, size_t n): nbLigne(0), TabStr(0), OldColor(0), NomFichier(NULL), Texte(""), _n(0) 
{
    std::string ligne="";

    std::cout << "L'argument est un string" << std::endl;
    
    int i=0;
    std::string phrase="";
    while (i != arg.size())
    {
         
        if (arg[i] == '\n')
        {
            TabStr.push_back(phrase);
            nbLigne++;
            phrase="";
        }
        else
        {
            phrase += arg[i];
        }
        std::cout<<phrase<<";"<<std::endl;;
        i++;
    }
    TabStr.push_back(phrase);
    nbLigne++;
}

std::vector<std::string> TexteEnrichis::getTab()
{
	return TabStr;
}

size_t TexteEnrichis::getNbLigne()
{
    return nbLigne;
}

void TexteEnrichis::TraitementBaliseCouleur(std::string& phrase, std::string& motBalise)
{
    std::istringstream StringFlux(motBalise);
    std::string StrPart="";
    std::string couleur="";

    std::string CodeCouleurFG="",CodeCouleurBG="";

    while (StringFlux >> StrPart)
    {
        
        bool Foreground=false;
        if (StrPart[0]=='f')
        {
            if (StrPart[StrPart.size()-1]=='>')
                couleur=StrPart.substr(3,StrPart.size()-4);
            else
                couleur=StrPart.substr(3,StrPart.size()-3);
            std::cout<<"couleur : "<<couleur<<std::endl;
            Foreground=true;

        }
        else if (StrPart[0]=='b')
        {
            if (StrPart[StrPart.size()-1]=='>')
                couleur=StrPart.substr(3,StrPart.size()-4);
            else
                couleur=StrPart.substr(3,StrPart.size()-3);
            std::cout<<"couleur : "<<couleur<<std::endl;
        }

        if (couleur != "")
        {
            if (couleur == "black")
            {
                if (Foreground)
                {
                    phrase+="\033[30m";
                    CodeCouleurFG="\033[30m";
                }
                else
                {
                    phrase+="\033[40m";
                    CodeCouleurBG="\033[40m";
                }
            }
            if (couleur == "red")
            {
                if (Foreground)
                {
                    phrase+="\033[31m";
                    CodeCouleurFG="\033[30m";
                }
                else
                {    
                    phrase+="\033[41m";
                    CodeCouleurBG="\033[30m";
                }
            }
            if (couleur == "green")
            {
                if (Foreground)
                {    
                    phrase+="\033[32m";
                    CodeCouleurFG="\033[32m";
                }
                else
                {    
                    phrase+="\033[42m";
                    CodeCouleurBG="\033[42m";
                }
            }
            if (couleur == "yellow")
            {
                if (Foreground)
                {    
                    phrase+="\033[33m";
                    CodeCouleurFG="\033[33m";
                }
                else
                {    
                    phrase+="\033[43m";
                    CodeCouleurBG="\033[43m";
                }
            }
            if (couleur == "blue")
            {
                if (Foreground)
                {    
                    phrase+="\033[34m";
                    CodeCouleurFG="\033[34m";
                }
                else
                {    
                    phrase+="\033[44m";
                    CodeCouleurBG="\033[44m";
                }
            }
            if (couleur == "magenta")
            {
                if (Foreground)
                {    
                    phrase+="\033[35m";
                    CodeCouleurFG="\033[35m";
                }
                else
                {    
                    phrase+="\033[45m";
                    CodeCouleurBG="\033[45m";
                }
            }
            if (couleur == "cyan")
            {
                if (Foreground)
                {    
                    phrase+="\033[36m";
                    CodeCouleurFG="\033[36m";
                }
                else
                {    
                    phrase+="\033[46m";
                    CodeCouleurBG="\033[46m";
                }
            }
            if (couleur == "white")
            {
                if (Foreground)
                {    
                    phrase+="\033[37m";
                    CodeCouleurFG="\033[37m";
                }
                else
                {    
                    phrase+="\033[47m";
                    CodeCouleurBG="\033[47m";
                }
            }

        }
        

    }
    OldColor.push_back((CodeCouleurFG+CodeCouleurBG));
}




void TexteEnrichis::TraitementBalise()
{
    if (NomFichier != NULL) 
    {
        std::string ligne="";
        std::string phrase="";
        bool VerbatimActif = false;
    
    
        std::ifstream fich(NomFichier);
    
        if (!fich.is_open())
        {
            std::cout << "L'argument n'est pas un fichier" << std::endl;
            
            int i=0;
            
            
            while (Texte[i] != '\0')
            {
                std::cout<<Texte[i]<<std::endl;
                
                if (Texte[i] == '\n')
                {
                    TabStr.push_back(phrase);
                    nbLigne++;
                    phrase="";
                }
                else
                {
                    phrase += Texte[i];
                }
                std::cout<<phrase<<";"<<std::endl;;
                i++;
            }
            TabStr.push_back(phrase);
            nbLigne++;
    
        }
        else
        {
            std::cout<<"L'argument est un fichier"<<std::endl;
            
            while (!fich.eof()) 
            {
                getline(fich, ligne);
                int i=0;
                bool Interrupt=false;
                while ( i<ligne.size()+1)
                {
                    
                    if ( ligne[i] == '\0' )
                    {
                        
                        if (!Interrupt)
                        {
                            TabStr.push_back(phrase);
                            nbLigne+=1;
                        }
                        phrase="";
                        i++;
                        Interrupt=false;
    
                        
                    }
                    else
                    {
                        Interrupt=false;
                        if ( ligne[i] == '<')
                        {
                            bool BaliseFermante = false;
                            std::string motBalise="";
    
                            if ( ligne[i+1] == '/')
                            {
                                BaliseFermante = true;
                            }
    
                            motBalise+=ligne[i];
                            
                            do
                            {
                                i++;
                                motBalise+=ligne[i];
                                
    
                            } while (ligne[i] != '>');
    
    
                            std::cout<<"motBalise :"<<motBalise<<std::endl;

                            
    
                            if (motBalise == "<verbatim>")
                            {
                                VerbatimActif = true;
                                phrase+="";
                            }
    
                            else if ( motBalise == "</verbatim>")
                            {
                                VerbatimActif = false;
                                phrase+="";
                            }
    
                            else if ( !BaliseFermante && !VerbatimActif)
                            {
                                TraitementBaliseOuvrante(phrase, motBalise, Interrupt);
                                
                            }
    
                            else if (BaliseFermante && !VerbatimActif)
                            {
                                if(motBalise == "</b>")
                                {
                                    phrase+="\033[21m";
                                }
                                else if (motBalise == "</i>")
                                {
                                    phrase+="\033[23m";
                                }
                                else if (motBalise == "</u>")
                                {
                                    phrase+="\033[24m";
                                }
                                else if (motBalise == "</blink>")
                                {
                                    phrase+="\033[25m";
                                }
                                else if (motBalise == "</reverse>")
                                {
                                    phrase+="\033[27m";
                                }
                                else if (motBalise == "</p>")
                                {
                                    //ActionsSiValeurN;
                                }
                                else if (motBalise == "</color>")
                                {
                                    size_t taille = OldColor.size();
                                    if (taille == 1)
                                    {
                                        phrase+="\033[0m";
                                    }
                                    else if (taille > 1)
                                    {
                                        phrase+=OldColor[taille-2];
                                        OldColor.pop_back();
                                    }
                                }
                                else
                                {
                                    phrase+=motBalise;
                                }
                                
                            }
                            else if (VerbatimActif)
                            {
                                phrase+=motBalise;
                            }
    
                            i++;
                        }
                        else
                        {
                            phrase+=ligne[i];
                            i++;
                        }
                        //std::cout<<"Etat Interrupt"<<((Interrupt)?"1":"0")<<std::endl;
                    }
                    
                }
                
            }
            
            fich.close();
        }
    }
}

void TexteEnrichis::TraitementBaliseOuvrante(std::string& phrase, std::string& motBalise, bool& Interrupt)
{
    if(motBalise == "<b>" )
    {
        phrase+="\033[1m";
    }
    else if (motBalise == "<i>")
    {
        phrase+="\033[3m";
    }
    else if (motBalise == "<u>")
    {
        phrase+="\033[4m";
    }
    else if (motBalise == "<blink>")
    {
        phrase+="\033[5m";
    }
    else if (motBalise == "<reverse>")
    {
        phrase+="\033[7m";
    }
    else if (motBalise == "<p>")
    {
        //ActionsSiValeurN;
    }
    else if ((motBalise.substr(0,motBalise.size()-(motBalise.size()-6))) == "<color")
    {
        TraitementBaliseCouleur(phrase, motBalise);
        
    }
    else if (motBalise == "<br />" || motBalise == "<br/>" || motBalise == "<br>") // Manquer a gérer le nettoyage de la chaine d'après sur les espaces d'avant
    {
        TabStr.push_back(phrase);
        nbLigne+=1;
        Interrupt=true;
        phrase="";
    }
    else if (motBalise == "<hr />" || motBalise == "<hr/>" || motBalise == "<hr>")
    {
        TabStr.push_back(phrase);
        TabStr.push_back("<hr>");
        nbLigne+=2;
        Interrupt=true;
        phrase="";
    }
    else
    {
        phrase+=motBalise;
    }
}


/*void TexteEnrichis::TraitementBaliseFermante(std::string& phrase, std::string& motBalise)
{
    //
}*/




void affiche(std::ostream& os, TexteEnrichis& T)
{
    for (size_t i=0;i<T.getNbLigne()-1;i++)
        os<<T.getTab().at(i)<<std::endl;
    os<<T.getNbLigne()-1<<std::endl;
}
