#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <filesystem>

#include <regex>
using namespace std;


//void symbolFrequencies(string& text) { //частоти символів 
//	unordered_map<char, int> freq;//контейнер для елементів 
//	for (const char& c : text)
//		freq[c]++;// добавляемо елементи до контецнеру 
//
//	for (auto& pair : freq) {
//		v++;
//		cout << '{' << pair.first << ": " << pair.second << '}' << endl; //
//	}
//}



string filterWithoutSpace(string& text, string& ABC) { //метод фильтрации текста без пробелов 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //проверяет, является ли данный символ алфавитом или нет
		{
			filterText += v;
		}
		else if (isspace(v)) {
			continue; //пропускаем пробелы 
		}
	}

	return filterText;
}

string filterSpace(string& text, string& ABC) {
	string filteredText = "";

	regex pattern("\\s+");//для нахождения последовательности пробелов 
	string result = regex_replace(text, pattern, " ");  // заміна на один пробіл

	for (char& c : result) {
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //проверяет, является ли данный символ алфавитом или нет
		{
			filteredText += v;

		}
		else if (isspace(v)) {
			filteredText += ' '; //+ пробелы 
		}
	}
	if (filteredText.back() == ' ') {
		filteredText.pop_back();
	}
	if (filteredText.front() == ' ') {
		filteredText.erase(0, 1);
	}
	return filteredText;
}


string Text() {
	//string str1 = " Карл у Клары Украл корали ,Карла у Карлы украла кларнет  ";
	string path = "..\\file.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "Ошибка вывода файла " << endl;
	}
	else
	{
		cout << "Файл открыт" << endl;
		//char ch;
		//fin.get(ch) выводит данные по символьно 

		string str;
		while (!fin.eof()) // отлвливает конец вайла 
		{
			str = ""; //для корректного счетия	
			getline(fin, str);
			res += str;
		}
	}

	//cout << res << endl;

	fin.close();

	return res;
}

double indexOfCoincidence(string& text) {
	unordered_map<char, int> freqs; // unordered_map для хранения частот каждой буквы
	long long int total = 0; // общее количество букв в тексте
	long double ic = 0.0; // индекс совпадений

	// подсчет частот каждой буквы
	for (char c : text) {
		if (c >= 'а' && c <= 'я') {
			freqs[c]++; // увеличиваем частоту символа на 1
			total++; // увеличиваем счетчик символов на 1
		}
	}

	// расчет индекса совпадений
	for (auto& pair : freqs) {
		ic += pair.second * (pair.second - 1);
	}
	long long int f = (total * (total - 1));
	ic /= f;

	return ic;
}

void Log() {
	string res = Text();

	string ABC = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
	string withoutSpace = filterWithoutSpace(res, ABC); //без них
	//cout<<withoutSpace<<endl;
	string withSpace = filterSpace(res, ABC);//  с пробелами
	//cout << withSpace << endl;
	double ic = indexOfCoincidence(withSpace);
	cout << "Индекс совпадений с пробелами: \t" << ic << endl;

	double ic1 = indexOfCoincidence(withoutSpace);
	cout << "Индекс совпадений без пробелов: \t" << ic1 << endl;

}


int main() {
	setlocale(LC_ALL, "RU");
	Log();
	return 0;

}
