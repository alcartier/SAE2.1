#pragma once
#include "CDate.h"
class CReleveMeteo
{
private:
	CDate m_date;
	double m_temperature;
public:
	CReleveMeteo(CDate date, double temperature);

	//GETTERS
	CDate getDate();
	double getTemperature();
};

