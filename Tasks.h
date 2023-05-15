#pragma once

#include "DataInput.h"

bool Comparison(string diagnosis, string currentDiagnosis);

void SearchDiagnosis(int mode, ui numberOfPatients, Patient* patients);

void OutputDiagnosis(int mode, pair<Patient, bool>* filteredPatients, ui numberOfPatients, string chosenDiagnosis);

void SearchCardNumber(int mode, ui numberOfPatients, Patient* patients);

void OutputCardNumber(int mode, pair<Patient, bool>* filteredPatients, ui numberOfPatients, pair<ui, ui> ranges);
