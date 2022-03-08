// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//for, =

#include <iostream>
#include "Tables.h"

int main()
{
    Tables tables = Tables();

    string c = tables.separators.get(2);
    int i = tables.separators.search("{");

    trio id = tables.find("{");
     id = tables.find("a");
     id = tables.find("if");
     id = tables.find("for");
     string v = "hello";
     identifier var = identifier("a", 0,v );
     tables.variables.set(var);
     var = identifier("a", 0, v);
     tables.variables.search("a");
     id = tables.find("a");
     tables.variables.setvalue("a", "bi");
     tables.variables.getvalue(1, 0);
     tables.variables.settype(2, 1,0);
     tables.variables.gettype(1, 0);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
