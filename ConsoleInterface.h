#pragma once
#include "Patient.h"
#include <fstream>

enum WorkWithFiles{input, output};
enum TopMenu{console = 1, file, module, quit};
enum BottomMenu{chooseDiagnosis = 1, chooseRange, back};

void WorkWithConsole(Patient *patients, int &actionBottom);

void WorkWithFile(Patient* patient, int& actionBottom);

void Fio();

void OptionsTop();

void InputOption(int option);

void OptionsBottom();

void Task();

void IncorrectOption();

char SaveResults(fstream& fout);

void PrintConsoleData(fstream &fout, Patient *patients, ui numberOfPatients);

void OutputConsole(Patient a, int cnt);

void OutputFile(fstream &fout, string o, int cnt);

string OpenFile(int option, fstream &file);

void StartProgram();