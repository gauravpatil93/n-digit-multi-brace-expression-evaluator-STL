#include <iostream>
#include <stack>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;

/*
Function Prototypes
*/
int get_weight(char ch);
string infix_to_postfix(string infix_expression);
int evaluate_postfix(string postfix);
int eval(int op1, int op2, char operate);

int eval(int op1, int op2, char operate) {
	switch (operate) {
	case '*': return op2 * op1;
	case '/': return op2 / op1;
	case '+': return op2 + op1;
	case '-': return op2 - op1;
	default : return 0;
	}
}

int get_weight(char ch)
{
	switch (ch) {
	case '/':
		return 2;
	case '*':
		return 2;
	case '+':
		return 1;
	case '-':
		return 1;
	default:
		return 0;
	}
}

string infix_to_postfix(string infix_expression)
{
	string postfix;
	stack<char> stk;


	for (int iterator = 0; iterator < infix_expression.length(); iterator++) {
		if (isdigit(infix_expression[iterator])) {
			while (isdigit(infix_expression[iterator])) {
				postfix += infix_expression[iterator];
				iterator++;
			}
			postfix += " ";
			iterator--;
			continue;
		}
		if (!isdigit(infix_expression[iterator])) {

			if (infix_expression[iterator] == '(' || infix_expression[iterator] == '[' || infix_expression[iterator] == '{') {
				stk.push(infix_expression[iterator]);
				continue;
			}

			if (infix_expression[iterator] == ')') {
				while (!stk.empty() && stk.top() != '(') {
					postfix += stk.top();
					stk.pop();
				}

				if (!stk.empty()) {
					stk.pop();
				}
				continue;
			}

			if (infix_expression[iterator]  == ']') {
				while (!stk.empty() && stk.top() != '[') {
					postfix += stk.top();
					stk.pop();
				}
				if (!stk.empty()) {
					stk.pop();
				}
				continue;
			}

			if (infix_expression[iterator]  == '}') {
				while (!stk.empty() && stk.top() != '{') {
					postfix += stk.top();
					stk.pop();
				}
				if (!stk.empty()) {
					stk.pop();
				}
				continue;
			}

			if (infix_expression[iterator] == '+' || infix_expression[iterator] == '-' || infix_expression[iterator] == '*' || infix_expression[iterator] == '/') {
				int weight = get_weight(infix_expression[iterator]);
				if (stk.empty()) {
					stk.push(infix_expression[iterator]);
				}
				else {
					while ((!stk.empty() && (stk.top() != '('  || stk.top() != '[' || stk.top() != '{')) && weight <= get_weight(stk.top())) {
						postfix += stk.top();
						stk.pop();
					}
					stk.push(infix_expression[iterator]);
				}
			}
		}
	}
	while (!stk.empty()) {
		postfix += stk.top();
		stk.pop();
	}

	cout << "\n" << postfix;
	return postfix;
}

int evaluate_postfix(string postfix) {
	stack<int> int_stack;
	string temp;
	int val;

	for (int iterator = 0; iterator < postfix.length(); iterator++) {
		if (isdigit(postfix[iterator])) {
			while (!isspace(postfix[iterator])) {
				temp += postfix[iterator];
				iterator++;
			}
			int_stack.push(stoi(temp));
			temp = "";
			continue;
		}
		if (!isdigit(postfix[iterator])) {
			int op1 = int_stack.top();
			int_stack.pop();
			int op2 = int_stack.top();
			int_stack.pop();
			val = eval(op1, op2, postfix[iterator]);
			int_stack.push(val);
			continue;
		}
	}
	return val;
}

int main()
{
	cout << "Expression: ";
	string expression;
	cin >> expression;
	string postfix_expression = infix_to_postfix(expression);
	cout << "\n Answer: ";
	cout << evaluate_postfix(postfix_expression);
	cout << "\n";
}
