#include "functions.h"

//Главная функция, на спуске объеденяет элементы в петли, на возврате объеденяет петли друг с другом
vector<Iter> LoopAndMerge(Iter Front, Iter Back, DList& List) {
	Iter IterJ = Front;
	Iter IterI = IterJ;

	bool LoopIsDone = false;
	while (true) {
		IterI = IterJ;
		++IterJ;
		while (true) {
			if (IterJ == List.end()) {
				LoopIsDone = true;
				break;
			}
			if (LastChar(*IterI) == (*IterJ).front()) {
				(IterI + 1).Pull(IterJ);
				break;
			}
			++IterJ;
		}
		if (LoopIsDone) {
			break;
		}
	}
	if (IterI == List.Back()) {
		return vector<Iter>({Front, IterI});
	}
	vector<Iter> Loops = LoopAndMerge(IterI + 1, Back, List);
	for (auto Loop = Loops.begin(); Loop != Loops.end(); Loop++) {
		if (*Loop != List.end()) {
			if (Merge(Front, IterI, *Loop, *(Loop+1))) {
				*Loop = *(Loop + 1) = List.end();
			}
		}
		Loop++;
	}

	Loops.push_back(Front);
	Loops.push_back(IterI);
	return Loops;
}
//Пытается из двух петель образовать петлю большего размера, если удалось, возвращает true
bool Merge(Iter Front1, Iter Back1, Iter Front2, Iter Back2) {
	Iter Front2AtStart = Front2;
	bool MergedSuccessfully = false;
	do {
		for (Iter IterI = Front1; IterI != Back1+1; ++IterI) {
			if ((*IterI)[0] == (*Front2)[0]) {
				IterI.Pull(Front2, Back2);
				MergedSuccessfully = true;
				break;
			}
		}
		if (MergedSuccessfully) {
			break;
		}
		if (Front2 != Back2) {
			--Back2;
			Front2.Pull(Back2 + 1);
			--Front2;
		}
	} while (Front2 != Front2AtStart);
	return MergedSuccessfully;
}
//Последняя буква кторая не ь, ъ или ы
wchar_t LastChar(wstring Word) {
	const int n = Word.size();
	if (Word[n - 1] == L'ь' || Word[n - 1] == L'ъ' || Word[n - 1] == L'ы') {
		return Word[n - 2];
	}
	else {
		return Word[n - 1];
	}
}
//Нужна, чтобы понять, решилась ли задача
int AmountOfLoops(vector<Iter> Loops, DList& List) {
	int Count = 0;
	for (auto& Loop : Loops) {
		if (Loop != List.end()) {
			Count++;
		}
	}
	return (Count / 2);
}

void IsThisRussian(wstring Word) {
	static const wstring Alph = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	static const wstring ALPH = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	static const wstring BadLetters = L"ьъы";
	for (wchar_t LetterFromWord : Word) {
		if (!IsIn(LetterFromWord, Alph)) {
			if (IsIn(LetterFromWord, ALPH)) {
				throw wstring(L"Слово \"") + Word + wstring(L"\" содержит заглавную букву! (Используйте только строчные буквы)");
			}
			else {
				throw wstring(L"Слово \"") + Word + wstring(L"\" содержит недопустимый символ \"") + wstring({LetterFromWord}) + wstring(L"\"! (слова могут содержать только буквы русского алфавита)");
			}
		}
	}
	if (IsIn(Word[0],BadLetters)) {
		throw wstring(L"Слово \"") + Word + wstring(L"\" начинается на недопустимый символ \"") + wstring({Word[0]}) + wstring(L"\"! (слова не могут начинаться на ь, ъ или ы)");
	}
	if (Word.size() > 1) {
		if (IsIn(Word[Word.size()-2],BadLetters) && IsIn(Word[Word.size() - 1], BadLetters)) {
			throw wstring(L"Слово \"") + Word + wstring(L"\" кончается на недопустимую комбинацию букв \"") + wstring({Word[Word.size() - 2], Word[Word.size() - 1]}) + wstring(L"\"!");
		}
	}
}

bool IsIn(wchar_t Letter, const wstring& Alph) {
	bool LetterExists = false;
	for (wchar_t LetterFromAlph : Alph) {
		if (Letter == LetterFromAlph) {
			LetterExists = true;
			break;
		}
	}
	return LetterExists;
}

bool IsThereAnySolution(Iter Begin, Iter End) {
	vector<int> LettersBalance(34);
	for (Iter IterI = Begin; IterI != End; ++IterI) {
		LettersBalance[(*IterI)[0] - 1072]++;				//ё - 1105 Почему боже???
		LettersBalance[LastChar(*IterI) - 1072]--;
	}
	for (int i : LettersBalance) {
		if (i != 0) {
			return false;
		}
	}
	return true;
}