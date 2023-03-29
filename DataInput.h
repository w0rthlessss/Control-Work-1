#pragma once

#include "ConsoleInterface.h"

void SortData(Patient* patients, ui numberOfPatients);

void SplitString(string s, string* ans);

Patient* ConsoleInput(ui &numberOfPatients);

Patient* FileInput(fstream& fin, ui& numberOfPatients, string name);