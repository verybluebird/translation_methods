#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct identifier {
	string name;
	int type;
	string value;
};

class const_table {

public:
	vector<string> table;
	const_table(string filename);// читать из файла
	string get(int number);
	int search(string value);
};

class variable_table {

public:
	vector<identifier> table;
	variable_table();
	void set(int number, string value);
	string get(int number);
};

