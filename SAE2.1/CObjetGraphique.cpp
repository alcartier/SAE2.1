#include "CObjetGraphique.h"
#include "LibGraph2.h"


//Prépare l'affichage de l'object Graphique.
void CObjetGraphique::Afficher(bool sombre) const
{
	LibGraph2::ARGB penColor = m_colColor;
	if (sombre)
	{
		penColor = LibGraph2::MakeARGB(255, 255, 255, 255);
	}
	LibGraph2::GetLibGraph2()->setPen(penColor, m_fThickness, m_eStyle);
	LibGraph2::GetLibGraph2()->setSolidBrush(m_colFillColor);
}

//Définit la position du coin haut-gauche de cet objet.
void CObjetGraphique::SetP1(const LibGraph2::CPoint& pt)
{
	m_ptP1 = pt;
}

