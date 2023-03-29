#include "ModuleTests.h"
#include "DataInput.h"
#include <sstream>

bool Check(Patient *testArray,Patient *testArrayFile, ui lim)
{
    for (ui i = 0; i < lim; i++) {
        if (testArray[i].GetName() != testArrayFile[i].GetName() ||
            testArray[i].GetSurname() != testArrayFile[i].GetSurname() ||
            testArray[i].GetPatronimyc() != testArrayFile[i].GetPatronimyc() ||
            testArray[i].GetAdress() != testArrayFile[i].GetAdress() ||
            testArray[i].GetDiagnosis() != testArrayFile[i].GetDiagnosis() ||
            testArray[i].GetMedicalCardNumber() != testArrayFile[i].GetMedicalCardNumber()
            ) return false;
                
    }
    return true;
}

bool Test1()
{
    //проверка ввода данных с файла
    cout << "\tTEST#1\n\tTesting file input...\n\n";

    fstream fin;
    const string fileName = "test_info.txt";
    fin.open(fileName, ios::in);

    if (!fin) {
        cout << "FAILURE!\nError opening file!\n\n";
        return false;
    }

    ui numberOfPatients = 0;
    Patient testArray[ValuesForModuleTests::first];
    testArray[0].SetInformation("Ilya", "Ekkert", "Denisovich", "Berlin", "Tourette_Syndrome", 1);
    testArray[1].SetInformation("Alina", "Galkina", "Aleksandrovna", "Pervomayka", "Koshmar", 2);
    
    Patient* testArrayFile = FileInput(fin, numberOfPatients, fileName);
    
    if (!Check(testArray, testArrayFile, ValuesForModuleTests::first)) {
        cout << "FAILURE!\nValues from inside the program and values from the test file do not match!\n\n";
        return false;
    }

    return true;

}

bool Test2()
{
    //фильтр по диагнозу
    cout << "\tTEST#2\n\tTesting diagnosis filter function...\n\n";

    fstream fin;
    const string fileName = "test_info.txt";
    fin.open(fileName, ios::in);
    string chosenDiagnosis = "koshmar";
    string res = "", resFile="";

    if (!fin) {
        cout << "FAILURE!\nError opening file!\n\n";
        return false;
    }

    ui numberOfPatients = 0;
    Patient testArray[ValuesForModuleTests::second];
    testArray[0].SetInformation("Ilya", "Ekkert", "Denisovich", "Berlin", "Tourette_Syndrome", 1);
    testArray[1].SetInformation("Alina", "Galkina", "Aleksandrovna", "Pervomayka", "Koshmar", 2);

    Patient* testArrayFile = FileInput(fin, numberOfPatients, fileName);

    for (ui i = 0; i < ValuesForModuleTests::second; i++) {
        if (Comparison(testArray[i].GetDiagnosis(), chosenDiagnosis)) res = testArray[i].GetFIO();
    }
    for (ui i = 0; i < numberOfPatients; i++) {
        if (Comparison(testArrayFile[i].GetDiagnosis(), chosenDiagnosis)) resFile = testArrayFile[i].GetFIO();
    }

    if (res != resFile) {
        cout << "FAILURE!\nIncorrect answer\n\n";
        return false;
    }
    return true;
}

bool Test3()
{   
    //фильтр по диапазону
    cout << "\tTEST#3\n\tTesting range filter function...\n\n";

    fstream fin;
    const string fileName = "test_info.txt";
    fin.open(fileName, ios::in);
    string chosenDiagnosis = "koshmar";
    string res = "", resFile = "";

    if (!fin) {
        cout << "FAILURE!\nError opening file!\n\n";
        return false;
    }

    ui numberOfPatients = 0;
    Patient testArray[ValuesForModuleTests::third];
    testArray[0].SetInformation("Ilya", "Ekkert", "Denisovich", "Berlin", "Tourette_Syndrome", 1);
    testArray[1].SetInformation("Alina", "Galkina", "Aleksandrovna", "Pervomayka", "Koshmar", 2);
    testArray[2].SetInformation("Anastasia", "Runina", "Sergeevna", "Astrakhan", "Children", 3);

    Patient* testArrayFile = FileInput(fin, numberOfPatients, fileName);

    ui lowerRange = 3, upperRange = 4;

    for (ui i = 0; i < ValuesForModuleTests::third; i++) {
        if (testArray[i].GetMedicalCardNumber() >= lowerRange && testArray[i].GetMedicalCardNumber() <= upperRange) res = testArray[i].GetFIO();
    }

    for (ui i = 0; i < numberOfPatients; i++) {
        if (testArrayFile[i].GetMedicalCardNumber() >= lowerRange && testArrayFile[i].GetMedicalCardNumber() <= upperRange) resFile = testArrayFile[i].GetFIO();
    }

    if (res != resFile) {
        cout << "FAILURE!\nIncorrect answer\n\n";
        return false;
    }

    return true;
}

bool Test4()
{
    //корректность счёта строк в файле
    cout << "\tTEST#4\n\tTesting correctness of counting lines in a file...\n\n";
    
    fstream fin;
    const string fileName = "test_info.txt";
    fin.open(fileName, ios::in);

    if (!fin) {
        cout << "FAILURE!\nError opening file!\n\n";
        return false;
    }

    ui numberOfPatients = 0;

    Patient* testArrayFile = FileInput(fin, numberOfPatients, fileName);

    if (numberOfPatients != ValuesForModuleTests::fourth) {
        cout << "FAILURE!\nIncorrect amount of data in the file!\n\n";
        return false;
    }

    return true;
}

bool Test5()
{
    //корректность работы ввода с консоли
    cout << "\tTEST#5\n\tTesting console input...\n\n";
    {
        istringstream test("576\n\n");
        streambuf* cinbuf = cin.rdbuf(test.rdbuf());

        bool res = (GetInt("") == 576);

        if (!res) {
            cout << "FAILURE!\nIncorrect console input!\n\n";
            return false;
        }

        cin.rdbuf(cinbuf);
    }
    return true;

}

void LaunchAllTests()
{
    bool tests[5] = { Test1(), Test2(), Test3(), Test4(), Test5() };
    //bool tests[5] = { Test1(), Test2(), Test3(), Test4(), true };
    for (ui i = 0; i < 5; i++) {
        if(!tests[i]) cout << "TEST#" << i + 1 << "\tFAILURE!\n\n";
    }

    if (tests[0] && tests[1] && tests[2] && tests[3] && tests[4]) cout << "All tests SUCCEDED!\n\n";
    else cout << "Some of the tests failed\n\n";
}
