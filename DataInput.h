#pragma once

#include "ConsoleInterface.h"


void SplitString(string s, string* ans);

Patient* ConsoleInput(ui &numberOfPatients);

Patient* FileInput(fstream& fin, ui& numberOfPatients, string name);