#include "Patient.h"

//конструктор по умолчанию
Patient::Patient() {
	name = "";
	surname = "";
	patronimyc = "";
	adress = "";
	diagnosis = "";
	numberOfMedicalCard = 0;
}

//заполнение всех полей объекта
void Patient::SetInformation(string n, string s, string p, string a, string d, ui number) {
	name = n;
	surname = s;
	patronimyc = p;
	adress = a;
	diagnosis = d;
	numberOfMedicalCard = number;
}

//получение значения поля "диагноз"
string Patient::GetDiagnosis() {
	return diagnosis;
}

//получение значения поля "номер мед. карты"
ui Patient::GetMedicalCardNumber() {
	return numberOfMedicalCard;
}

//получение строки из полей "имя", "фамилия" и "отчество"
string Patient::GetFIO() {
	return name + " " + surname + " " + patronimyc;
}

//получение значения поля "имя"
string Patient::GetName()
{
	return name;
}

//получение значения поля "фамилия"
string Patient::GetSurname()
{
	return surname;
}

//получение значения поля "отчество"
string Patient::GetPatronimyc()
{
	return patronimyc;
}

//получение значения поля "адрес"
string Patient::GetAdress()
{
	return adress;
}

//вывод в консоль строки из полей "имя", "фамилия" и "отчество"
void Patient::ShowFIO()
{
	cout << GetFIO() << endl;
}


