#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct identifier 
{
	string name;
	int type;
	string value;
	identifier(string name, int type, string value);
	identifier();
};

class const_table 
{

public:
	vector<string> table;
	const_table(string filename);// читать из файла
	const_table();
	string get(int number);
	int search(string value);
};
struct trio
{
	int table;
	int ind;
	int sind;
	trio(int t, int i, int si = 0);
	trio(int t, pair <int, int> par_index);

};
/*---------------------------------*/

class variable_table 
{

public:
	vector<vector<identifier>> table; 
	variable_table();
	void settype(int type, int hash, int i);
	pair <int, int> set(identifier id);
	pair <int, int> setname(string name);
	void setvalue(string name, string value);
	pair <int, int> search(string name); 
	pair <int, int> search(identifier id);
	int gettype( int hash, int i);
	string getvalue(int hash, int i);
	int calc_hash(string name);
	
};
class Tables
{
public:

	const_table words, operations, separators, alphabet, digits;
	variable_table constants, variables;

	Tables();
	trio find(string c);

};


