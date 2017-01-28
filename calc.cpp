#include <iostream>
#include <string>
#include <stack>
#include<cmath> //Added so we could use pow()-power-.

using namespace std;
int main(int argc, char *argv[]){
	// Simple math expression calculator 3*4/3+5
	// to compile: g++ -Wall -o calc calc.cpp

	// TODO 0. fix infix2rpn --done
	// TODO 1. support multi-digits and decimal points 23.23*43.2
	// TODO 2. support paranthesis --done 
	// TODO 3. support power (^) operation --done
	// TODO 4. support functions like sin/cos/log

	cout << "Insert the operation sign(+,-,*,^,/) and numbers in infix : " << endl;
	string infix;
	getline(cin, infix, '\n');
	string rpn = infix;
	stack<float> numbers;

	// First lets convert from infix notation to Reverse Polish Notation (NPR)
	// This code could be buggy
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
	for(int q = 0; q < cCount; q++) {
		rpn[sl] = op.top();
		op.pop();
		sl++;
	}
	rpn.erase(sl,(rpn.length()-sl));


	cout << "RPN line: " << rpn << endl;

	// Now, lets parse and calculate the result
	for (unsigned int i = 0; i < rpn.length(); i++) {
		char token = (char)rpn[i];
		float a,b;
		switch(token) {
			case '+': 
				a = numbers.top();
				numbers.pop();
				b = numbers.top();
				numbers.pop();
				numbers.push(a+b);
				break;
			case '-':
				a = numbers.top();
				numbers.pop();
				b = numbers.top();
				numbers.pop();
				numbers.push(b-a);
				break;
			case '*':
				a = numbers.top();
				numbers.pop();
				b = numbers.top();
				numbers.pop();
				numbers.push(a*b);
				break;
			case '/':
				a = numbers.top();
				numbers.pop();
				b = numbers.top();
				numbers.pop();
				numbers.push(b/a);
				break;
			case '^':
				a = numbers.top();
				numbers.pop();
				b = numbers.top();
				numbers.pop();
				numbers.push(pow(b,a));
				break;
			default: // This must be a number, lets push it onto the stack
				numbers.push((float)(token-'0'));
				break;
		}
	}

	cout << "The result is: " << numbers.top() << endl;

	return numbers.top();
}

