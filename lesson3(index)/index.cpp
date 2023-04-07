#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <filesystem>

#include <regex>
using namespace std;


//void symbolFrequencies(string& text) { //������� ������� 
//	unordered_map<char, int> freq;//��������� ��� �������� 
//	for (const char& c : text)
//		freq[c]++;// ���������� �������� �� ���������� 
//
//	for (auto& pair : freq) {
//		v++;
//		cout << '{' << pair.first << ": " << pair.second << '}' << endl; //
//	}
//}



string filterWithoutSpace(string& text, string& ABC) { //����� ���������� ������ ��� �������� 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //���������, �������� �� ������ ������ ��������� ��� ���
		{
			filterText += v;
		}
		else if (isspace(v)) {
			continue; //���������� ������� 
		}
	}

	return filterText;
}

string filterSpace(string& text, string& ABC) {
	string filteredText = "";

	regex pattern("\\s+");//��� ���������� ������������������ �������� 
	string result = regex_replace(text, pattern, " ");  // ����� �� ���� �����

	for (char& c : result) {
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //���������, �������� �� ������ ������ ��������� ��� ���
		{
			filteredText += v;

		}
		else if (isspace(v)) {
			filteredText += ' '; //+ ������� 
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
	//string str1 = " ���� � ����� ����� ������ ,����� � ����� ������ �������  ";
	string path = "..\\file.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "������ ������ ����� " << endl;
	}
	else
	{
		cout << "���� ������" << endl;
		//char ch;
		//fin.get(ch) ������� ������ �� ��������� 

		string str;
		while (!fin.eof()) // ���������� ����� ����� 
		{
			str = ""; //��� ����������� ������	
			getline(fin, str);
			res += str;
		}
	}

	//cout << res << endl;

	fin.close();

	return res;
}

double indexOfCoincidence(string& text) {
	unordered_map<char, int> freqs; // unordered_map ��� �������� ������ ������ �����
	long long int total = 0; // ����� ���������� ���� � ������
	long double ic = 0.0; // ������ ����������

	// ������� ������ ������ �����
	for (char c : text) {
		if (c >= '�' && c <= '�') {
			freqs[c]++; // ����������� ������� ������� �� 1
			total++; // ����������� ������� �������� �� 1
		}
	}

	// ������ ������� ����������
	for (auto& pair : freqs) {
		ic += pair.second * (pair.second - 1);
	}
	long long int f = (total * (total - 1));
	ic /= f;

	return ic;
}

void Log() {
	string res = Text();

	string ABC = "��������������������������������";
	string withoutSpace = filterWithoutSpace(res, ABC); //��� ���
	//cout<<withoutSpace<<endl;
	string withSpace = filterSpace(res, ABC);//  � ���������
	//cout << withSpace << endl;
	double ic = indexOfCoincidence(withSpace);
	cout << "������ ���������� � ���������: \t" << ic << endl;

	double ic1 = indexOfCoincidence(withoutSpace);
	cout << "������ ���������� ��� ��������: \t" << ic1 << endl;

}


int main() {
	setlocale(LC_ALL, "RU");
	Log();
	return 0;

}