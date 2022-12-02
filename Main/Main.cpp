#include <iostream>
#include <string>
#include "Lex.h"

#pragma warning( disable : 4018 )

using namespace std;

int main() {
    string str = "(53 + 32 * 2) - 40 / 20\n\n";
    cout << "Answer = " << (53 + 32 * 2) - 40 / 20 << "\n" << str;

    Queue <Lexema> lex_res;
    lex_res = lex(str);
    cout << lex_res << '\n';

    vector <Lexema> polska;
    polska = ReversePolska(lex_res);
    for (int i = 0; i < polska.size(); i++) cout << polska[i] << " ";

    cout << "\n\nCalculate answer = " << Calculate(polska);

    return 0;
}