#include <iostream>
#include <string>
#include "Lex.h"

#pragma warning( disable : 4018 )

using namespace std;

int main() {
    string str = "(53 + 32 * 2) - 40 / 20";
    cout << "Answer = " << (53 + 32 * 2) - 40 / 20 << "\n" << str << "\n\n";

    Queue <Lexema> lex_res;
    lex_res = lex(str);
    cout << lex_res << '\n';

    try {
        vector <Lexema> polska = ReversePolska(lex_res);
        for (int i = 0; i < polska.size(); i++) cout << polska[i] << ' ';
        cout << "\n\nCalculate answer = " << Calculate(polska);
    }
    catch (exception exc) {
        cout << exc.what();
        BracketsCheck(lex_res);
        OperationsCheck(lex_res);
    }

    return 0;
}