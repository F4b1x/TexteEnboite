#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include "TexteEnrichis3.h"





TexteEnrichis::TexteEnrichis(): nbLigne(0), TabStr(0), OldColorFG(0), OldColorBG(0), Hist_Color(0), NomFichier(NULL), Texte(""), _n(0), CptChar(0), TailleMot(0), balise_b(false), balise_i(false), balise_u(false), balise_verb(false), balise_blink(false), balise_rever(false), phrase(""), MotDuTexte(""), motBalise(""), ligne(""), Interrupt(false), FinLigne(false), FinFinal(false), balise_center(false), balise_justify(false), balise_left(false), balise_right(false), AncienneTailleColor(0), DerniereColor("\033[0m"), balise_center_excpt(false), balise_justify_excpt(false), balise_left_excpt(false), balise_right_excpt(false), PeutJustify(false) {}
TexteEnrichis::TexteEnrichis(char* arg, size_t n): nbLigne(0), TabStr(0), OldColorFG(0), OldColorBG(0), Hist_Color(0), _n(n), CptChar(0), TailleMot(0), balise_b(false), balise_i(false), balise_u(false), balise_verb(false), balise_blink(false), balise_rever(false), phrase(""), MotDuTexte(""), motBalise(""), ligne(""), Interrupt(false), FinLigne(false), FinFinal(false), balise_center(false), balise_justify(false), balise_left(false), balise_right(false), AncienneTailleColor(0), DerniereColor("\033[0m"), balise_b_init(false), balise_i_init(false), balise_u_init(false), balise_verb_init(false), balise_blink_init(false), balise_rever_init(false), balise_center_excpt(false), balise_justify_excpt(false), balise_left_excpt(false), balise_right_excpt(false), PeutJustify(false)
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

TexteEnrichis::TexteEnrichis(const std::string arg, size_t n): nbLigne(0), TabStr(0), OldColorFG(0), OldColorBG(0), Hist_Color(0), NomFichier(NULL), Texte(arg), _n(0), CptChar(0), TailleMot(0), balise_b(false), balise_i(false), balise_u(false), balise_verb(false), balise_blink(false), balise_rever(false), phrase(""), MotDuTexte(""), motBalise(""), ligne(arg), Interrupt(false), FinLigne(false), FinFinal(false), balise_center(false), balise_justify(false), balise_left(false), balise_right(false), AncienneTailleColor(0), DerniereColor("\033[0m"), balise_b_init(false), balise_i_init(false), balise_u_init(false), balise_verb_init(false), balise_blink_init(false), balise_rever_init(false), balise_center_excpt(false), balise_justify_excpt(false), balise_left_excpt(false), balise_right_excpt(false), PeutJustify(false)
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

            RajoutPhrase();

            fich.close();
        }
    }
    else
    {
        std::cout<<"L'argument n'est pas un fichier"<<std::endl;
        ligne=Texte;
        AnalyseString();
        FinFinal=true;
        RajoutPhrase();
    }
}

void TexteEnrichis::TraitementBaliseCouleur()
{
    std::istringstream StringFlux(motBalise);
    std::string StrPart="";
    std::string couleur="";

    std::string CodeCouleurFG="",CodeCouleurBG="";

    DerniereColor="";

    bool FG=false, BG=false;
    while (StringFlux >> StrPart)
    {
        
        bool Foreground=false;
        bool Background=false;
        if (StrPart[0]=='f')
        {
            if (StrPart[StrPart.size()-1]=='>')
                couleur=StrPart.substr(3,StrPart.size()-4);
            else
                couleur=StrPart.substr(3,StrPart.size()-3);
            std::cout<<"couleur : "<<couleur<<std::endl;
            Foreground=true;
            FG=true;

        }
        else if (StrPart[0]=='b')
        {
            if (StrPart[StrPart.size()-1]=='>')
                couleur=StrPart.substr(3,StrPart.size()-4);
            else
                couleur=StrPart.substr(3,StrPart.size()-3);
            std::cout<<"couleur : "<<couleur<<std::endl;
            Background=true;
            BG=true;
        }

        if (couleur != "")
        {
            std::cout<<"Etat Foreground : "<<(Foreground?"1":"0")<<"\t Etat Background : "<<(Background?"1":"0")<<std::endl;
            if (couleur == "black")
            {
                if (Foreground)
                {
                    MotDuTexte+="\033[30m";
                    OldColorFG.push_back("\033[30m");
                }
                else
                {
                    MotDuTexte+="\033[40m";
                    OldColorBG.push_back("\033[40m");
                }
            }
            if (couleur == "red")
            {
                if (Foreground)
                {
                    MotDuTexte+="\033[31m";
                    OldColorFG.push_back("\033[31m");
                }
                else
                {    
                    MotDuTexte+="\033[41m";
                    OldColorBG.push_back("\033[41m");
                }
            }
            if (couleur == "green")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[32m";
                    OldColorFG.push_back("\033[32m");
                }
                else
                {    
                    MotDuTexte+="\033[42m";
                    OldColorBG.push_back("\033[42m");
                }
            }
            if (couleur == "yellow")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[33m";
                    OldColorFG.push_back("\033[33m");
                }
                else
                {    
                    MotDuTexte+="\033[43m";
                    OldColorBG.push_back("\033[43m");
                }
            }
            if (couleur == "blue")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[34m";
                    OldColorFG.push_back("\033[34m");
                }
                else
                {    
                    MotDuTexte+="\033[44m";
                    OldColorBG.push_back("\033[44m");
                }
            }
            if (couleur == "magenta")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[35m";
                    OldColorFG.push_back("\033[35m");
                }
                else
                {    
                    MotDuTexte+="\033[45m";
                    OldColorBG.push_back("\033[45m");
                }
            }
            if (couleur == "cyan")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[36m";
                    OldColorFG.push_back("\033[36m");
                }
                else
                {    
                    MotDuTexte+="\033[46m";
                    OldColorBG.push_back("\033[46m");
                }
            }
            if (couleur == "white")
            {
                if (Foreground)
                {    
                    MotDuTexte+="\033[37m";
                    OldColorFG.push_back("\033[37m");
                }
                else
                {    
                    MotDuTexte+="\033[47m";
                    OldColorBG.push_back("\033[47m");
                }
            }

        }

        
    }

    if ( FG && BG)
    {
        Hist_Color.push_back("fbg");
    }   
    else if ( FG && !BG)
    {    
        Hist_Color.push_back("fg");
    }
    else if ( !FG && BG)
    {    
        Hist_Color.push_back("bg");
    }

    if (OldColorFG.size() == 0 && OldColorBG.size() == 0)
    {
        DerniereColor="";
    }
    else if (OldColorFG.size() == 0)
    {
        DerniereColor=OldColorBG.back();
    }
    else if (OldColorBG.size() == 0)
    {
        DerniereColor= OldColorFG.back();
    }
    else
        DerniereColor=( OldColorFG.back() + OldColorBG.back() );

}

void TexteEnrichis::TraitementBaliseOuvrante()
{
    if(motBalise == "<b>" )
    {
        
        MotDuTexte+="\033[01m";
        balise_b=true;
        balise_b_init = true;
        
    }
    else if (motBalise == "<i>")
    {
        
        MotDuTexte+="\033[03m";
        balise_i=true;
        balise_i_init = true;
        
    }
    else if (motBalise == "<u>")
    {
        
        MotDuTexte+="\033[04m";
        balise_u=true;
        balise_u_init = true;
        
    }
    else if (motBalise == "<blink>")
    {
        
        MotDuTexte+="\033[05m";
        balise_blink=true;
        balise_blink_init = true;
        
    }
    else if (motBalise == "<reverse>")
    {
        
        MotDuTexte+="\033[07m";
        balise_rever=true;
        balise_rever_init = true;
        
    }
    else if (motBalise == "<p>")
    {
        FinLigne=true;
        RajoutPhrase();
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
        MotDuTexte+="<hr>";
        TailleMot+=4;
        //Interrupt=true;
    }
    else if (motBalise == "<center>")
    {
        FinLigne=true;
        RajoutPhrase();
        balise_center=true;
        balise_center_excpt=true;
    }
    else if (motBalise == "<left>")
    {
        FinLigne=true;
        RajoutPhrase();
        balise_left=true;
        balise_left_excpt=true;
    }
    else if (motBalise == "<right>")
    {
        FinLigne=true;
        RajoutPhrase();
        balise_right=true;
        balise_right_excpt=true;
    }
    else if (motBalise == "<justify>")
    {
        balise_justify=true;
        balise_justify_excpt=true;
        FinLigne=true;
        RajoutPhrase();

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
        FinLigne=true;
        RajoutPhrase();
    }
    else if (motBalise == "</center>")
    {
        balise_center=false;
    }
    else if (motBalise == "</left>")
    {
        balise_left=false;
    }
    else if (motBalise == "</right>")
    {
        balise_right=false;
    }
    else if (motBalise == "</justify>")
    {
        balise_justify=false;
    }
    else if (motBalise == "</color>")
    {
        //Interrupt=true;
        std::cout<<"Etat Interrupt dedans: "<<(Interrupt?"1":"0")<<std::endl;
        size_t tailleFG = OldColorFG.size();
        std::cout<<"tailleFG : "<<tailleFG<<std::endl;
        size_t tailleBG = OldColorBG.size();
        std::cout<<"tailleBG : "<<tailleBG<<std::endl;
        size_t tailleHist= Hist_Color.size();
        std::cout<<"taille : "<<tailleHist<<std::endl;
        //std::cout<<"Dans Hist : "<<Hist_Color[tailleHist]<<std::endl;
        //std::cout<<"Dans Hist-1 : "<<Hist_Color[tailleHist-1]<<std::endl;
        //std::cout<<"Dans Hist-2 : "<<Hist_Color[tailleHist-2]<<std::endl;

        if ( tailleHist == 1)
        {
            std::cout<<"Hello"<<std::endl;
            MotDuTexte+="\033[00m";
            Remise_style();
            if (Hist_Color.back() == "fg")
                OldColorFG.pop_back();
            else if (Hist_Color.back() == "bg")
                OldColorBG.pop_back();
            else if (Hist_Color.back() == "fbg")
            {
                OldColorFG.pop_back();
                OldColorBG.pop_back();
            }
            Hist_Color.pop_back();
        }
        else if (tailleHist > 1)
        {
            //std::cout<<"bonjour"<<std::endl;
            if (Hist_Color[tailleHist-1] == "fg")
            {
                if( tailleFG == 1)
                {
                    MotDuTexte+="\033[00m";
                    Remise_style();
                    if ( tailleBG > 0)
                    {
                        MotDuTexte+=OldColorBG.back();
                    }

                    OldColorFG.pop_back();
                }
                else if ( tailleFG > 1)
                {
                    MotDuTexte+=OldColorFG[tailleFG-2];
                    OldColorFG.pop_back();
                }
            }
            else if (Hist_Color[tailleHist-1] == "bg")
            {    
                if ( tailleBG == 1)
                {
                    MotDuTexte+="\033[00m";
                    Remise_style();
                    if ( tailleFG > 0)
                    {
                        MotDuTexte+=OldColorFG.back();
                    }
                    OldColorBG.pop_back();
                }
                else if ( tailleBG > 1)
                {
                    MotDuTexte+=OldColorBG[tailleBG-2];
                    OldColorBG.pop_back();
                }

            }
            else if ( Hist_Color[tailleHist-1] == "fbg")
            {
                if (tailleFG == 1 && tailleBG == 1)
                {
                    MotDuTexte+="\033[00m";
                    Remise_style();
                    OldColorFG.pop_back();
                    OldColorBG.pop_back();
                }
                else if(tailleFG == 1 && tailleBG > 1)
                {
                    MotDuTexte+="\033[00m";
                    Remise_style();
                    MotDuTexte+=OldColorBG[tailleBG-2];
                    OldColorBG.pop_back();
                    OldColorFG.pop_back();
                }
                else if (tailleFG > 1 && tailleBG == 1)
                {
                    MotDuTexte+="\033[00m";
                    Remise_style();
                    MotDuTexte+=OldColorFG[tailleFG-2];
                    OldColorBG.pop_back();
                    OldColorFG.pop_back();
                }
                else
                {
                    MotDuTexte+= ( OldColorFG[tailleFG-2] + OldColorBG[tailleBG-2] );
                    Remise_style();
                }

            }

            Hist_Color.pop_back();
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
                    balise_verb_init=true;
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
            

            /*size_t tailleHist= Hist_Color.size();
            //std::cout<<"taille : "<<tailleHist<<std::endl;

            if ( tailleHist == 0)
            {
                DerniereColor="";
            }
            else if (tailleHist > 0)
            {

                if (Hist_Color.back() == "fg")
                {    
                    DerniereColor=OldColorFG[OldColorFG.size()-1];
                }
                else if (Hist_Color.back() == "bg")
                {    
                    DerniereColor=OldColorBG[OldColorBG.size()-1];
                }
                else
                {
                    DerniereColor=OldColorFG[OldColorFG.size()-1]+OldColorBG[OldColorBG.size()-1];
                }
            }*/

                /*if (OldColor.size() == 0)
                {
                    DerniereColor="";
                }
                else if ( OldColor.size() > 0)
                {
                    DerniereColor=OldColor.back();
                }*/
            std::cout<<"Mot du Texte : "<<MotDuTexte<<"\t";
            TailleMot++;
            //std::cout<<"TailleMot : "<<TailleMot<<"\t";
            i++;
        }
        else if ( ligne[i] == ' ' || ligne[i]=='\0' || ligne[i]=='\t')
        {
            if ( TailleMot != 0)
            {    
                RajoutPhrase();
            }

            i++;
        }
        
    }

}

void TexteEnrichis::RajoutPhrase()
{
    //std::cout<<"Etat Interrupt avant: "<<(Interrupt?"1":"0")<<"\t";
    std::cout<<"CptCharAvant : "<<CptChar<<std::endl;

    if ( CptChar != 0)
    {
        TailleMot++;
    }


    if ( TailleMot + CptChar <= _n && !FinLigne && !FinFinal)
    {


        std::cout<< " Quel if dans le RajoutPhrase : 1"<<std::endl;
        std::cout<< " la couleur : "<<DerniereColor<<"Hello \e[0m"<<std::endl;

        if ( Interrupt)
        {
            Interrupt = false;
            std::cout<<"eeeeeeeeeeeeeeeeeeeeeeeeeeee : "<<Hist_Color.size()<<"eeeeeeeeeeeeeeeeeeeee";
            
            /*size_t tailleHist= Hist_Color.size();
            std::cout<<"taille1 : "<<tailleHist<<std::endl;

            if ( tailleHist >= 1)
            {
                if (Hist_Color.back() == "fg")
                {    
                    DerniereColor=OldColorFG[OldColorFG.size()-1];
                }
                else if (Hist_Color.back() == "bg")
                {    
                    DerniereColor=OldColorBG[OldColorBG.size()-1];
                }
                else
                {
                    DerniereColor=OldColorFG[OldColorFG.size()-1]+OldColorBG[OldColorBG.size()-1];
                }
            }*/


            /*if (OldColor.size() == 1)
            {
                DerniereColor=OldColor.back();
                std::cout<<"Last Color iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii : "<<DerniereColor<<"Hello \033[31m ReHello \033[0m"<<std::endl;
            }
            else if ( OldColor.size() > 1)
            {
                DerniereColor=OldColor.back();
                std::cout<<"Last Color iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii : "<<DerniereColor<<"Hello \033[0m"<<std::endl;
            }*/

        }

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
        Remise_bool_Egal();

    }


    else if ( TailleMot + CptChar <= _n && FinLigne && !FinFinal)
    {
        
        std::cout<< " Quel if dans le RajoutPhrase : 2"<<std::endl;
        if ( CptChar == 0)
        {
            phrase+=MotDuTexte;
            CptChar+= TailleMot;
        }
        else
        {
            phrase+=" "+MotDuTexte;
            CptChar+=TailleMot;
        }
        
        if ( Interrupt)
        {
            Interrupt = false;
            

            /*size_t tailleHist= Hist_Color.size();
            std::cout<<"taille2 : "<<tailleHist<<std::endl;

            if ( tailleHist == 0)
            {
                DerniereColor="";
            }
            else if (tailleHist > 0)
            {

                if (Hist_Color.back() == "fg")
                {    
                    DerniereColor=OldColorFG[OldColorFG.size()-1];
                }
                else if (Hist_Color.back() == "bg")
                {    
                    DerniereColor=OldColorBG[OldColorBG.size()-1];
                }
                else
                {
                    DerniereColor=OldColorFG[OldColorFG.size()-1]+OldColorBG[OldColorBG.size()-1];
                }
            }*/


            /*if (OldColor.size() == 0)
            {
                DerniereColor="";
            }
            else if ( OldColor.size() > 0)
            {
                DerniereColor=OldColor.back();
            }*/

        }
        
        //size_t tailleOldColor = OldColor.size();
        
        phrase+="\033[00m";

        PeutJustify = false;
        LastVerifAvantTabStr();
        nbLigne+=1;

        Init_style();
        Remise_bool_Egal();

        CptChar=0;
        TailleMot=0;
        MotDuTexte="";
        FinLigne=false;
    }


    else if (TailleMot + CptChar > _n && !FinLigne && !FinFinal)
    {
        std::cout<< " Quel if dans le RajoutPhrase : 3"<<std::endl;
        //if (!Interrupt)
        //{
        TailleMot--;
        //size_t tailleOldColor = OldColor.size();

        //std::cout<<"Taille du tableau Color : "<<tailleOldColor<<std::endl;
        //std::cout<<"Etat FinLigne"<<std::endl;

        phrase+="\033[00m";

        PeutJustify=true;
        LastVerifAvantTabStr();
        nbLigne+=1;

        /*if ( tailleOldColor >0)
        {
            phrase=""+OldColor.back();
        }
        else
            phrase="";*/
        Init_style();

        CptChar=0;
        RajoutPhrase();

            
        //}
    }
    else if (TailleMot + CptChar > _n && FinLigne && !FinFinal)
    {
        std::cout<< " Quel if dans le RajoutPhrase : 4"<<std::endl;
        //if (!Interrupt)
        //{
        TailleMot--;
        //size_t tailleOldColor = OldColor.size();
        
        phrase+="\033[00m";

        PeutJustify=true;
        LastVerifAvantTabStr();
        nbLigne+=1;

        /*if ( tailleOldColor >0)
        {
            phrase=""+OldColor.back();
        }
        else
            phrase="";*/

        Init_style();

        CptChar=0;
        RajoutPhrase();
            
        //}
    }
    else if(FinFinal)
    {
        phrase+="\033[0m";

        LastVerifAvantTabStr();
        nbLigne+=1;
    }
    std::cout<<"CptCharAprès : "<<CptChar<<std::endl;
    //std::cout<<"Etat Interrupt apres: "<<(Interrupt?"1":"0")<<std::endl;
}

void TexteEnrichis::Init_style()
{
    std::cout<<"ici peut être  : "<<DerniereColor<<"hello \033[0m"<<std::endl;
    std::cout<<"Etat reverse "<<(balise_rever?"1":"0")<<std::endl;
    std::cout<<"Etat reverser_init "<<(balise_rever_init?"1":"0")<<std::endl;
    /*std::cout<<"Etat i "<<(balise_i?"1":"0")<<std::endl;
    std::cout<<"Etat i_init "<<(balise_i_init?"1":"0")<<std::endl;
    std::cout<<"Etat u "<<(balise_u?"1":"0")<<std::endl;
    std::cout<<"Etat u_init "<<(balise_u_init?"1":"0")<<std::endl;*/
    phrase="";
    if( balise_b || (balise_b==false && balise_b_init==true))
    {
        phrase+="\033[01m";
        balise_b_init = false;

    }
    if( balise_i || (balise_i==false && balise_i_init==true))
    {
        phrase+="\033[03m";
        balise_i_init = false;
    }
    if( balise_u || (balise_u==false && balise_u_init==true))
    {
        phrase+="\033[04m";
        balise_u_init = false;
    }
    if( balise_blink || (balise_blink==false && balise_blink_init==true))
    {
        phrase+="\033[05m";
        balise_blink_init = false;
    }
    if( balise_rever || (balise_rever==false && balise_rever_init==true))
    {

        phrase+="\033[07m";
        balise_rever_init = false;
    }
    if ( Hist_Color.size() > 0)
    {
        if ( OldColorFG.size() == 0 && OldColorBG.size() > 0)
        {
            phrase+=OldColorBG.back();
        }
        else if (  OldColorFG.size() > 0 && OldColorBG.size() == 0 )
        {
            phrase+=OldColorFG.back();
        }
        else if ( OldColorFG.size() > 0 && OldColorBG.size() > 0)
        {
            phrase+= ( OldColorFG.back() + OldColorBG.back() );
        }
    }
    /*if( Interrupt)
    {
        phrase+=DerniereColor;
        Interrupt = false;

        /*size_t tailleHist= Hist_Color.size();
        std::cout<<"taille init: "<<tailleHist<<std::endl;
        std::cout<<"dedans il y a : "<<Hist_Color[tailleHist-1]<<std::endl;

        if ( tailleHist == 0)
        {
            DerniereColor="";
        }
        else if (tailleHist > 0)
        {

            if (Hist_Color[tailleHist-1] == "fg")
            {
                std::cout<<OldColorFG[OldColorFG.size()-1]<<"lol \e[0m"<<std::endl;
                DerniereColor=OldColorFG[OldColorFG.size()-1];
            }
            else if (Hist_Color[tailleHist-1] == "bg")
            {    
                DerniereColor=OldColorBG[OldColorBG.size()-1];
            }
            else
            {
                DerniereColor=OldColorFG[OldColorFG.size()-1]+OldColorBG[OldColorBG.size()-1];
            }
        }*/

        /*if (OldColor.size() == 0)
        {
            std::cout<<"ou là \t";
            DerniereColor="";
        }
        else if ( OldColor.size() > 0)
        {
            DerniereColor=OldColor.back();
            std::cout<<"ici \t";
        }*/
    /*}
    else if ( !Interrupt && DerniereColor!="")
    {
        std::cout<<"la alors ?";
        phrase+=DerniereColor;
    }*/
        
}

void TexteEnrichis::Remise_style()
{
    std::cout<<"bonne nuit"<<std::endl;
    if( balise_b || balise_b==false && balise_b_init==true)
    {
        MotDuTexte+="\033[01m";
    }
    if(  balise_i || balise_i==false && balise_i_init==true)
    {
        MotDuTexte+="\033[03m";
    }
    if(  balise_u || balise_u==false && balise_u_init==true)
    {
        MotDuTexte+="\033[04m";
    }
    if(  balise_blink || balise_blink==false && balise_blink_init==true)
    {
        MotDuTexte+="\033[05m";
    }
    if(  balise_rever || balise_rever==false && balise_rever_init==true)
    {
        MotDuTexte+="\033[07m";
    }
}

void TexteEnrichis::Remise_bool_Egal()
{
    if (balise_b == false)
        balise_b_init = false;

    if (balise_i == false)
        balise_i_init = false;

    if (balise_u == false)
        balise_u_init = false;

    if (balise_blink == false)
        balise_blink_init = false;

    if (balise_rever == false)
        balise_rever_init = false;

}

void TexteEnrichis::LastVerifAvantTabStr()
{
    size_t difference = _n - CptChar;

    if ( CptChar == 0)
    {
        for (size_t i = 0; i < difference; i++)
        {
            phrase+= " ";
        }
        TabStr.push_back(phrase);
    }

    else if ( balise_center || (balise_center==false && balise_center_excpt==true))
    {
        size_t NbEspace = difference / 2;
        for(size_t i = 0 ; i < NbEspace ; i++)
        {
            phrase = " "+phrase;
        }
        NbEspace = difference - NbEspace;
        for (size_t j = 0; j < NbEspace; j++)
        {
            phrase+=" ";
        }
        TabStr.push_back(phrase);
    }
    else if ( balise_right || (balise_right==false && balise_right_excpt==true))
    {
        for (size_t i = 0; i < difference; i++)
        {
            phrase = " "+phrase;
        }
        TabStr.push_back(phrase);
    }
    else if ( balise_left || (balise_left==false && balise_left_excpt==true))
    {
        for (size_t i = 0; i < difference; i++)
        {
            phrase+= " ";
        }
        TabStr.push_back(phrase);
    }
    else if ( (balise_justify || (balise_justify==false && balise_justify_excpt==true)) && PeutJustify )
    {
        if ( CptChar != 0)
        {
            size_t i=0;
            while (CptChar < _n)
            {
                if ( i == phrase.size())
                {
                    i=0;
                }
    
                if ( phrase[i]== ' ')
                {
                    phrase=(phrase.substr(0,i)+"  "+phrase.substr(i+1));
                    CptChar++;
                    i+=2;
                }
                else
                    i++;
            }
        }

        TabStr.push_back(phrase);
    }
    else
    {
        for (size_t i = 0; i < difference; i++)
        {
            phrase+= " ";
        }
        TabStr.push_back(phrase);
    }


    if ( balise_center == false && balise_center_excpt==true)
    {
        balise_center_excpt = false;
    }
    else if ( balise_left == false && balise_left_excpt==true)
    {
        balise_left_excpt = false;
    }
    else if ( balise_right == false && balise_right_excpt==true)
    {
        balise_right_excpt = false;
    }
    else if ( balise_justify == false && balise_justify_excpt==true)
    {
        balise_justify_excpt = false;
    }
}

void affiche(std::ostream& os, TexteEnrichis& T)
{
    for (size_t i=0;i<T.getNbLigne();i++)
        os<<T.getTab().at(i)<<std::endl;
    os<<T.getNbLigne()<<std::endl;
}
