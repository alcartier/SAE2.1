#include "CParsing.h"
#include <fstream>
#include <iostream>

//Fonction pour lire le fichier ligne par ligne
std::vector<std::string> CParsing::lireFichier(const std::string& nom_fichier)
{
	std::vector <std::string> resultat;
	std::ifstream in(nom_fichier);
	//Vérifie que le fichier est correctement ouvert (accessible)
	if (!in.is_open())
	{
		std::cerr << "Problème d'ouverture du fichier.\n";
	}
	std::string line;
	//parcours du fichier
	while (!in.eof())
	{
		std::getline(in, line);
		if (line.empty())
		{
			continue;
		}
		resultat.push_back(line);
	}
	return resultat;
}

//Focntion pour separer les lignes avec d'un cote la date et de l'autre la temperature
std::vector<std::vector<std::string>> CParsing::separerLignes(const std::vector<std::string>& lignes)
{
	std::vector<std::vector<std::string>> resultat;
	for (auto ligne : lignes)
	{
		std::vector<std::string> elements;
		std::string element;
		for (char c : ligne)
		{
			if (c == ';')
			{
				elements.push_back(element);
				element.clear();
			}
			else
			{
				element += c;
			}
		}
		if (!element.empty())
		{
			elements.push_back(element);
		}
		resultat.push_back(elements);
	}
	return resultat;
}

//Renvoie un vector de CReleveMeteo qui contient la date bien ordonné et la température
std::vector<CReleveMeteo> CParsing::parseLigne(std::vector<std::vector<std::string>>& datas)
{
	std::vector<CReleveMeteo> resultat;
	for (int i = 0; i < datas.size(); ++i)
	{
		std::string annee;
		for (int j = 0; j < 4; ++j)
		{
			annee += datas[i][0][j];
		}
		std::string mois;
		for (int j = 4; j < 6; ++j)
		{
			mois += datas[i][0][j];
		}
		CReleveMeteo temp = { CDate(stoi(annee), stoi(mois)), stod(datas[i][1]) };
		resultat.push_back(temp);
	}
	return resultat;
}
