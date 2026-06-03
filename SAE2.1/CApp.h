#pragma once
#include <vector>
#include "CReleveMeteo.h"
class CApp
{
private:
	std::vector<CReleveMeteo> m_data = {};

public:

	CApp(std::vector<CReleveMeteo> data);

	std::vector<CReleveMeteo> getData() const;
	std::vector<CReleveMeteo> getDataMois(int mois);
	std::vector<CReleveMeteo> getDataAnnee(int annee);

	double moyenneAnnee(int annee);
	int anneeMax();
	int anneeMin();
	int tempMax();
	int tempMin();
};

