#include "Tables.h"



const_table::const_table(string filename)
{
	ifstream rfile (filename);
	if (rfile.is_open()) { 
		string s;
		while (!rfile.eof()) { // keep reading until end-of-file
			getline(rfile, s);
			table.push_back(s);
		}
	}
	rfile.close();
}

string const_table::get(int number)
{
	return string();
}

int const_table::search(string value)
{
	return 0;
}

/*------------------------------------------*/
variable_table::variable_table()
{
}

void variable_table::set(int number, string value)
{
}

string variable_table::get(int number)
{
	return string();
}
