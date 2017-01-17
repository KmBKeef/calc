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
	int sl = 0;
	for(unsigned int x = 0; x < infix.length(); x++) {
		char token = infix[x];
		switch(token) {
			case '+':
			case '-':
				if(op.top() == '0') {
					op.push(token);
					count++;
				}
				else {
					for(int f = 0; f < count; f++){
						rpn[sl] = op.top();
						sl++;
						op.pop();
					}
					op.push(token);
				}
				break;

			case '*':
			case '/':
				if(op.top() == '0' ||op.top() == '+' ||op.top() == '-') {
					op.push(token);
					count++;
				}
				else if(op.top() == '*' ||op.top() == '/') {
					for(int w = 0; w < count; w++) {
						if(op.top() == '*' || op.top() == '/') {
							rpn[sl] = op.top();
							op.pop();
							sl++;
						}
						else {
							break;
						}
					}
				}
				break;

			default:
				rpn[sl] = token;
				sl++;
				break;
		}
	}	

	for(int q = 0; q < count; q++) {
		rpn[sl] = op.top();
		op.pop();
		sl++;
	}

	cout << "RPN line: "<< rpn << endl;

	return 0;
}
