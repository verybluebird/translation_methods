#include "dfa.h"

DFA::DFA(Tables& tab)
{
	tables = tab;
	read_matr();
}

void DFA::read_matr()
{
	matrix.resize(32);
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i].resize(18);
	}
	ifstream rfile("matr.txt");
	if (rfile.is_open()) {
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++)
				rfile >> matrix[i][j];
	}
	rfile.close();
}

void DFA::print_tokens()
{
	ofstream fout("tokens.txt");
	for (int i = 0; i < tokens.size(); ++i)
	{
		fout << "(" << tokens[i].table << ", " << tokens[i].ind << ", " << tokens[i].sind << ")\n";
	}
	fout.close();
	//tables.constants.print_table("constant_table.txt");
	//tables.variables.print_table("variable_table.txt");

}

void DFA::read_code(string filename)
{
	now.stat = 0;
	now.str = "";
	now.c = 0;
	tokens.clear();


	ifstream rfile(filename);
	if (rfile.is_open()) {
		char buff;
		string s;
		while (rfile.get(buff))
		{
			s.push_back(buff);
			next_state(s);
			if (now.stat == 0 && s != " ") {
				int p = tables.separators.search(s);
				if ( p!= -1)
					tokens.push_back(trio(6, p));
			}
			s = "";
		}
		s = "eof";
		next_state(s);
		s = "";
	}
	rfile.close();
}

int DFA::find_way(string c)
{
	
	if (c == "=") {
		return 0;
	}
	if (c == "|") {
		return 1;
	}
	if (c == "&") {
		return 2;
	}
	if (c == "+" || c == "-") {
		return 3;
	}
	if (c == "*" ) {
		return 4;
	}
	if (c == "f") {
		return 5;
	}
	if (c == "i") {
		return 6;
	}
	if (c == "n") {
		return 7;
	}
	if (c == "t") {
		return 8;
	}
	if (c == "o") {
		return 9;
	}
	if (c == "r") {
		return 10;
	}
	if (tables.separators.search(c) != -1) {
		return 12;
	}
	if (tables.alphabet.search(c) != -1) {
		return 11;
	}
	
	if (c == "/") {
		return 13;
	}
	if (tables.digits.search(c) != -1) {
		return 14;
	}
	if (c == "eof") {
		return 15;
	}
	if (c == "\n" || c == "\t") {
		return 16;
	}
	return 17;
}


void DFA::next_state(string s)
{
	curr++;
	char c = s[0];
	int way = find_way(s);
	int next_st = matrix[now.stat][way];
	now.c = c;
	if (next_st == 0)
	{
		now.str = "";
		/*int p = tables.separators.search(now.str);
		tokens.push_back(trio(1, p));*/
		return;
	}
	if (next_st == 26 || next_st == 25)
	{
		cerr <<  "Error in " << curr << ", "<< now.str <<"\nUnclosed comment "<< endl;
	}
	if (next_st == 22 || next_st == 24 || next_st == 27 || next_st == 28 || next_st == 29 || next_st == 30 || next_st == 31)
	{
		cerr << "Error in " << curr << ", " << now.c << "\nUnexpected char" << endl;
	}
	if (next_st != -1)
	{
		now.str.push_back(c);
		now.stat = next_st;
		now.c = 0;
	}
	if (next_st == -1)
	{
		switch (now.stat)
		{
		default:
			break;
		case (2):
		case (3):
		case (9):
		case (10):
		case (11):
		case (12):
		case (13):
		{
			int p = tables.operations.search(now.str);
			tokens.push_back(trio(1,p));
			now.str = "";
			now.stat = 0;
			break;
		}
		case (8):
		case(14):
		case(15):
		case(19):
		case(20):

		{
			identifier id = identifier(now.str, 0, "");
			pair <int, int> p = tables.variables.set(id);
			tokens.push_back(trio(3, p));
			now.str = "";
			now.stat = 0;
			break;
		}
		case (16):
		case (21):
		{
			int p = tables.words.search(now.str);
			tokens.push_back(trio(0, p));
			now.str = "";
			now.stat = 0;
			break;
		}
		case(1):
		{
			identifier id = identifier(now.str, 0, "");
			pair <int, int> p = tables.constants.set(id);
			tokens.push_back(trio(2, p));
			now.str = "";
			now.stat = 0;
			break;
		}
		case (5):
		case (7): {
			now.str = "";
			now.stat = 0;
			break;
		}
		}
	}

}
