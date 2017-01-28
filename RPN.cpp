#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
	string infix;
	cout << "Infix: " << flush;
	cin >> infix;
	string rpn = infix;
	stack<char> op;
	op.push('0');
	int count = 0;
	int cCount;
	int sl = 0;
	for(unsigned int x = 0; x < infix.length(); x++) {
		char token = infix[x];
		switch(token) {
			case '+':
			case '-':
				if(op.top() == '0' || op.top() == '(') {
					op.push(token);
					count++;
					cCount = count;
				}
				else {
					for(int f = 0; f < cCount; f++){
						rpn[sl] = op.top();
						sl++;
						op.pop();
						count--;
					}
					op.push(token);
					count++;
				}

				cCount = count;
				break;

			case '*':
			case '/':
				if(op.top() == '0' || op.top() == '+' || op.top() == '-' || op.top() == '(') {
					op.push(token);
					count++;
					cCount = count;
				}
				else {
					for(int w = 0; w < cCount; w++) {
							rpn[sl] = op.top();
							op.pop();
							sl++;
							count--;
						
						if(op.top() != '*' && op.top() != '/' && op.top() != '^') {
							op.push(token);
							count++;
							break;
						}
					}
					cCount = count;
					cout << op.top();
				}
				break;

			case '^':
				if(op.top() != '^') {
					op.push(token);
					count++;
					cCount = count;
				}
				else {
					for(int d =0; d < cCount; d++) {
							rpn[sl] = op.top();
							op.pop();
							sl++;
							count--;
						
						if(op.top() != '^') {
							op.push(token);
							count++;
							break;
						}
					}
				}
				cCount = count;
				break;

			case '(':
				op.push(token);
				count++;
				cCount = count;
				break;
			case ')':
				for(int l =0; l < cCount; l++) {
					if(op.top() != '(') {
						rpn[sl] = op.top();
						op.pop();
						sl++;
						count--;
					}
					else if(op.top() == '(') {
						op.pop();
						count--;
						break;

					}
				}
				cCount = count;
				break;
			default:
				rpn[sl] = token;
				sl++;
				break;
		}
	}
	cout << "RPN line 1: " << rpn << endl;
	cout << "Op.top(): " << op.top() << endl;
	cout << "count: " << count << endl;
	for(int q = 0; q < cCount; q++) {
		rpn[sl] = op.top();
		op.pop();
		sl++;
	}
	rpn.erase(sl,(rpn.length()-sl));
	cout << "Sl: " << sl << endl;
	cout << "count: " << count << endl;
	cout << "op.top(): " << op.top() << endl;
	cout << "RPN line: "<< rpn << endl;

	return 0;
}
