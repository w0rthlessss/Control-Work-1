#include "Tasks.h"

//сравнение строк без учета регистра
bool Comparison(string diagnosis, string currentDiagnosis)
{
	if (diagnosis == currentDiagnosis) return true;
	else {
		if (diagnosis.length() == currentDiagnosis.length()) {
			for (int i = 0; i < diagnosis.length(); i++) {
				if (tolower(diagnosis[i]) != tolower(currentDiagnosis[i])) {
					return false;
				}
			}
			return true;
		}
		else return false;
	}
}

//сделать это в одной функции
//функция для поиска совпадений поля "диагноз" и записи ФИО таких людей в файл
void SearchDiagnosis(int mode, ui numberOfPatients, Patient* patients)
{
	string chosenDiagnosis = GetString("\nEnter the diagnosis you want to see patients with: ");

	pair<Patient, bool> *results = new pair<Patient, bool>[numberOfPatients];
	for (ui i = 0; i < numberOfPatients; i++) {
		if (Comparison(patients[i].GetDiagnosis(), chosenDiagnosis)) {
			results[i].second = true;
		}
		else results[i].second = false;

		results[i].first = patients[i];
	}

	OutputDiagnosis(mode, results, numberOfPatients, chosenDiagnosis);
}

//вывод пациентов с данным диагнозом в консоль или в файл
void OutputDiagnosis(int mode, pair<Patient, bool>* filteredPatients, ui numberOfPatients, string chosenDiagnosis)
{
	int cnt = 1;
	fstream fout;
	if (mode == TopMenu::console) {
		cout << "\nPatients with diagnosis of " << chosenDiagnosis << ":\n\n";
		for (ui i = 0; i < numberOfPatients; i++) {
			if (filteredPatients[i].second == true) {
				OutputConsole(filteredPatients[i].first, cnt);
				cnt++;
			}
		}
		cnt = 1;

		//предложить пользователю записать результат работы функции в файл
		char ans = SaveResults(fout);
		if (ans == 'y') {
			fout << "Patients with diagnosis of " << chosenDiagnosis << ":\n\n";
			for (ui i = 0; i < numberOfPatients; i++) {
				if (filteredPatients[i].second == true) {
					OutputFile(fout, filteredPatients[i].first.GetFIO(), cnt);
					cnt++;
				}
			}
		}
		fout.close();

	}
	else {
		string name = OpenFile(WorkWithFiles::output, fout);
		fout << "Patients with diagnosis of " << chosenDiagnosis << ":\n\n";
		for (ui i = 0; i < numberOfPatients; i++) {
			if (filteredPatients[i].second == true) {
				OutputFile(fout, filteredPatients[i].first.GetFIO(), cnt);
				cnt++;
			}
		}
		fout.close();
	}
}

//функция для поиска людей с номером мед. карты в определенном интервале и запись ФИО этих людей в файл
void SearchCardNumber(int mode, ui numberOfPatients, Patient* patients)
{
	pair<ui, ui> ranges = { 0, 1 };

	pair<Patient, bool>* results = new pair<Patient, bool>[numberOfPatients];

	//ввод и проверка корректности значений границ интервала
	do {
		ranges.first = static_cast<ui>(GetInt("\nEnter lower range of medical card numbers: "));
		ranges.second = static_cast<ui>(GetInt("Enter upper range of medical card numbers: "));
		
		if (ranges.first > ranges.second) {
			cout << "\nLower range must be less or equal to the upper range!\n";
			continue;
		}
		else if (ranges.first < 0 || ranges.second < 0) {
			cout << "\nBorders must be positive!\n";
			continue;
		}
		
		break;
	} while (ranges.first > ranges.second);
	
	cout << "\n";
	//fout << "\nPatients with medical card number in the range of [" << lowerRange << ":" << upperRange << "]:\n\n";

	for (ui i = 0; i < numberOfPatients; i++) {
		if (patients[i].GetMedicalCardNumber() >= ranges.first && patients[i].GetMedicalCardNumber() <= ranges.second) {
			results[i].second = true;
		}
		else results[i].second = false;

		results[i].first = patients[i];
	}

	OutputCardNumber(mode, results, numberOfPatients, ranges);

}

//вывод пациентов с номером карты в заданном отрезке в консоль или в файл
void OutputCardNumber(int mode, pair<Patient, bool>* filteredPatients, ui numberOfPatients, pair<ui, ui> ranges)
{
	int cnt = 1;
	fstream fout;
	if (mode == TopMenu::console) {
		cout << "Patients with medical card number in the range of [" << ranges.first << ":" << ranges.second << "]:\n\n";
		for (ui i = 0; i < numberOfPatients; i++) {
			if (filteredPatients[i].second == true) {
				OutputConsole(filteredPatients[i].first, cnt);
				cnt++;
			}
		}
		cnt = 1;

		//предложить пользователю записать результат работы функции в файл
		char ans = SaveResults(fout);
		if (ans == 'y') {
			fout << "Patients with medical card number in the range of [" << ranges.first << ":" << ranges.second << "]:\n\n";
			for (ui i = 0; i < numberOfPatients; i++) {
				if (filteredPatients[i].second == true) {
					OutputFile(fout, filteredPatients[i].first.GetFIO(), cnt);
					cnt++;
				}
			}
		}
		fout.close();

	}
	else {

		string name = OpenFile(WorkWithFiles::output, fout);
		fout << "Patients with medical card number in the range of [" << ranges.first << ":" << ranges.second << "]:\n\n";
		for (ui i = 0; i < numberOfPatients; i++) {
			if (filteredPatients[i].second == true) {
				OutputFile(fout, filteredPatients[i].first.GetFIO(), cnt);
				cnt++;
			}
		}
		fout.close();
	}
}

//функция для поиска людей с номером мед. карты в определенном интервале и вывод ФИО этих людей в консоль
/*void SearchCardNumber(ui numberOfPatients, Patient* patients)
{
	fstream fout;
	int lowerRange = 0, upperRange = 1, cnt = 1;

	//ввод и проверка корректности значений границ интервала
	do {
		lowerRange = GetInt("\nEnter lower range of medical card numbers: ");
		upperRange = GetInt("Enter upper range of medical card numbers: ");

		if (lowerRange > upperRange) {
			cout << "\nLower range must be less than upper range!\n";
			continue;
		}
		else if (lowerRange < 0 || upperRange < 0) {
			cout << "\nBorders must be positive!\n";
			continue;
		}

		break;
	} while (lowerRange > upperRange);

	//предложить пользователю записать результат работы функции в файл
	char ans = SaveResults(fout);

	cout << "\n";
	cout << "Patients with medical card number in the range of [" << lowerRange << ":" << upperRange << "]:\n\n";
	for (ui i = 0; i < numberOfPatients; i++) {
		if (patients[i].GetMedicalCardNumber() >= static_cast<ui>(lowerRange) && patients[i].GetMedicalCardNumber() <= static_cast<ui>(upperRange)) {
			if (ans == 'y') OutputFile(fout, patients[i].GetFIO(), cnt);
			OutputConsole(patients[i], cnt);
		}
	}

	if (!cnt) {
		cout << "There is no patients with medical card number within chosen range!\n";
	}
	if (ans == 'y') fout.close();

}*/
