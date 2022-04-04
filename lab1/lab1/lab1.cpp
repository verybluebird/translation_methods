#include "Tables.h"
#include "dfa.h"

int main()
{
    Tables tables = Tables();
    DFA dfa(tables);
    dfa.read_matr();
    dfa.read_code("code.txt");
    dfa.print_tokens();
}

