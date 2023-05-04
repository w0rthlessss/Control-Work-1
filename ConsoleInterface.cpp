#include "ConsoleInterface.h"
#include "ModuleTests.h"
#include "Tasks.h"
#include <filesystem>

using namespace filesystem;

//если пользователь выбрал ввод с консоли
void WorkWithConsole(Patient* patients, int& actionBottom)
{
	ui numberOfPatients = 0;
	actionBottom = 1;

	//инициализация и заполнение массива пациентов
	patients = ConsoleInput(numberOfPatients);
	PrintPatients(patients, numberOfPatients);
	while (actionBottom != BottomMenu::back) {

		OptionsBottom();
		actionBottom = GetInt(">>");
		switch (actionBottom)
		{
		case BottomMenu::chooseDiagnosis:
			SearchDiagnosis(TopMenu::console, numberOfPatients, patients);
			break;
		case BottomMenu::chooseRange:
			SearchCardNumber(TopMenu::console, numberOfPatients, patients);
			break;
		case BottomMenu::back:

			system("cls");
			Fio();
			break;
		default:
			IncorrectOption();
			break;
		}
	}
	delete[]patients;
}

//если пользователь выбрал ввод с файла
void WorkWithFile(Patient* patients, int& actionBottom)
{
	ui numberOfPatients = 0;
	actionBottom = 1;
	fstream docIn, docOut;
	do {
		string inputName = OpenFile(WorkWithFiles::input, docIn);
		patients = FileInput(docIn, numberOfPatients, inputName);
		docIn.close();
	} while (patients == nullptr);
	PrintPatients(patients, numberOfPatients);
	while (actionBottom != BottomMenu::back) {
		OptionsBottom();

		actionBottom = GetInt(">>");
		switch (actionBottom)
		{
		case BottomMenu::chooseDiagnosis:
			SearchDiagnosis(TopMenu::file, numberOfPatients, patients);
			break;
		case BottomMenu::chooseRange:
			SearchCardNumber(TopMenu::file, numberOfPatients, patients);
			break;
		case BottomMenu::back:
			
			system("cls");
			Task();
			Fio();
			break;
		default:
			IncorrectOption();
			break;
		}
	}
	delete[]patients;
}

void PrintPatients(Patient* patients, ui numberOfPatients)
{
	cout << "\nPatient list:\n";
	for (ui i = 0; i < numberOfPatients; i++) {
		cout << "#" << i + 1 << ": " << patients[i].GetFIO() << ' ' << patients[i].GetAdress() << 
			' '<< patients[i].GetDiagnosis() << ' ' << patients[i].GetMedicalCardNumber() << endl;
	}
}

//вывод на консоль данных о разработчике
void Fio()
{
	cout << "Control work #1\nEfremov Ivan Andreevich\nGroup #423\nVariant #8\n\n";
}

//вывод на консоль верхнего меню
void OptionsTop()
{
	cout << "1 - Console input\n2 - File input\n3 - Run module tests\n4 - Exit\n\n";
}

//вывод на консоль нижнего меню
void OptionsBottom()
{
	cout << "\n\n1 - List of patients with chosen diagnosis\n";
	cout << "2 - List of patients with medical card number within chosen range\n";
	cout << "3 - Back\n\n";
}

//формулировка задания
void Task()
{
	cout << "Create class \"Patient\", including fields \"name\", \"surname\", \"patronimyc\", \"adress\", \"diagnosis\", \"medical card number\".\n";
	cout << "Create an array of objects. Realize filtration of patients by:\n";
	cout << "1 - chosen diagnosis\n2 - number of medical card in a certain range\n";
	cout << "\nData of each patient in the file must be written as:\n";
	cout << "\"name_1\" \"surname_1\", \"patronimyc_1\", \"adress_1\", \"diagnosis_1\", \"medical card number_1\"\n";
	cout<<".\n.\n.\n\"name_n\" \"surname_n\", \"patronimyc_n\", \"adress_n\", \"diagnosis_n\", \"medical card number_n\"\n\n";
}

//вывод на консоль ФИО пациента под номером
void OutputConsole(Patient a, int patientNum)
{
	cout << "#" << patientNum << ": ";
	a.ShowFIO();
}

//вывод на консоль выбора пользователя по считыванию данных
void InputOption(int option)
{
	if (option == TopMenu::console) {
		cout << "\n<<Console Input>>\n\n";
	}
	else if(option == TopMenu::file){
		cout << "\n<<File Input>>\n\n";
	}
}

//вывод в файл ФИО пациента под номером
void OutputFile(fstream &fout, string o, int patientNum)
{
	fout << "#" << patientNum << ": ";
	fout << o << '\n';
}

//если выбран некорректный пункт меню
void IncorrectOption()
{
	cout << "There is no such option in menu!\n";
}

//предложить пользователю сохранить данные в файл при вводе с консоли
char SaveResults(fstream &fout)
{
	string name;
	
	cout << "\nDo you want to save results in the file? (y/n)\n\n";
	char res = 'n';
	do {
		res = GetChar(">>");
		if (res != 'y' && res != 'n') {
			cout << "Incorrect input. Type 'y' or 'n' only!\n\n";
		}
	} while (res != 'y' && res != 'n');
	if (res == 'y') {
		name = OpenFile(WorkWithFiles::output, fout);
	}

	return res;
}

//запись данных из консоли в файл
void PrintConsoleData(fstream& fout, Patient* patients, ui numberOfPatients)
{
	for (ui i = 0; i < numberOfPatients; i++) {
		fout << patients[i].GetName() << ' ' <<
			patients[i].GetSurname() << ' ' <<
			patients[i].GetPatronimyc() << ' ' <<
			patients[i].GetAdress() << ' ' <<
			patients[i].GetDiagnosis() << ' ' <<
			patients[i].GetMedicalCardNumber() << endl;
	}
}

//открытие файла с двумя опциями: 0 - для считывания 1 - для записи
string OpenFile(int option, fstream &file) {
	string name = "";
	error_code ec;
	if (option == WorkWithFiles::input) {
		do {
			name = GetLink("\nEnter the name of file with data. Example: patients.txt\n");
			file.open(name, ios::in);
			if (!file.is_open()) {
				cout << "\nError opening file. Make sure, that file exists!\n";
				continue;
			}

			if (!is_regular_file(name, ec)) {
				cout << "\nAdress contains forbidden value. Try another file path!\n";
				continue;
			}
			return name;
		} while (true);
		

	}
	else {
		do {
			name = GetLink("\nEnter the name of file where results will be stored.\nIf there is data in the file it will be overwritten.\nExample: filtered.txt\n");

			file.open(name, ios::out, ios::trunc);

			if (!is_regular_file(name, ec)) {
				cout << "\nAdress contains forbidden value. Try another file path!\n";
				continue;
			}

			return name;
		} while (true);
		
	}
}

//основная структура программы
void StartProgram()
{
	Patient* patients = nullptr;
	int actionTop = 1, actionBottom = 1;
	Task();
	Fio();
	while (actionTop) {
		OptionsTop();
		actionTop = GetInt(">>");
		InputOption(actionTop);
		switch (actionTop)
		{
		case TopMenu::console:
			
			WorkWithConsole(patients, actionBottom);
			break;

		case TopMenu::file:
			WorkWithFile(patients, actionBottom);
			break;

		case TopMenu::module:
			LaunchAllTests();
			break;

		case TopMenu::quit:
			cout << "\nProgramm finished it's work!\n";
			exit(EXIT_SUCCESS);

		default:

			IncorrectOption();
			break;

		}
	}
}
