#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Queue.h"
#include "Stack.h"

#pragma warning( disable : 4018; disable : 4081; disable : 4267)

using namespace std;

enum TypeElement { Operation, Value, Null };

class Lexema {
	string str;
	TypeElement type;
public:
	Lexema(string nstr = " ", TypeElement ntype = Null) : str(nstr), type(ntype) {};
	string getStr() { return str; }
	TypeElement getType() { return type; }
	friend ostream& operator << (ostream& out, Lexema& p) {
		out << "{" << p.str << ", ";

		if (p.type == Operation) {
			out << "operation";
		}
		else if (p.type == Value) {
			out << "value";
		};
		out << "}";

		return out;
	}
};

Queue<Lexema> lex(string input) {
	Queue<Lexema>res;
	input += ' ';
	int i = 0;
	string tmp = "";
	string op = "+-*/()";
	string sep = " \n\t";
	int state = 0;
	for (i = 0; i < input.size(); i++) {
		char c = input[i];
		int fres;
		switch (state) {
		case 0: // операция
			if (c >= '0' && c <= '9') {
				tmp = c;
				state = 1;

				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				tmp = c;
				Lexema l(tmp, Operation);
				res.Push(l);
				state = 0;

				break;
			}
			break;
		case 1: // число
			if (c >= '0' && c <= '9') {
				tmp += c;
				state = 1;

				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				Lexema l1(tmp, Value);
				res.Push(l1);
				tmp = c;
				Lexema l2(tmp, Operation);
				res.Push(l2);
				state = 0;

				break;
			}
			fres = sep.find(c);
			if (fres >= 0) {
				Lexema l(tmp, Value);
				res.Push(l);
				state = 0;

				break;
			}
			break;
		}
	}
	return res;
}

vector <Lexema> ReversePolska(Queue<Lexema>& q)
{
	vector <Lexema> res;
	Stack<Lexema> stack;
	int bkt = 0, priority1, priority2;
	string op = "+-/*";
	char c;

	for (int i = 1; i < q.GetSize() + 1; i++) {
		switch (q.GetElement(i).getType()) {
			case Operation:
				c = q.GetElement(i).getStr()[0];
				switch (c) {
				case '(':
						bkt++;

						break;
				case '+':case '-':case'*':case'/':
					if (stack.IsEmpty()) {
						stack.Push(q.GetElement(i));
						break;
					}

					priority1 = op.find(c) / 2;

					while (!stack.IsEmpty()) {
						priority2 = op.find(stack.Top().getStr()) / 2;
						if (priority1 <= priority2) { res.push_back(stack.Pop()); }
						else { break; }
					}

					stack.Push(q.GetElement(i));

					break;
				case ')':
					bkt--;

					break;
				}
				break;
			case Value:
				res.push_back(q.GetElement(i));

				break;
		}
		if ((i > 1) && (op.find(q.GetElement(i).getStr()[0]) != string::npos) && 
			(op.find(q.GetElement(i - 1).getStr()[0]) != string::npos)) throw exception("Error: Excess operation\n");
	}

	while (stack.IsEmpty() == false) res.push_back(stack.Pop());
	if (bkt != 0) throw exception("Error: Bracket problem\n");

	return res;
}

double Calculate(vector<Lexema>& vc) {
	Stack<double> stack;
	int i = 0;
	double o1;
	double o2;
	while (i < vc.size()) {
		string str = vc[i].getStr();
		if (vc[i].getType() == Value) { stack.Push(stod(str)); }
		else {
			if (stack.Size() >= 2) {
				o2 = stack.Pop();
				o1 = stack.Pop();
				char c = vc[i].getStr()[0];

				switch (c) {

				case '+':
					stack.Push(o1 + o2);
					break;

				case '-':
					stack.Push(o1 - o2);
					break;

				case '*':
					stack.Push(o1 * o2);
					break;

				case '/':
					stack.Push(o1 / o2);
					break;
				}
			}
		}
		i++;
	}

	return stack.Pop();
}

void BracketsCheck(Queue<Lexema>& q) {
	int lBkt = 0, rBkt = 0, pos = 1, tBkt = 0;

	for (pos; pos != q.GetSize() + 1; pos++) switch (q.GetElement(pos).getStr()[0]) {
		case '(':
			lBkt++;
			break;
		case ')':
			rBkt++;
			break;
	}

	if (lBkt == rBkt) cout << "Brackets are OK\n";
	else {
		if (lBkt > rBkt) {
			lBkt = 0;
			for (pos = 1; pos != q.GetSize() + 1; pos++) if (q.GetElement(pos).getStr()[0] == '(') {
					if (lBkt == rBkt) cout << "Excess ( - opening bracket - on position: " << pos << '\n';
					else lBkt++;
			}
		}
		if (lBkt < rBkt) {
			rBkt = 0;
			for (pos = 1; pos != q.GetSize() + 1; pos++) if (q.GetElement(pos).getStr()[0] == ')') {
				if (lBkt == rBkt) cout << "Excess ) - closing bracket - on position: " << pos << '\n';
				else rBkt++;
			}
		}
	}
}

void OperationsCheck(Queue<Lexema>& q) {
	string op = "+-/*";

	for (int i = 1; i < q.GetSize() + 1; i++) 
		if ((i > 1) && (op.find(q.GetElement(i).getStr()[0]) != string::npos) &&(op.find(q.GetElement(i - 1).getStr()[0]) != string::npos)) 
			cout <<	"Excess operation (" << q.GetElement(i).getStr()[0] << ") on position : " << i << '\n';
}