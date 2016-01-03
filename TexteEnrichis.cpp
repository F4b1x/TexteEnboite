#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include "TexteEnrichis2.h"





TexteEnrichis::TexteEnrichis(): nbLigne(0), TabStr(0), OldColor(0), NomFichier(NULL), Texte(""), _n(0), CptChar(0), TailleMot(0), balise_b(false), balise_i(false), balise_u(false), balise_verb(false), balise_blink(false), balise_rever(false), phrase(""), MotDuTexte(""), motBalise(""), ligne(""), Interrupt(false), FinLigne(false), FinFinal(false), balise_center(false), balise_justify(false), balise_left(false), balise_right(false), AncienneTailleColor(0), DerniereColor("\033[0m") {}
TexteEnrichis::TexteEnrichis(char* arg, size_t n): nbLigne(0), TabStr(0), OldColor(0), _n(n), CptChar(0), TailleMot(0), balise_b(false), balise_i(false), balise_u(false), balise_verb(false), balise_blink(false), balise_rever(false), phrase(""), MotDuTexte(""), motBalise(""), ligne(""), Interrupt(false), FinLigne(false), FinFinal(false), balise_center(false), balise_justify(false), balise_left(false), balise_right(false), AncienneTailleColor(0), DerniereColor("\033[0m")
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

TexteEnrichis::TexteEnrichis(const std::string arg, size_t n): nbLigne(0), TabStr(0), OldColor(0), NomFichier(NULL), Texte(arg), _n(0), CptChar(0), TailleMot(0), balise_b(false), balise_i(false), balise_u(false), balise_verb(false), balise_blink(false), balise_rever(false), phrase(""), MotDuTexte(""), motBalise(""), ligne(arg), Interrupt(false), FinLigne(false), FinFinal(false), balise_center(false), balise_justify(false), balise_left(false), balise_right(false), AncienneTailleColor(0), DerniereColor("\033[0m")
{
    std::cout << "L'argument est un string" << std::endl;
}

std::vector<std::string> TexteEnrichis::getTab()
{
	return TabStr;
}

size_t TexteEnrichis::getNbLigne()
{
    return nbLigne;
}

void TexteEnrichis::TraitementBaliseCouleur()
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
                    MotDuTexte+="\033[30m";
                    CodeCouleurFG="\033[30m";
                }
                else
                {
                    MotDuTexte+="\033[40m";
                    CodeCouleurBG="\033[40m";
                }
            }
            if (couleur == "red")
            {
                if (Foreground)
                {
                    MotDuTexte+="\033[31m";
                    CodeCouleurFG="\033[30m";
                }
                else
                {    
                    MotDuTexte+="\033[41m";
                    CodeCouleurBG="\033[30m";
                }
            }
            if (couleur == "green")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[32m";
                    CodeCouleurFG="\033[32m";
                }
                else
                {    
                    MotDuTexte+="\033[42m";
                    CodeCouleurBG="\033[42m";
                }
            }
            if (couleur == "yellow")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[33m";
                    CodeCouleurFG="\033[33m";
                }
                else
                {    
                    MotDuTexte+="\033[43m";
                    CodeCouleurBG="\033[43m";
                }
            }
            if (couleur == "blue")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[34m";
                    CodeCouleurFG="\033[34m";
                }
                else
                {    
                    MotDuTexte+="\033[44m";
                    CodeCouleurBG="\033[44m";
                }
            }
            if (couleur == "magenta")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[35m";
                    CodeCouleurFG="\033[35m";
                }
                else
                {    
                    MotDuTexte+="\033[45m";
                    CodeCouleurBG="\033[45m";
                }
            }
            if (couleur == "cyan")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[36m";
                    CodeCouleurFG="\033[36m";
                }
                else
                {    
                    MotDuTexte+="\033[46m";
                    CodeCouleurBG="\033[46m";
                }
            }
            if (couleur == "white")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[37m";
                    CodeCouleurFG="\033[37m";
                }
                else
                {    
                    MotDuTexte+="\033[47m";
                    CodeCouleurBG="\033[47m";
                }
            }

        }
        

    }
    OldColor.push_back((CodeCouleurFG+CodeCouleurBG));
    DerniereColor=(CodeCouleurFG+CodeCouleurBG);
    AncienneTailleColor++;
}




void TexteEnrichis::TraitementTexte()
{



    if (NomFichier != NULL) 
    {
        std::ifstream fich(NomFichier);
    
        if (!fich.is_open())
        {
            std::cout << "Le fichier ne s'est pas ouvert" << std::endl;
        }
        else
        {
            std::cout<<"L'argument est un fichier"<<std::endl;
            
            while (!fich.eof()) 
            {
                getline(fich, ligne);
                AnalyseString();
                
            }
            FinFinal=true;
            
            //std::cout<<" CptChar à la fin du while : "<<CptChar<<std::endl;
            if ( CptChar != 0)
            {
                RajoutPhrase();
            }

            fich.close();
        }
    }
    else
    {
        std::cout<<"L'argument n'est pas un fichier"<<std::endl;
        ligne=Texte;
        AnalyseString();
        FinFinal=true;
        if ( CptChar != 0)
        {
            RajoutPhrase();
        }
    }
}

void TexteEnrichis::TraitementBaliseOuvrante()
{
    if(motBalise == "<b>" )
    {
        
        MotDuTexte+="\033[1m";
        balise_b=true;
        
    }
    else if (motBalise == "<i>")
    {
        
        MotDuTexte+="\033[3m";
        balise_i=true;
        
    }
    else if (motBalise == "<u>")
    {
        
        MotDuTexte+="\033[4m";
        balise_u=true;
        
    }
    else if (motBalise == "<blink>")
    {
        
        MotDuTexte+="\033[5m";
        balise_blink=true;
        
    }
    else if (motBalise == "<reverse>")
    {
        
        MotDuTexte+="\033[7m";
        balise_rever=true;
        
    }
    else if (motBalise == "<p>")
    {
        //ActionsSiValeurN;
    }
    else if ((motBalise.substr(0,motBalise.size()-(motBalise.size()-6))) == "<color")
    {
        TraitementBaliseCouleur();
        
        
    }
    else if (motBalise == "<br />" || motBalise == "<br/>" || motBalise == "<br>") // Manquer a gérer le nettoyage de la chaine d'après sur les espaces d'avant
    {
        FinLigne=true;
        RajoutPhrase();
        /*TabStr.push_back(phrase);
        MotDuTexte="";
        phrase="";
        CptChar=0;
        TailleMot=0;*/
        
        
        //Interrupt=true;
    }
    else if (motBalise == "<hr />" || motBalise == "<hr/>" || motBalise == "<hr>")
    {
        MotDuTexte+="";
        RajoutPhrase();
        MotDuTexte+="<hr>";
        RajoutPhrase();
        //Interrupt=true;
    }
    else
    {
        TailleMot+= motBalise.size();
        MotDuTexte+=motBalise;
    }
}


void TexteEnrichis::TraitementBaliseFermante()
{
    if(motBalise == "</b>")
    {
        MotDuTexte+="\033[21m";
        balise_b=false;
        
    }
    else if (motBalise == "</i>")
    {
        
        MotDuTexte+="\033[23m";
        balise_i=false;
        
    }
    else if (motBalise == "</u>")
    {
        
        MotDuTexte+="\033[24m";
        balise_u=false;
        
    }
    else if (motBalise == "</blink>")
    {
        
        MotDuTexte+="\033[25m";
        balise_blink=false;
        
    }
    else if (motBalise == "</reverse>")
    {
        
        MotDuTexte+="\033[27m";
        balise_rever=false;
        
    }
    else if (motBalise == "</p>")
    {
        //ActionsSiValeurN;
    }
    else if (motBalise == "</color>")
    {
        size_t taille = OldColor.size();
        //std::cout<<"taille : "<<taille<<std::endl;

        if (taille == 1)
        {
            MotDuTexte+="\033[0m";
            OldColor.pop_back();
            
        }
        else if (taille > 1)
        {
            MotDuTexte+=OldColor[taille-2];
            OldColor.pop_back();
        }
    }
    else
    {
        TailleMot+=motBalise.size();
        RajoutPhrase();
    }
}

void TexteEnrichis::AnalyseString()
{



    int i=0;

    while ( i<ligne.size()+1)
    {
        //std::cout<<"i : "<<i<<std::endl;
        /*if ( ligne[i] == '\0')
        {   
            FinLigne = true;
            RajoutPhrase(MotDuTexte, phrase, Interrupt, FinLigne);
            i++;
        }*/
        //else
        //{
        bool Balise = false;
        Interrupt=false;
        if ( ligne[i] == '<')
        {
            Balise=true;

            bool BaliseFermante = false;
            
            motBalise="";

            if ( ligne[i+1] == '/')
            {
                BaliseFermante = true;
            }
            else if ( ligne[i+1] == ' ' )
            {
                Balise = false;
            }

            if (Balise)
            {
                motBalise+=ligne[i];
                
                do
                {
                    i++;
                    motBalise+=ligne[i];
                    

                } while (ligne[i] != '>');


                std::cout<<"motBalise :"<<motBalise<<std::endl;

                

                if (motBalise == "<verbatim>")
                {
                    balise_verb = true;
                }

                else if ( motBalise == "</verbatim>")
                {
                    balise_verb = false;
                }

                else if ( !BaliseFermante && !balise_verb)
                {
                    TraitementBaliseOuvrante();
                    
                }

                else if (BaliseFermante && !balise_verb)
                {
                    TraitementBaliseFermante();
                    
                }
                else if (balise_verb)
                {
                    RajoutPhrase();
                }
                
                i++;
            }
            //}
        }  
            
        if (ligne[i]!=' ' && ligne[i]!='\0' && !Balise)
        {
            MotDuTexte+=ligne[i];
            //std::cout<<"Mot du Texte : "<<MotDuTexte<<"\t";
            TailleMot++;
            //std::cout<<"TailleMot : "<<TailleMot<<"\t";
            i++;
        }
        else if ( ligne[i] == ' ' || ligne[i]=='\0')
        {
            if ( TailleMot != 0)
                RajoutPhrase();
            i++;
        }
        
    }

}

void TexteEnrichis::RajoutPhrase()
{
    //std::cout<<"CptCharAvant : "<<CptChar<<std::endl;

    if ( CptChar != 0)
    {
        TailleMot++;
    }


    if ( TailleMot + CptChar <= _n && !FinLigne && !FinFinal)
    {
        //std::cout<< " Quel if dans le RajoutPhrase : 1"<<std::endl;
        if ( CptChar == 0)
        {
            phrase+=MotDuTexte;
        }
        else
        {
            phrase+=" "+MotDuTexte;
        }

        CptChar+= TailleMot;
        
        TailleMot=0;
        MotDuTexte="";

    }


    else if ( TailleMot + CptChar <= _n && FinLigne && !FinFinal)
    {
        //std::cout<< " Quel if dans le RajoutPhrase : 2"<<std::endl;
        if ( CptChar == 0)
        {
            phrase+=MotDuTexte;
        }
        else
        {
            phrase+=" "+MotDuTexte;
        }
        
        
        size_t tailleOldColor = OldColor.size();
        if (tailleOldColor > 0)
        {
            phrase+="\033[0m";
        }

        TabStr.push_back(phrase);
        nbLigne+=1;

        if ( tailleOldColor > 0 )
        {
            phrase=""+OldColor.back();
        }
        else
            phrase="";

        CptChar=0;
        Interrupt=false;
        TailleMot=0;
        MotDuTexte="";
        FinLigne=false;
    }


    else if (TailleMot + CptChar > _n && !FinLigne && !FinFinal)
    {
        //std::cout<< " Quel if dans le RajoutPhrase : 3"<<std::endl;
        if (!Interrupt)
        {
            TailleMot--;
            size_t tailleOldColor = OldColor.size();

            //std::cout<<"Taille du tableau Color : "<<tailleOldColor<<std::endl;
            //std::cout<<"Etat FinLigne"<<std::endl;

            phrase+="\033[0m";

            TabStr.push_back(phrase);
            nbLigne+=1;

            if ( tailleOldColor >0)
            {
                phrase=""+OldColor.back();
            }
            else
                phrase="";

            CptChar=0;
            RajoutPhrase();

            
        }
    }
    else if (TailleMot + CptChar > _n && FinLigne && !FinFinal)
    {
        //std::cout<< " Quel if dans le RajoutPhrase : 4"<<std::endl;
        if (!Interrupt)
        {
            TailleMot--;
            size_t tailleOldColor = OldColor.size();
            
            phrase+="\033[0m";

            TabStr.push_back(phrase);
            nbLigne+=1;

            if ( tailleOldColor >0)
            {
                phrase=""+OldColor.back();
            }
            else
                phrase="";

            //std::cout<<"------------------------- fois 2 ? -----------------------------------------";
            CptChar=0;
            RajoutPhrase();
            
        }
    }
    else if(FinFinal)
    {
        phrase+="\033[0m";

        TabStr.push_back(phrase);
        nbLigne+=1;
    }
    //std::cout<<"CptCharAprès : "<<CptChar<<std::endl;
}

void TexteEnrichis::Init_style()
{
    if( balise_b)
    {
        phrase+="\033[1m";
    }
    if( balise_i)
    {
        phrase+="\033[3m";
    }
    if( balise_u)
    {
        phrase+="\033[4m";
    }
    if( balise_blink)
    {
        phrase+="\033[4m";
    }
    if( balise_rever)
    {
        phrase+="\033[4m";
    }
    if( DerniereColor=="")
    {
        phrase+="\033[0m";
    }
    else
        phrase+=DerniereColor;
}

void affiche(std::ostream& os, TexteEnrichis& T)
{
    for (size_t i=0;i<T.getNbLigne();i++)
        os<<T.getTab().at(i)<<std::endl;
    os<<T.getNbLigne()<<std::endl;
}
