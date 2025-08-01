#include "functions.h"

void main() {
	std::locale::global(std::locale(""));

	try {
		wifstream Input("InputFile.txt");
		if (!Input.is_open()) {
			wofstream Input("InputFile.txt");
			Input.close();
			wofstream Output("OutputFile.txt");
			Output.close();
			wcout << L"Файлы \"InputFile.txt\" и \"OutputFile.txt\" были созданы в рабочей директории.\n";
			return;
		}
		Input.imbue(std::locale(Input.getloc(),new codecvt_utf8<wchar_t, 0x10FFFF, consume_header>()));

		DList ListOfWords;

		wstring TmpWord;
		while (Input >> TmpWord) {
			IsThisRussian(TmpWord);
			ListOfWords.PushBack(TmpWord);
		}
		Input.close();

		if (ListOfWords.IsEmpty()) {
			wofstream Output("OutputFile.txt");
			Output.close();
			throw wstring(L"Файл \"InputFile.txt\" не содржит не одного слова!");
		}

		if (!IsThereAnySolution(ListOfWords.begin(), ListOfWords.end())) {
			wcout << L"Решений не существует!\n";
			wofstream Output("OutputFile.txt");
			Output.close();
			return;
		}
		
		bool OnlyOneLoopLeft = (AmountOfLoops(LoopAndMerge(ListOfWords.begin(), ListOfWords.Back(), ListOfWords), ListOfWords) == 1);

		if (OnlyOneLoopLeft) {
			wcout << L"Решение успешно найденно! Результат сохранён в \"OutputFile.txt\"\n";
			wofstream Output("OutputFile.txt");
			Output.imbue(std::locale(Output.getloc(), new std::codecvt_utf8<wchar_t, 0x10FFFF, std::generate_header>()));

			for (const wstring& Word : ListOfWords) {
				Output << Word << ' ';
			}

			Output.close();
		}
		else {
			wcout << L"Решений не существует!\n";
			wofstream Output("OutputFile.txt");
			Output.close();
		}
	}
	catch (wstring& ErrorMesage) {
		wcout << L"Ошибка: " << ErrorMesage << '\n';
		wcout << L"Не удалось решить задачу.\n";
	}


}