#include "Patient.h"

//����������� �� ���������
Patient::Patient() {
	name = "";
	surname = "";
	patronimyc = "";
	adress = "";
	diagnosis = "";
	numberOfMedicalCard = 0;
}

//���������� ���� ����� �������
void Patient::SetInformation(string n, string s, string p, string a, string d, ui number) {
	name = n;
	surname = s;
	patronimyc = p;
	adress = a;
	diagnosis = d;
	numberOfMedicalCard = number;
}

//��������� �������� ���� "�������"
string Patient::GetDiagnosis() {
	return diagnosis;
}

//��������� �������� ���� "����� ���. �����"
ui Patient::GetMedicalCardNumber() {
	return numberOfMedicalCard;
}

//��������� ������ �� ����� "���", "�������" � "��������"
string Patient::GetFIO() {
	return name + " " + surname + " " + patronimyc;
}

//��������� �������� ���� "���"
string Patient::GetName()
{
	return name;
}

//��������� �������� ���� "�������"
string Patient::GetSurname()
{
	return surname;
}

//��������� �������� ���� "��������"
string Patient::GetPatronimyc()
{
	return patronimyc;
}

//��������� �������� ���� "�����"
string Patient::GetAdress()
{
	return adress;
}

//����� � ������� ������ �� ����� "���", "�������" � "��������"
void Patient::ShowFIO()
{
	cout << GetFIO() << endl;
}


