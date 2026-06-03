#include "CAffichage.h"
#include <sstream>
using namespace LibGraph2;

//AFFICHAGE DES BOUTONS

void CAffichage::AfficherBtn()
{
	for (int i = 0; i < m_buttons.size() - 2;i++) {
		m_buttons[i].Afficher(m_sombre);
	}
}

//Ajout des boutons dans la liste des boutons 
void CAffichage::AddButton(CBouton btn)
{
	m_buttons.push_back(btn);
}

void CAffichage::hover(CBouton& btn)
{
	btn.SetFillColor(btn.GetHoverColor());
}

void CAffichage::unhover(CBouton& btn)
{
	btn.SetFillColor(btn.GetBaseFillColor());
}

std::vector<CBouton>& CAffichage::getBouton() {
	return m_buttons;
}

//Fonction pour dessiner les graphique



void CAffichage::DrawGraphique()
{
	auto* lg = GetLibGraph2();

	int aMin = m_app->anneeMin();
	int aMax = m_app->anneeMax();

	// Moyennes annuelles
	std::vector<std::pair<int, double>> moyennes;
	for (int a = aMin; a <= aMax; ++a)
	{
		double m = m_app->moyenneAnnee(a);
		if (m != 0.0) moyennes.emplace_back(a, m);
	}

	double moyMin = moyennes[0].second;
	double moyMax = moyennes[0].second;
	for (const auto& p : moyennes)
	{
		if (p.second < moyMin)
		{
			moyMin = p.second;
		}
		if (p.second > moyMax)
		{
			moyMax = p.second;
		}
	}
	moyMin -= 0.5;  moyMax += 0.5;

	//ZONE DU GRAPHIQUE
	float zoneX = 200;
	float zoneY = 200;
	float zoneW = 850;
	float zoneH = 375;

	// Grille
	if (m_sombre)
	{
		lg->setPen(MakeARGB(80, 255, 255, 255), 1.0f, pen_DashStyles::Dash);
	}
	else
	{
		lg->setPen(MakeARGB(80, 20, 20, 20), 1.0f, pen_DashStyles::Dash);
	}

	for (int i = 0; i <= 5; ++i)
	{
		float y = zoneY + i * zoneH / 5;
		lg->drawLine(CPoint(zoneX, y), CPoint(zoneX + zoneW, y));
		double valeur = moyMax - (moyMax - moyMin) * i / 5;

		//https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-c
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "%g °C", round(valeur * 100) / 100);

		if (m_sombre)
		{
			lg->setSolidBrush(MakeARGB(255, 255, 255, 255));
		}
		else
		{
			lg->setSolidBrush(MakeARGB(255, 20, 20, 20));
		}
		lg->setFont("Segoe UI", 9.0f, font_styles::FontStyleRegular);
		lg->drawString(buffer, CPoint(zoneX - 50, y - 8));
	}

	// Moyenne annuelle : points + ligne bleue
	std::vector<CPoint> pts;
	for (const auto& p : moyennes)
	{
		float x = zoneX + (p.first - aMin) * zoneW / (aMax - aMin);
		float y = zoneY + zoneH - float((p.second - moyMin) / (moyMax - moyMin) * zoneH);
		pts.emplace_back(x, y);
	}
	//On enleve 2026 car l'annee n'est pas finit
	pts.pop_back();

	lg->setPen(MakeARGB(200, 100, 140, 220), 1.5f);
	lg->drawPolylines(pts, false);


	//On dessine tout les points
	lg->setSolidBrush(MakeARGB(255, 100, 140, 220));
	for (const auto& p : pts) {
		lg->drawEllipse(CRectangle(CPoint(p.m_fX - 2, p.m_fY - 2), CSize(4, 4)));
	}

	// Moyenne glissante sur 5 ans : ligne rouge
	std::vector<CPoint> ptsLiss;
	for (size_t i = 0; i < moyennes.size(); ++i)
	{
		int n = 0; double s = 0.0;
		for (int k = -2; k <= 2; ++k)
		{
			int j = static_cast<int>(i) + k;
			if (j < 0 || j >= static_cast<int>(moyennes.size())) continue;
			s += moyennes[j].second;
			++n;
		}
		if (n == 0) continue;
		double v = s / n;
		float x = zoneX + (moyennes[i].first - aMin) * zoneW / (aMax - aMin);
		float y = zoneY + zoneH - float((v - moyMin) / (moyMax - moyMin) * zoneH);
		ptsLiss.emplace_back(x, y);
	}
	//On enleve 2026 car l'annee n'est pas finit
	ptsLiss.pop_back();

	lg->setPen(MakeARGB(255, 230, 60, 60), 3.0f);
	lg->drawPolylines(ptsLiss, false);

	// Légende
	lg->setSolidBrush(MakeARGB(255, 100, 140, 220));
	lg->setFont(L"Segoe UI", 10.0f, font_styles::FontStyleRegular);
	lg->drawString("Moyenne annuelle", CPoint(zoneX + zoneW - 260, zoneY - 40));
	lg->setSolidBrush(MakeARGB(255, 230, 60, 60));
	lg->drawString("Moyenne glissante sur 5 ans", CPoint(zoneX + zoneW - 260, zoneY - 60));

	// Axe X - années
	if (m_sombre)
	{
		lg->setSolidBrush(MakeARGB(255, 255, 255, 255));
	}
	else
	{
		lg->setSolidBrush(MakeARGB(255, 20, 20, 20));
	}
	for (int a = aMin; a <= aMax; a += 10)
	{
		float x = zoneX + (a - aMin) * zoneW / (aMax - aMin);
		lg->drawString(CString(std::to_wstring(a)), CPoint(x - 12, zoneY + zoneH + 5));
	}
}


void CAffichage::DrawGraphiqueMois(int mois)
{
	auto* lg = GetLibGraph2();

	auto data = m_app->getData();
	int aMin = m_app->anneeMin();
	int aMax = m_app->anneeMax();

	// Moyennes annuelles
	std::vector<std::pair<int, double>> moyennes;
	for (int i = 0;i < data.size(); i++)
	{
		if (data[i].getDate().getMois() == mois) 
		{
			moyennes.emplace_back(data[i].getDate().getAnnee(), data[i].getTemperature());
		}
	}

	double moyMin = moyennes[0].second;
	double moyMax = moyennes[0].second;
	for (const auto& p : moyennes)
	{
		if (p.second < moyMin) 
		{
			moyMin = p.second;
		}
		if (p.second > moyMax)
		{
			moyMax = p.second;
		}
	}
	moyMin -= 0.5;  moyMax += 0.5;

	//ZONE DU GRAPHIQUE
	float zoneX = 200;
	float zoneY = 200;
	float zoneW = 850;
	float zoneH = 375;

	// Grille
	if (m_sombre)
	{
		lg->setPen(MakeARGB(80, 255, 255, 255), 1.0f, pen_DashStyles::Dash);
	}
	else
	{
		lg->setPen(MakeARGB(80, 20, 20, 20), 1.0f, pen_DashStyles::Dash);
	}
	for (int i = 0; i <= 5; ++i)
	{
		float y = zoneY + i * zoneH / 5;
		lg->drawLine(CPoint(zoneX, y), CPoint(zoneX + zoneW, y));
		double valeur = moyMax - (moyMax - moyMin) * i / 5;

		//https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-c
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "%g °C", round(valeur * 100) / 100);

		if (m_sombre)
		{
			lg->setSolidBrush(MakeARGB(255, 255, 255, 255));
		}
		else
		{
			lg->setSolidBrush(MakeARGB(255, 20, 20, 20));
		}
		lg->setFont("Segoe UI", 9.0f, font_styles::FontStyleRegular);
		lg->drawString(buffer, CPoint(zoneX - 50, y - 8));
	}

	// Moyenne annuelle : points + ligne bleue
	std::vector<CPoint> pts;
	for (const auto& p : moyennes)
	{
		float x = zoneX + (p.first - aMin) * zoneW / (aMax - aMin);
		float y = zoneY + zoneH - float((p.second - moyMin) / (moyMax - moyMin) * zoneH);
		pts.emplace_back(x, y);
	}
	//On enleve 2026 car l'annee n'est pas finit
	pts.pop_back();

	lg->setPen(MakeARGB(200, 100, 140, 220), 1.5f);
	lg->drawPolylines(pts, false);


	//On dessine tout les points
	lg->setSolidBrush(MakeARGB(255, 100, 140, 220));
	for (const auto& p : pts) {
		lg->drawEllipse(CRectangle(CPoint(p.m_fX - 2, p.m_fY - 2), CSize(4, 4)));
	}

	// Moyenne glissante sur 5 ans : ligne rouge
	std::vector<CPoint> ptsLiss;
	for (size_t i = 0; i < moyennes.size(); ++i)
	{
		int n = 0; double s = 0.0;
		for (int k = -2; k <= 2; ++k)
		{
			int j = static_cast<int>(i) + k;
			if (j < 0 || j >= static_cast<int>(moyennes.size())) 
				continue;
			s += moyennes[j].second;
			++n;
		}
		if (n == 0) 
			continue;
		double v = s / n;
		float x = zoneX + (moyennes[i].first - aMin) * zoneW / (aMax - aMin);
		float y = zoneY + zoneH - float((v - moyMin) / (moyMax - moyMin) * zoneH);
		ptsLiss.emplace_back(x, y);
	}
	//On enleve 2026 car l'annee n'est pas finit
	ptsLiss.pop_back();

	lg->setPen(MakeARGB(255, 230, 60, 60), 3.0f);
	lg->drawPolylines(ptsLiss, false);

	// Légende
	lg->setSolidBrush(MakeARGB(255, 100, 140, 220));
	lg->setFont(L"Segoe UI", 10.0f, font_styles::FontStyleRegular);
	lg->drawString("Moyenne annuelle", CPoint(zoneX + zoneW - 260, zoneY - 40));
	lg->setSolidBrush(MakeARGB(255, 230, 60, 60));
	lg->drawString("Moyenne glissante sur 5 ans", CPoint(zoneX + zoneW - 260, zoneY - 60));
	// Axe X - années
	if (m_sombre)
	{
		lg->setSolidBrush(MakeARGB(255, 255, 255, 255));
	}
	else
	{
		lg->setSolidBrush(MakeARGB(255, 20, 20, 20));
	}
	for (int a = aMin; a <= aMax; a += 10)
	{
		float x = zoneX + (a - aMin) * zoneW / (aMax - aMin);
		lg->drawString(CString(std::to_wstring(a)), CPoint(x - 12, zoneY + zoneH + 5));
	}
}

void CAffichage::DrawGraphiqueAnnee(int annee)
{
	auto* lg = GetLibGraph2();

	auto data = m_app->getData();
	int mMin = 1;
	int mMax = 12;

	// Moyennes
	std::vector<std::pair<int, double>> moyennes;
	for (int i = 0;i < data.size(); i++)
	{
		if (data[i].getDate().getAnnee() == annee) {
			moyennes.emplace_back(data[i].getDate().getMois(), data[i].getTemperature());
		}

	}

	double moyMin = moyennes[0].second;
	double moyMax = moyennes[0].second;
	for (const auto& p : moyennes)
	{
		if (p.second < moyMin) {
			moyMin = p.second;
		}
		if (p.second > moyMax)
		{
			moyMax = p.second;
		}
	}
	moyMin -= 0.5;  moyMax += 0.5;

	//ZONE DU GRAPHIQUE
	float zoneX = 200;
	float zoneY = 200;
	float zoneW = 850;
	float zoneH = 375;

	// Grille
	if (m_sombre)
	{
		lg->setPen(MakeARGB(80, 255, 255, 255), 1.0f, pen_DashStyles::Dash);
	}
	else
	{
		lg->setPen(MakeARGB(80, 20, 20, 20), 1.0f, pen_DashStyles::Dash);
	}
	for (int i = 0; i <= 5; ++i)
	{
		float y = zoneY + i * zoneH / 5;
		lg->drawLine(CPoint(zoneX, y), CPoint(zoneX + zoneW, y));
		double valeur = moyMax - (moyMax - moyMin) * i / 5;

		//https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-c
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "%g °C", round(valeur * 100) / 100);

		if (m_sombre)
		{
			lg->setSolidBrush(MakeARGB(255, 255, 255, 255));
		}
		else
		{
			lg->setSolidBrush(MakeARGB(255, 20, 20, 20));
		}
		lg->setFont("Segoe UI", 9.0f, font_styles::FontStyleRegular);
		lg->drawString(buffer, CPoint(zoneX - 50, y - 8));
	}

	// Moyenne annuelle : points + ligne bleue
	std::vector<CPoint> pts;
	for (const auto& p : moyennes)
	{
		float x = zoneX + (p.first - mMin) * zoneW / (mMax - mMin);
		float y = zoneY + zoneH - float((p.second - moyMin) / (moyMax - moyMin) * zoneH);
		pts.emplace_back(x, y);
	}

	lg->setPen(MakeARGB(200, 100, 140, 220), 1.5f);
	lg->drawPolylines(pts, false);


	//On dessine tout les points
	lg->setSolidBrush(MakeARGB(255, 100, 140, 220));
	for (const auto& p : pts) {
		lg->drawEllipse(CRectangle(CPoint(p.m_fX - 2, p.m_fY - 2), CSize(4, 4)));
	}

	// Légende
	lg->setSolidBrush(MakeARGB(255, 100, 140, 220));
	lg->setFont(L"Segoe UI", 10.0f, font_styles::FontStyleRegular);
	lg->drawString("Moyenne annuelle", CPoint(zoneX + zoneW - 260, zoneY - 40));
	// Axe X - années
	if (m_sombre)
	{
		lg->setSolidBrush(MakeARGB(255, 255, 255, 255));
	}
	else
	{
		lg->setSolidBrush(MakeARGB(255, 20, 20, 20));
	}
	std::vector<std::string> mois = { "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre" };

	for (int a = mMin; a <= mMax; a += 1)
	{
		float x = zoneX + (a - mMin) * zoneW / (mMax - mMin);

		lg->drawString(CString(mois[a - 1]), CPoint(x - 12, zoneY + zoneH + 5));
	}
}

void CAffichage::DrawTitle(std::string title)
{
	auto* lg = LibGraph2::GetLibGraph2();
	if (m_sombre)
	{
		lg->setSolidBrush(LibGraph2::MakeARGB(255, 255, 255, 255));
	}
	else
	{
		lg->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
	}
	lg->setFont(L"Segoe UI", 35.0f, LibGraph2::font_styles::FontStyleRegular);
	LibGraph2::CPoint ptTexte(10, 25);
	lg->drawString(LibGraph2::CString(title), ptTexte);
}

void CAffichage::DrawSubTitle(std::string subtitle)
{
	auto* lg = LibGraph2::GetLibGraph2();
	if (m_sombre)
	{
		lg->setSolidBrush(LibGraph2::MakeARGB(255, 255, 255, 255));
	}
	else
	{
		lg->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
	}
	lg->setFont(L"Segoe UI", 20, LibGraph2::font_styles::FontStyleRegular);
	LibGraph2::CPoint ptTexte(30, 75);
	lg->drawString(LibGraph2::CString(subtitle), ptTexte);
}

void CAffichage::setSombre(bool sombre)
{
	m_sombre = sombre;
}

bool CAffichage::getSombre()
{
	return m_sombre;
}

//fonction appel des bouton
int CAffichage::AfficherGraphiqueMois(int mois)
{
	if (mois < 1)
	{
		mois = 1;
	}
	else if (mois > 12)
	{
		mois = 12;
	}
	m_currentMois = mois;
	etatActuel = Graphique1;
	return mois;
}
int CAffichage::AfficherGraphiqueAnnee(int annee)
{
	if (annee < 1896)
	{
		annee = 1896;
	}
	else if (annee > 2025)
	{
		annee = 2025;
	}
	m_currentAnnee = annee;
	etatActuel = Graphique2;
	return annee;
}
void CAffichage::AfficherGraphique()
{
	etatActuel = Graphique3;
}
void CAffichage::EffacerGraphique()
{
	etatActuel = None;
}

void CAffichage::Next()
{
	if (etatActuel == Graphique2)
	{
		m_currentAnnee += 1;
		AfficherGraphiqueAnnee(m_currentAnnee);
	}
	else if (etatActuel == Graphique1)
	{
		m_currentMois += 1;
		AfficherGraphiqueMois(m_currentMois);
	}
}

void CAffichage::Previous()
{
	if (etatActuel == Graphique2)
	{
		m_currentAnnee -= 1;
		AfficherGraphiqueAnnee(m_currentAnnee);
	}
	else if (etatActuel == Graphique1)
	{
		m_currentMois -= 1;
		AfficherGraphiqueMois(m_currentMois);
	}
}

//Fonction AffichagePrincipale

CAffichage::CAffichage(CApp& app, bool sombre)
{
	m_app = &app;
	m_sombre = sombre;
}

void CAffichage::Afficher()
{

	
	switch (etatActuel)
	{
	case CAffichage::None:
		DrawTitle("BIENVENUE DANS NOTRE APPLICATION");
		DrawSubTitle("Pour afficher des graphiques il suffit de cliquer sur les boutons ci-dessous.");
		break;
	case CAffichage::Graphique1:
	{
		DrawGraphiqueMois(m_currentMois);
		DrawTitle("GRAPHIQUE MOIS");
		std::vector<std::string> mois = { "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre" };
		std::stringstream os;
		os << "Mois : " << mois[m_currentMois-1];
		std::string sousTitre = os.str();
		DrawSubTitle(sousTitre);
		m_buttons[m_buttons.size() - 1].Afficher(m_sombre);
		m_buttons[m_buttons.size() - 2].Afficher(m_sombre);
		break;
	}
	case CAffichage::Graphique2:
	{
		DrawGraphiqueAnnee(m_currentAnnee);
		DrawTitle("GRAPHIQUE ANNEE");
		std::stringstream os;
		os << "Année : " << m_currentAnnee;
		std::string sousTitre = os.str();
		DrawSubTitle(sousTitre);
		m_buttons[m_buttons.size()-1].Afficher(m_sombre);
		m_buttons[m_buttons.size() - 2].Afficher(m_sombre);
		break;
	}
	case CAffichage::Graphique3:
		DrawGraphique();
		DrawTitle("GRAPHIQUE GENERAL :");
		break;
	default:
		break;
	}

	AfficherBtn();
}