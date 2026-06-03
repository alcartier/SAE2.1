#pragma once
#include <LibGraph2.h>
#include "CApp.h"
#include "CBouton.h"

class CAffichage
{
private:
	enum Etat{
		None,
		Graphique1,
		Graphique2,
		Graphique3,
	};
	Etat etatActuel = None;

	CApp* m_app = nullptr;

	std::vector<CBouton> m_buttons;

	int m_currentMois = 1;
	int m_currentAnnee = 1;
	bool m_sombre = false;

public:
	CAffichage(CApp& app, bool sombre);

	void Afficher();

	void AfficherBtn();

	void DrawTitle(std::string title);
	void DrawSubTitle(std::string subtitle);

	int AfficherGraphiqueMois(int mois);
	int AfficherGraphiqueAnnee(int annee);
	void AfficherGraphique();
	void EffacerGraphique();
	void Next();
	void Previous();

	void AddButton(CBouton btn);
	void hover(CBouton& btn);
	void unhover(CBouton& btn);
	std::vector<CBouton>& getBouton();

	void DrawGraphique();
	void DrawGraphiqueMois(int mois);
	void DrawGraphiqueAnnee(int annee);

	void setSombre(bool sombre);
	bool getSombre();
};

