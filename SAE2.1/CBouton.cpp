#include "CBouton.h"
#include "LibGraph2.h"

//Affiche le bouton
void CBouton::Afficher(bool sombre) const 
{
	CObjetGraphique::Afficher(sombre);
	auto* lg = LibGraph2::GetLibGraph2();
	lg->drawRectangle(LibGraph2::CRectangle(m_ptP1, m_size));

	if (!m_Libelle.empty())
	{
		lg->setSolidBrush(LibGraph2::MakeARGB(255, 255, 255, 255));
		lg->setFont(L"Segoe UI", 11.0f, LibGraph2::font_styles::FontStyleRegular);
		LibGraph2::CPoint ptTexte(m_ptP1.m_fX + 10, m_ptP1.m_fY + m_size.m_fHeight / 2 - 8);
		lg->drawString(LibGraph2::CString(m_Libelle), ptTexte);
	}
}

//Check si la souris est sur le bouton
bool CBouton::isClicked(double x, double y)
{
	if (m_ptP1.m_fX <= x && x <= m_ptP1.m_fX + m_size.m_fWidth)
	{
		if (m_ptP1.m_fY <= y && y <= m_ptP1.m_fY + m_size.m_fHeight)
		{
			return true;
		}
	}
	return false;
}

//Definit la taille du bouton
void CBouton::SetSize(const LibGraph2::CSize& size){
	m_size = size;
}

//Definit le libelle du bouton
void CBouton::SetLibelle(const std::string& lib)
{
	m_Libelle = lib;
}

//Renvoie la couleur de hover du bouton
LibGraph2::ARGB CBouton::GetHoverColor(){
	return m_hoverColor;
}

//Constructeur du bouton pour initialiser les donnees membres
CBouton::CBouton(float x, float y, float w, float h, const std::string& libelle, LibGraph2::ARGB couleur)
{
	SetP1(LibGraph2::CPoint(x, y));
	SetSize(LibGraph2::CSize(w, h));
	SetFillColor(couleur);
	SetBAseFillColor(couleur);
	m_hoverColor = couleur + 1315860;
	SetColor(LibGraph2::MakeARGB(255, 0, 0, 0));
	SetThickness(3.0f);
	SetLibelle(libelle);
}