#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>

#include "DList.h"

using namespace std;

vector<Iter> LoopAndMerge(Iter Front, Iter Back, DList& List);
bool Merge(Iter Front1, Iter Back1, Iter Front2, Iter Back2);
wchar_t LastChar(wstring Word);
int AmountOfLoops(vector<Iter> Loops, DList& List);
void IsThisRussian(wstring Word);
bool IsIn(wchar_t Letter, const wstring& Alph);
bool IsThereAnySolution(Iter Begin, Iter End);