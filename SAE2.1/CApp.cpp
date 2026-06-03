#include "CApp.h"

//Constructeur
CApp::CApp(std::vector<CReleveMeteo> data)
{
	m_data = data;
}

//Getters :

std::vector<CReleveMeteo> CApp::getData() const
{
	return m_data;
}

std::vector<CReleveMeteo> CApp::getDataMois(int mois)
{
	std::vector<CReleveMeteo> resultat;
	for (int i = 0; i < m_data.size(); ++i)
	{
		if (m_data[i].getDate().getMois() == mois)
		{
			resultat.push_back(m_data[i]);
		}
	}
	return resultat;
}

std::vector<CReleveMeteo> CApp::getDataAnnee(int annee)
{
	std::vector<CReleveMeteo> temp;
	for(int i = 0; i < m_data.size();i++){
		if(m_data[i].getDate().getAnnee() == annee){
			temp.push_back(m_data[i]);
		}
	}
	return temp;
}

//Calcule la moyenne des temperatures sur une annee donnee
double CApp::moyenneAnnee(int annee)
{
	std::vector<CReleveMeteo> datas = getDataAnnee(annee);
	double total = 0;
	for (auto data : datas)
	{
		total += data.getTemperature();
	}
	total /= datas.size();
	return total;
}

//Renvoie la derniere annee où on a des donnee
int CApp::anneeMax()
{
	return m_data[m_data.size()-1].getDate().getAnnee();
}

//Renvoie la premiere annee où on a des donnee
int CApp::anneeMin()
{
	return m_data[0].getDate().getAnnee();
}

//Renvoie la temperature max
int CApp::tempMax()
{
	float tempMax = m_data[0].getTemperature();
	for(int i = 0; i < m_data.size(); i++){
		if(m_data[i].getTemperature() > tempMax){
			tempMax = m_data[i].getTemperature();
		}
	}
	return tempMax;
}

//Renvoie la temperature minimum;
int CApp::tempMin()
{
	float tempMin = m_data[0].getTemperature();
	for (int i = 0; i < m_data.size(); i++) {
		if (m_data[i].getTemperature() < tempMin) {
			tempMin = m_data[i].getTemperature();
		}
	}
	return tempMin;
}
