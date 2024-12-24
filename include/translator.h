#pragma once
#include <iostream>
#include <stdexcept>
#include <stack>
#include <string>
#include <vector>


class Translator {
private:
	std::vector<std::string> terms;
	std::string postfixExpression;
	bool isOper(char val)
	{
		return (val == '+' || val == '-' || val == '*' || val == '/' || val == '^');
	}

	bool isnum(char val)
	{
		return val >= '0' && val <= '9';
	}

	bool isemp(char val)
	{
		return val == ' ';
	}

	int priority(char op)
	{
		if (op == '+' || op == '-') {
			return 1;
		}
		else if (op == '*' || op == '/') {
			return 2;
		}
		else if (op == '^') {
			return 3;
		}
		return 0;
	}

	double operation(double operand1, double operand2, char op)
	{
		switch (op) {
		case '+': return operand1 + operand2;
		case '-': return operand1 - operand2;
		case '*': return operand1 * operand2;
		case '/':
			if (operand2 == 0) {
				throw std::runtime_error("Division by 0");
			}
			return operand1 / operand2;
		case '^': return pow(operand1, operand2);
		default: throw std::runtime_error("Incorrect operator");
		}
	}
	std::string infixToPostfix()
	{
		std::string postf;
		std::stack<std::string> operts;

		for (const std::string& term : terms) {
			if (isnum(term[0]) || (term[0] == '.' && term.size() > 1)) {
				postf += term + " ";
			}
			else if (term == "(") {
				operts.push(term);
			}
			else if (term == ")") {
				while (!operts.empty() && operts.top() != "(") {
					postf += operts.top() + " ";
					operts.pop();
				}
				if (!operts.empty()) {
					operts.pop();
				}
				else {
					throw std::runtime_error("Incorrect brackets");
				}
			}
			else if (isOper(term[0])) {
				while (!operts.empty() && priority(term[0]) <= priority(operts.top()[0])) {
					postf += operts.top() + " ";
					operts.pop();
				}
				operts.push(term);
			}
			else {
				throw std::runtime_error("Incorrect symbol: " + term);
			}
		}

		while (!operts.empty()) {
			postf += operts.top() + " ";
			operts.pop();
		}

		postf.pop_back();
		return postf;
	}

	void checkErrors() {
		int openBrackets = 0;
		bool lastWasOperator = false;
		bool hasOperand = false;

		if (terms.empty()) {
			throw std::runtime_error("Empty expression");
		}

		for (size_t i = 0; i < terms.size(); ++i) {
			const std::string& term = terms[i];

			if (term == "(") {
				openBrackets++;
				if (i > 0 && !isOper(terms[i - 1][0]) && terms[i - 1] != "(") {
					throw std::runtime_error("Invalid expression before opening parenthesis");
				}
			}
			else if (term == ")") {
				openBrackets--;
				if (openBrackets < 0) {
					throw std::runtime_error("Mismatched parentheses");
				}
				if (i > 0 && isOper(terms[i - 1][0])) {
					throw std::runtime_error("Invalid expression before closing parenthesis");
				}
			}
			else if (isOper(term[0])) {
				if (lastWasOperator || i == 0 || i == terms.size() - 1 || (i < terms.size() - 1 && terms[i + 1] == ")")) {
					throw std::runtime_error("Multiple operators in a row or operator at beginning/end");
				}
				lastWasOperator = true;
			}
			else {
				hasOperand = true;

				int dotCount = 0;
				for (char c : term) {
					if (c == '.') {
						dotCount++;
					}
					else if (!isdigit(c)) {
						throw std::runtime_error("Invalid number: " + term);
					}
				}
				if (dotCount > 1 || term[0] == '.' || term.back() == '.') {
					throw std::runtime_error("Invalid number: " + term);
				}

				lastWasOperator = false;
			}
		}

		if (openBrackets != 0) {
			throw std::runtime_error("Mismatched parentheses");
		}

		if (!hasOperand) {
			throw std::runtime_error("No operands found");
		}

		if (isOper(terms.back()[0]))
		{
			throw std::runtime_error("Expression cannot end with an operator");
		}
	}
public:
	Translator(std::string str = "")
	{
		std::string tmp;

		for (char c : str) {
			if (isnum(c) || c == '.') {
				tmp += c;
			}
			else if (!tmp.empty()) {
				terms.push_back(tmp);
				tmp.clear();
			}
			if (!isemp(c)) {
				if (isOper(c) || c == '(' || c == ')') {
					terms.push_back(std::string(1, c));
				}
				else if (!isnum(c) && c != '.') {
					throw std::runtime_error("Incorrect symbol: " + std::string(1, c));
				}
			}
		}

		if (!tmp.empty()) {
			terms.push_back(tmp);
		}
	}

	double calculate() {
		checkErrors();
		postfixExpression = infixToPostfix();

		std::stack<double> operands;
		std::stringstream ss(postfixExpression);
		std::string token;

		while (ss >> token) {
			if (isOper(token[0])) {
				if (operands.size() < 2) {
					throw std::runtime_error("Not enough operands");
				}

				double operand2 = operands.top(); operands.pop();
				double operand1 = operands.top(); operands.pop();

				try {
					operands.push(operation(operand1, operand2, token[0]));
				}
				catch (const std::runtime_error& e) {
					throw;
				}

			}
			else {
				try {
					operands.push(std::stod(token));
				}
				catch (const std::invalid_argument& e) {
					throw std::runtime_error("Incorrect operand " + token);
				}
			}
		}

		if (operands.size() != 1) {
			throw std::runtime_error("incorrect postfix expression");
		}

		return operands.top();
	}

	void printRes()
	{
		try {
			double result = calculate();
			std::cout << "Result: " << result << std::endl;
		}
		catch (const std::runtime_error& error) {
			std::cerr << "Error: " << error.what() << std::endl;
		}
	}

	std::string getPostfixExpression() const
	{
		return postfixExpression;
	}

	friend std::ostream& operator<<(std::ostream& ostr, const Translator& other)
	{

		for (int i = 0; i < other.terms.size(); i++) {
			std::cout << other.terms[i] << std::endl;
		}

		return ostr;
	}
};