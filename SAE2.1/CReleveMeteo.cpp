#include "CReleveMeteo.h"

//Constructeur pour initialiser les donnees membres
CReleveMeteo::CReleveMeteo(CDate date, double temperature)
{
	m_date = date;
	m_temperature = temperature;
}

//Renvoie la date dans un CDate
CDate CReleveMeteo::getDate()
{
	return m_date;
}

//Renvoie la température
double CReleveMeteo::getTemperature()
{
	return m_temperature;
}
