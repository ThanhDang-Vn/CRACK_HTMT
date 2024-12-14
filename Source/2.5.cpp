#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std; 

void Note(vector<vector<char>> arr, string name) {
	system("cls") ; 
	cout << "How to get serial: " << endl ; 
	cout << "9 is Snake - C is food - D is Destination" << endl ; 
	cout << "Move Snake to eat all food(C) and then move to Destination (D)" << endl ; 
	cout << "1 Moving Snake reasonably to get serial correctly \n"  ;
	cout << "2.Avoid moving Snake circles \n" ;  

	cout << endl ; 
	cout << "----------------------------- \n" ; 
	cout << "Guideline: \n" ; 
	cout << "S - DOWN, A - LEFT, D - RIGHT, W - UP \n" ; 

	cout << endl ; 

	for (int i = 0 ; i < arr.size() ; i ++) {
		for (int j = 0 ; j < arr[i].size() ; j++) {
			cout << arr[i][j] << "  " ; 
		}
		cout << endl ; 
	}  

}

int TransferName(vector<vector<char>>& arr, string name, int& rb, int& cb, int& rd, int& cd) {
	int dl = 0 ; 
	int i = 0 ;
	for (int i = 0 ; i < name.size() ; i ++) {
		dl += name[i] ; 
	}

	int tmp ; 
	int div, mod ; 
	int tmp_div[30] ; 
	int tmp_mod[30] ; 
	for (int i = 0 ; i < name.size() ; i++) {
		tmp = int(name[i]) ; 
		tmp = int(name[i]) ^ int(dl) ; 
		dl -= tmp ; 
		if (dl < 0) dl = 256 + dl ; 
		div = (tmp - 256 * (tmp / 256)) / 16 ; 
		mod = (tmp - 256 * (tmp / 256)) % 16 ; 
		if (arr[div][mod] == '0') {
			arr[div][mod] = 'C' ; 
		} else return 0 ; 

		tmp_div[i] = div ; 
		tmp_mod[i] = mod ; 
	}

	dl = dl ^ tmp ; 
	tmp = tmp - dl ; 
	if (tmp < 0) tmp = 256 + tmp ; 
	div = (tmp - 256 * (tmp / 256)) / 16 ; 
	mod = (tmp - 256 * (tmp / 256)) % 16 ;

	if (arr[div][mod] == '0') {
		arr[div][mod] = 'D' ; 
	} else return 0 ; 

	rd = div ; 
	cd = mod ; 
	tmp = dl ; 
	div = (tmp - 256 * (tmp / 256)) / 16 ; 
	mod = (tmp - 256 * (tmp / 256)) % 16 ; 
	if (arr[div][mod] == '0') arr[div][mod] = '9' ; 
	else return 0 ; 

	rb = div ; 
	cb = mod ; 
	return 1; 

}

string getS(string s) {
	int len = 0 ; 
	string tmp = "" ; 
	while (s[len] != 0) {
		len++ ; 
	}
	tmp = s[len - 1] ; 
	return tmp ; 
}

void Show1(string &s)
{
	while (s.find("0000") != -1)
		s.replace(s.find("0000"), 4, "C");
	while (s.find("1111") != -1)
		s.replace(s.find("1111"), 4, "D");
	while (s.find("2222") != -1)
		s.replace(s.find("2222"), 4, "E");
	while (s.find("3333") != -1)
		s.replace(s.find("3333"), 4, "F");
}

void Show2(string &s)
{
	while (s.find("000") != -1)
		s.replace(s.find("000"), 3, "8");
	while (s.find("111") != -1)
		s.replace(s.find("111"), 3, "9");
	while (s.find("222") != -1)
		s.replace(s.find("222"), 3, "A");
	while (s.find("333") != -1)
		s.replace(s.find("333"), 3, "B");
}

void Show3(string &s)
{
	while (s.find("00") != -1)
		s.replace(s.find("00"), 2, "4");
	while (s.find("11") != -1)
		s.replace(s.find("11"), 2, "5");
	while (s.find("22") != -1)
		s.replace(s.find("22"), 2, "6");
	while (s.find("33") != -1)
		s.replace(s.find("33"), 2, "7");
}


int main() {
	int row = 16, col = 16 ; 
	int rb = 0, cb = 0, rd = 0, cd = 0 ; 
	
	vector<vector<char>> arr(row, vector<char>(col, '0')) ; 
	string name ; 
	while(true) {
		cout << "Enter Name: " ; 
		getline(cin, name) ; 
		if (TransferName(arr, name, rb, cb, rd, cd)) {
			Note(arr, name) ; 
			break ; 
		} 
	}

	string str ; 
	int k = 1 ; 
	while(k) {
		if (_kbhit()) {
			switch(_getch()) {
				case 'w': 
					if (getS(str) == "0") break ; 
					else arr[rb][cb] = '0' ; 
					if (rb - 1 < 0) break ;  
					rb-- ; 
					arr[rb][cb] = '9' ; 
					str = str + "1" ;
					system("cls") ; 
					Note(arr, name) ; 
					break ;

 				case 's': 
					if (getS(str) == "1") break ; 
					else arr[rb][cb] = '0' ; 
					if (rb + 1 > 15) break ; 
					rb ++ ; 
					arr[rb][cb] = '9' ; 
					system("cls") ; 
					str = str + "0" ; 
					Note(arr, name) ; 
					break ; 
				
				case 'a': 
					if (getS(str) == "3") break ; 
					else arr[rb][cb] = '0' ;
					if (cb - 1 < 0) break ; 
					cb-- ; 
					arr[rb][cb] = '9' ; 
					str = str + "2" ;
					system("cls") ; 
					Note(arr, name) ; 
					break ; 

				case 'd': 
					if (getS(str) == "2") break ; 
					else arr[rb][cb] = '0' ; 
					if (cb + 1 > 15) break ; 
					cb++ ; 
					arr[rb][cb] = '9' ; 
					str = str + "3" ; 
					system("cls") ; 
					Note(arr, name) ; 
					break ; 
			}
			if (cb == cd && rb == rd)
			{
				k = 0;
				break;
			}
		}
	}

	cout << "Name: " << name << endl ;  
	cout << "Move :" << str << endl ; 
	Show1(str);
	Show2(str);
	Show3(str);
	cout << "SERIAL is :" << str << endl;
	system("pause");
	return 0 ; 
}