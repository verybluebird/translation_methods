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

const_table::const_table()
{
}


string const_table::get(int number)
{	
	return table[number];
}

int const_table::search(string value)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (value == table[i])
		{
			return i;
		}

	}
	return -1;
}

/*------------------------------------------*/

variable_table::variable_table()
{
	table.resize(32);
}

void variable_table::settype(int type, int hash, int i)
{
	table[hash][i].type = type;
}

pair <int, int> variable_table::set(identifier id)
{
	unsigned int hash = calc_hash(id.name) % table.size();
	pair <int, int> index = search(id.name);
	if (index.first == -1)
	{
		table[hash].push_back(id);
		return { hash, table[hash].size() - 1 };
	}
	return { index.first, index.second };

}


pair <int, int> variable_table::setname(string name)
{
	unsigned int hash = calc_hash(name) % table.size();
	pair <int, int> index = search(name);
	identifier id(name, 0, "");
	if (index.first == -1)
	{
		table[hash].push_back(id);
		return { hash, table[hash].size() - 1 };
	}
	return { index.first, index.second };
}

void variable_table::setvalue(string name, string value)
{
	pair <int, int> index = search(name);
	
	if (index.first != -1)
	{
		table[index.first][index.second].value=value;		
	}
}

pair <int, int> variable_table::search(string name)
{
	int hash = calc_hash(name) % table.size();
	if (table[hash].size() == 0)
	{
		return { -1, 0 };
	}
	for (int i = 0; i < table[hash].size(); ++i)
	{
		if (table[hash][i].name == name)
		{
			return { hash, i };
		}
	}
	return { -1, 0 };

}

pair<int, int> variable_table::search(identifier id)
{
	return search(id.name);
}

int variable_table::gettype( int hash, int i)
{
	return table[hash][i].type;
}

string variable_table::getvalue( int hash, int i)
{
	return table[hash][i].value;
}

int variable_table::calc_hash(string name)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	for (unsigned int i = 0; i < name.length(); i++)
	{
		hash = hash * a + name[i];
		a = a * b;
	}
	return (hash & 0x7FFFFFFF);//убирает знаковый бит

}
/*------------------------------------------*/
identifier::identifier(string nam, int typ, string valu)
{
	name = nam;
	type = typ;
	value = valu;
}

identifier::identifier()
{
	name = "";
	type = 0;
	value = "0";
}
/*------------------------------------------*/
Tables::Tables()
{

	words = const_table("words.txt");
	operations = const_table("operations.txt");
	separators = const_table("separators.txt");
	alphabet = const_table("alphabet.txt");
	digits = const_table("digits.txt");
	variables = variable_table();
	constants = variable_table();
	
}

trio Tables::find(string c)
{
	int p;
	p = separators.search(c);
	if (p != -1)
		return trio(0, p);
	p = words.search(c);
	if ( p!= -1)
		return trio(1, p);
	p = operations.search(c);
	if ( p!= -1)
		return trio(2, p);
	pair <int, int> pa;
	pa = variables.search(c);
	if (pa.first != -1)
		return trio(3, pa);
	pa = constants.search(c);
	if (pa.first != -1)
		return trio(4, pa);
	return trio(-1, 0);

}
/*------------------------------------------*/
trio::trio(int t, int i, int si)
{
	table = t;
	ind = i;
	sind = si;
}

trio::trio(int t, pair<int, int> par_index)
{
	table = t;
	ind = par_index.first;
	sind = par_index.second;
	
}
