#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Point
{
	unsigned int x;
	unsigned int y;
};

unsigned int t1 = 0x00, t2 = 0x00;
string Name, serial;
unsigned int Namelen, Sizestr;
string str;
Point start, finish;
string key;

void Init() 
{
	for (int i = 3; i >= 0; i--)
	{
		char s = Name[i] & 0xff;
		t1 = t1 << 8;
		t1 = t1 + int(s);
	}
	Namelen = Name.length();
	for (int i = Namelen - 1; i >= 4; i--)
	{
		char s = Name[i] & 0xff;
		t2 = t2 << 8;
		t2 = t2 + int(s);
	}
}

int GETNUMBER(unsigned int num)
{
	unsigned int a = t1;
	unsigned int d = 0x5dc1;
	a = a * d;
	unsigned int c = 0x560b;
	d = 0;
	t1 = a % c;
	a = t2;
	d = 0x549d;
	a = a * d;
	c = 0x51a1;
	d = 0;
	t2 = a % c;
	a = t1;
	d = t2;
	a = a + d;
	c = num;
	unsigned int b = a % c;
	a = b;
	return a;
	
}

void Create() 
{
	unsigned int num = 0x14;
	unsigned int a = GETNUMBER(num);
	a += 0x14; 
	Sizestr = a;
	unsigned int b = 0;
	while (b < Sizestr*Sizestr)
	{
		num = 0x4;
		a = GETNUMBER(num) ; 
		if (a == 0)
			str += "=";
		else
			str += ".";
		b++;
	}

	num = Sizestr;
	start.x = GETNUMBER(num);
	start.y = GETNUMBER(num);

	do
	{
		num = Sizestr;
		finish.x = GETNUMBER(num);
	} while (start.x == finish.x);

	do
	{
		num = Sizestr;
		finish.y = GETNUMBER(num);
	} while (start.y == finish.y);

	a = start.x;
	unsigned int d = Sizestr;
	a = a * d;
	d = start.y;
	a += d;
	str[a] = 'S';

	a = finish.x;
	d = Sizestr;
	a = a * d;
	d = finish.y;
	a += d;
	str[a] = 'F';
}

bool Solvestr(int x, int y)
{
	if (x > Sizestr - 1 || x < 0 ||  y > Sizestr - 1 ||y < 0 )
		return false;
	if (str[x*Sizestr + y] == 'F') 
		return true;
	if (str[x*Sizestr + y] != '.' && str[x*Sizestr + y] != 'S')
		return false;
	str[x*Sizestr + y] = '+';

	if (Solvestr(x - 1, y) == true)
	{
		key += 'l';
		return true;
	}
	if (Solvestr(x + 1, y) == true)
	{
		key += 'r';
		return true;
	}
	if (Solvestr(x, y + 1) == true)
	{
		key += 'd';
		return true;
	}
	if (Solvestr(x, y - 1) == true)
	{
		key += 'u';
		return true;
	}
	str[x*Sizestr + y] = ' ';
	return false;
}

string GetKey()
{
	if (Solvestr(start.x, start.y))
	{
		string temp = "";
		for (int i = key.length() - 1; i >= 0; i--)
		{
			temp += key[i];
		}
		return temp;
	}
	else
	{
		return "False";
	}
}

int main()
{
	do {
		cout << "UserName(5 -> 8 char): ";
		cin >> Name;
	} while (Name.length() < 5 || Name.length() > 8);
	cout << "r: Down" << endl;
	cout << "l: Up" << endl;
	cout << "d: Right" << endl;
	cout << "u: Left" << endl;
	cout << "S: Starting Point" << endl;
	cout << "F: Finshing Point" << endl;
	Init();
	Create();
	cout << "\nKey: " << GetKey() << endl;
	system("pause");
	return 0 ; 
}