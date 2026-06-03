#pragma once
class CDate
{
private:
	int m_mois;
	int m_annee;

public:
	CDate(int annee = 0, int mois = 0);

	//GETTERS
	int getMois();
	int getAnnee();
};