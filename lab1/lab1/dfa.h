#pragma once
#include "Tables.h"


enum token {
	WORD = 0,
	OPERATOR = 1,
	CONSTANT = 2,
	ID = 3,
	ERROR = 4,
	COMMENT = 5,
	SEPARATOR = 6
};
struct state {
	int stat;
	string str;
	char c;
	
};

class DFA {
public:
	DFA(Tables& tab);
	state now;
	void read_matr();
	vector<vector<int>> matrix; //матрица перехода
	Tables tables;
	void print_tokens();
	void read_code(string filename);
	int find_way(string c);
	void next_state(string c);
	int curr = 0;
	vector<trio> tokens;


};
