#pragma once

#include "GetInfo.h"

#define ui unsigned int

class Patient {
private:
	string name;
	string surname;
	string patronimyc;
	string adress;
	string diagnosis;
	ui numberOfMedicalCard;
public:
	Patient();
	void SetInformation(string n, string s, string p, string a, string d, ui number);
	string GetDiagnosis();
	ui GetMedicalCardNumber();
	string GetFIO();
	string GetName();
	string GetSurname();
	string GetPatronimyc();
	string GetAdress();
	void ShowFIO();
};
