#include "DataInput.h"
#include <fstream>
#include <algorithm>

const ui arguments = 6;

//���������� ������� �������� �� ����������� ������ ���. �����
void SortData(Patient* patients, ui numberOfPatients) {
	sort(patients, patients + numberOfPatients,
		[](Patient& x, Patient& y) ->bool {
			return x.GetMedicalCardNumber() < y.GetMedicalCardNumber();
		}
	);
}

//���������� ������ �� �������� � ���������� ������� ����������� ����������
void SplitString(string s, string *ans)
{
	string cur = "";
	ui cnt = 0;

	for (int i = 0; i < arguments; i++) ans[i] = "";

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			ans[cnt] = cur;
			cur = "";
			cnt++;
		}
		else if (i == s.length() - 1) {
			cur += s[i];
			ans[cnt] = cur;
		}
		else cur += s[i];
	}
}

//��������� ������ � ���������� ������� �������� ������ ��� ����� �������� � �������
Patient* ConsoleInput(ui &numberOfPatients)
{
	string n = "", s = "", p = "", a = "", d = "";
	string cn = "";
	Patient* patients = nullptr;
	numberOfPatients = static_cast<ui>(GetInt("\nEnter number of patients: "));

	patients = new Patient[numberOfPatients];

	for (ui i = 0; i < numberOfPatients; i++) {
		cout << "\nPatient " << i + 1 << ":\n";

		n = GetString("Enter name of patient #", i + 1);
		s = GetString("Enter surname of patient #", i + 1);
		p = GetString("Enter patronimyc of patient #", i + 1);
		a = GetString("Enter adress of patient #", i + 1);
		d = GetString("Enter diagnosis of patient #", i + 1);
		cn = "Enter medical card number of patient #" + to_string(i + 1) + ": ";
		ui cardNumber = static_cast<ui>(GetInt(cn));

		//���������� ����� ������ ��� i-���� ��������
		patients[i].SetInformation(n, s, p, a, d, cardNumber);

	}
	
	//���������� �������
	SortData(patients, numberOfPatients);

	return patients;
}

//��������� ������ � ���������� ������� �������� ������ ��� ����� �������� � �����
Patient* FileInput(fstream &fin, ui &numberOfPatients, string name)
{
	ui lineNumber = 0, j = 0, cardNumber=0;
	string tmp = "";
	char* trash;
	string args[6];
	Patient* patients = nullptr;

	//������� ���������� ������ � ������ ��������� � �����
	while (getline(fin, tmp)) {
		if (!tmp.empty()) numberOfPatients++;
	}
	fin.close();

	patients = new Patient[numberOfPatients];

	fin.open(name);

	while(getline(fin, tmp) && j < numberOfPatients) {
		lineNumber++;
		if (!tmp.empty()) {
			SplitString(tmp, args);
			for (int i = 0; i < arguments; i++) {
				if (args[i] == "" || args[i] == " ") {
					cout << "\nERROR!\nCheck file line #" << lineNumber << "\nIt may be incorrect space input or incorrect amount of values\n";
					cout << "Choose another file or edit the current one\n\n";
					delete[] patients;
					patients = nullptr;
					return patients;
				}
			}
			//���������� ������ � ������� ����� � ���� unsigned int
			cardNumber = static_cast<ui>(strtol(args[5].c_str(), &trash, 10));
			
			//�������� ���������� �� ������ ��������� � ���� unsigned int
			if (cardNumber != static_cast<ui>(stoi(args[5]))) {
				cout << "\nERROR!\nCheck file line #" << lineNumber << "\nCard number must be integer!\n";
				cout << "Choose another file or edit the current one\n\n";
				delete[] patients;
				patients = nullptr;
				return patients;
			}

			//���������� ����� ������ ��� i-���� ��������
			patients[j].SetInformation(args[0], args[1], args[2], args[3], args[4], cardNumber);
			j++;

		}
	}
	fin.close();

	//���������� �������
	SortData(patients, numberOfPatients);

	return patients;
}


