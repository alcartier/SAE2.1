#pragma once
#include <string>
#include "CObjetGraphique.h"
#include "LibGraph2.h"
#include <string>

class CBouton : public CObjetGraphique
{
private:
	double height = 100;
	double width = 100;
	LibGraph2::CSize m_size;
	std::string m_Libelle;
	LibGraph2::ARGB m_hoverColor;

public:
	CBouton(float x, float y, float w, float h, const std::string& libelle, LibGraph2::ARGB couleur);

	void Afficher(bool sombre) const override;

	bool isClicked(double x, double y);

	//GETTERS
	LibGraph2::ARGB GetHoverColor();

	//SETTERS
	void SetSize(const LibGraph2::CSize& size);
	void SetLibelle(const std::string& lib);
};

