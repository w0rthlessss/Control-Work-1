#include "ConsoleInterface.h"
#include "ModuleTests.h"
#include "Tasks.h"

//если пользователь выбрал ввод с консоли
void WorkWithConsole(Patient* patients, int& actionBottom)
{
	ui numberOfPatients = 0;
	actionBottom = 1;

	//инициализация и заполнение массива пациентов
	patients = ConsoleInput(numberOfPatients);
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
		docOut.close();
		patients = FileInput(docIn, numberOfPatients, inputName);
		docIn.close();
	} while (patients == nullptr);
	
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
			Fio();
			break;
		default:
			IncorrectOption();
			break;
		}
	}
	delete[]patients;
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
	
	cout << "Do you want to save results in the file? (y/n)\n\n";
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

//открытие файла с двумя опциями: 0 - для считывания 1 - для записи
string OpenFile(int option, fstream &file) {
	string name = "";
	if (option == WorkWithFiles::input) {
		do {
			name = GetLink("\nEnter the name of file with data. Example: patients.txt\n");
			file.open(name, ios::in);
			if (!file.is_open()) {
				cout << "\nError opening file. Make sure, that file exists!\n";
			}

		} while (!file.is_open());
		return name;

	}
	else {
		do {
			name = GetLink("\nEnter the name of file where results will be stored.\nIf there is data in the file it will be overwritten.\nExample: filtered.txt\n");
			
			file.open(name, ios::out, ios::trunc);

		} while (!file.is_open());
		return name;
	}
}

//основная структура программы
void StartProgram()
{
	Patient* patients = nullptr;
	int actionTop = 1, actionBottom = 1;
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
