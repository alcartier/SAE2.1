#include "CDate.h"

//Constructeur pour initialiser les donnees membres
CDate::CDate(int annee, int mois){
	m_annee = annee;
	m_mois = mois;
}

//Renvoie la donnee membre du mois 
int CDate::getMois()
{
	return m_mois;
}

//Renvoie la donnee membre de l'annee 
int CDate::getAnnee()
{
	return m_annee;
}