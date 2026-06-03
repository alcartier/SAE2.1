#pragma once
#include <string>
#include <vector>
#include "CReleveMeteo.h"



class CParsing
{
public:
	static std::vector<std::string> lireFichier(const std::string& nom_fichier);
	static std::vector<std::vector<std::string>> separerLignes(const std::vector<std::string>& lignes);
	static std::vector<CReleveMeteo> parseLigne(std::vector<std::vector<std::string>>& datas);
};