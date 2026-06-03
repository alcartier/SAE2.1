#include <Windows.h>
#include <tchar.h>
#include <LibGraph2.h>
#include <memory>
#include <vector>
#include "CParsing.h"
#include "CDate.h"
#include "CReleveMeteo.h"
#include "CApp.h"
#include "CAffichage.h"
#include "CBouton.h"
#include "CObjetGraphique.h"
using namespace LibGraph2;

/*--------------------------------------HELP--------------------------------------*/

//fonction pour afficher un pop up d'aide
void Help()
{
    LibGraph2::GetLibGraph2()->guiMessageBox("Aide", "Commandes claviers :\n"
        "G : Afficher le graphique général\n"
        "A : Afficher le graphique des années\n"
        "M : Afficher le graphique des mois\n"
        "E : Effacer le graphique en cours\n"
        "S : Active le mode sombre !\n"
        "C : Active le mode clair !\n"
        "-> : Augmente la date ou le mois de 1\n"
        "<- : Diminue la date ou le mois de 1\n"
        "F1 : Affiche cette aide", LibGraph2::msgbtn_types::MsgBtnOK, LibGraph2::msgicon_types::MsgIcnInformation);
}

/*-------------------------------------/HELP--------------------------------------*/

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	/*----------------------------------INIT------------------------------------------*/

    ILibGraph2* libgraph = GetLibGraph2();
    libgraph->show(CSize(1200, 800));
    //libgraph->showConsole();
    evt e;

    /*----------------------------LectureDesDonnees-----------------------------------*/

    //parsing des donnees
    std::vector<std::string> lecFichier = CParsing::lireFichier("data.csv");
    std::vector<std::vector<std::string>> datas = CParsing::separerLignes(lecFichier);
    std::vector<CReleveMeteo> releveMeteo = CParsing::parseLigne(datas);
    //creation de l'app avec l'ajout des donnees
    CApp app(releveMeteo);

    int val = 0;

    /*---------------------------CREATION DES BOUTONS---------------------------------*/

    //calcul pour que ça tombe bien
    float gap = (1200 - (20 * 6)) / 5;
    float x = 66;
    CBouton btnGraphque = { x, 720, 200, 50, "Graphique", MakeARGB(255, 180, 60, 60) };
    x += gap;
    CBouton btnAnnee = { x, 720, 200, 50, "Graphique Annee", MakeARGB(255, 60, 120, 180) };
    x += gap;
    CBouton btnMois = { x, 720, 200, 50, "Graphique Mois", MakeARGB(255, 150, 90, 170) };
    x += gap;
    CBouton btnDelete = { x, 720, 200, 50, "Supprimmer Graphique", MakeARGB(255, 90, 150, 90) };
    x += gap;
    CBouton btnRaccourcis = { x, 720, 200, 50, "Raccourcis", MakeARGB(255, 190, 140, 60) };
    //boutons pour le mode sombre et clair
    CBouton btnSombre = { 1014, 40, 50, 50, "  S", MakeARGB(255, 80, 80, 80) };
    CBouton btnClair = { 1084, 40, 50, 50, "  C", MakeARGB(255, 190, 190, 190) };
    //boutons pour avancer et reculer dans la date
    CBouton btnNext = { 1084, 360, 50, 50, " ->", MakeARGB(255, 190, 100, 200) };
    CBouton btnPrevious = { 66, 360, 50, 50, " <-", MakeARGB(255, 190, 100, 200) };
    //creation de l'affichage et ajout des boutons
    CAffichage affichage(app, false);
    affichage.AddButton(btnGraphque);
    affichage.AddButton(btnAnnee);
    affichage.AddButton(btnMois);
    affichage.AddButton(btnDelete);
    affichage.AddButton(btnRaccourcis);
    affichage.AddButton(btnSombre);
    affichage.AddButton(btnClair);
    affichage.AddButton(btnNext);
    affichage.AddButton(btnPrevious);

    /*--------------------------------------HELP--------------------------------------*/

    Help();

    /*-----------------------------------APPLICATION----------------------------------*/
                                               

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'événement
        {
            case evt_type::evtRefresh:
                libgraph->beginPaint();
                if (affichage.getSombre())
                {
                    libgraph->setSolidBrush(LibGraph2::MakeARGB(255, 50, 50, 50));
                    libgraph->drawRectangle(LibGraph2::CRectangle(LibGraph2::CPoint(0, 0), libgraph->getSize()));
                }
                libgraph->setPen(MakeARGB(255, 0, 0, 0), 4.0f, LibGraph2::pen_DashStyles::Solid);
                affichage.Afficher();
                libgraph->endPaint();
                break;

            // RACCOURCIS CLAVIER
            case evt_type::evtKeyDown:  //Enfoncement d'une touche
            {
                
                
                switch (e.vkKeyCode) //En fonction de la touche enfoncée
                {
                    case VK_F1:
                    {
                        Help();
                        break;
                    }
                    case VK_LEFT:
                    {
                        affichage.Previous();
                        break;
                    }
                    case VK_RIGHT:
                    {
                        affichage.Next();
                        break;
                    }
                    case 'A':
                    {
                        int annee = 0;
                        libgraph->guiGetValue(annee, "Annee", "Entrez une année entre 1896 et 2025 :");
                        affichage.AfficherGraphiqueAnnee(annee);
                        break;
                    }
                    case 'C':
                    {
                        affichage.setSombre(false);
                        break;
                    }
                    case 'E':
                    {
                        affichage.EffacerGraphique();
                        break;
                    }
                    case 'G':
                    {
                        affichage.AfficherGraphique();
                        break;
                    }
                    case 'M':
                    {
                        int mois = 0;
                        libgraph->guiGetValue(mois, "Mois", "Entrez un mois entre 1 et 12 :");
                        affichage.AfficherGraphiqueMois(mois);
                        break;
                    }
                    case 'S':
                    {
                        affichage.setSombre(true);
                        break;
                    }
                }
                break;
            }

            //BOUTON CLICK
            case evt_type::evtMouseDown:
            {
                //evenement lors du click de la souris
                if (btnGraphque.isClicked(e.x, e.y))
                {
                    affichage.AfficherGraphique();
                }
                if (btnAnnee.isClicked(e.x, e.y))
                {
                    libgraph->guiGetValue(val, "Annee", "Entrez une année entre 1896 et 2025 :");
                    affichage.AfficherGraphiqueAnnee(val);
                }
                if (btnMois.isClicked(e.x, e.y))
                {
                    libgraph->guiGetValue(val, "Mois", "Entrez un mois entre 1 et 12 :");
                    affichage.AfficherGraphiqueMois(val);
                }
                if (btnDelete.isClicked(e.x, e.y))
                {
                    affichage.EffacerGraphique();
                }
                if (btnRaccourcis.isClicked(e.x, e.y))
                {
                    Help();
                }
                if (btnSombre.isClicked(e.x, e.y))
                {
                    affichage.setSombre(true);
                }
                if (btnClair.isClicked(e.x, e.y))
                {
                    affichage.setSombre(false);
                }
                if (btnNext.isClicked(e.x, e.y))
                {
                    affichage.Next();
                }
                if (btnPrevious.isClicked(e.x, e.y))
                {
                    affichage.Previous();
                }
                break;
            }

            //POUR LES HOVER DES BOUTONS 
            case evt_type::evtMouseMove:
            {
                for (auto& btn : affichage.getBouton())
                {
                    if (btn.isClicked(e.x, e.y))
                    {
                        affichage.hover(btn);
                    }
                    else
                    {
                        affichage.unhover(btn);
                    }
                }
            }
        }
        libgraph->askForRefresh();
    }

    //Libération de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
    return 0;
}