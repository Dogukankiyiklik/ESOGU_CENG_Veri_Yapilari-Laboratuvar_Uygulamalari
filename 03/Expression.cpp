#include <string>
#include <stack>

using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {
	// Fill this in
	string result;

	int index1 = 0, index2 = 0;
	string tempInfixNumber = "";
	char tempInfixSign = ' ';
	string* output = new string[size(s)];

	stack<char> InfixSigns;

	while (s[index1] != NULL) {
		if (s[index1] != ' ' && s[index1] != '+' && s[index1] != '-' && s[index1] != '*' && s[index1] != '/' && s[index1] != '(' && s[index1] != ')') {
			while (s[index1] != ' ' && s[index1] != '+' && s[index1] != '-' && s[index1] != '*' && s[index1] != '/' && s[index1] != '(' && s[index1] != ')' && s[index1] != NULL) {
				tempInfixNumber += s[index1];
				index1++;
			}
		}

		if (s[index1] == '+' || s[index1] == '-' || s[index1] == '*' || s[index1] == '/' || s[index1] == '(' || s[index1] == ')') {
			InfixSigns.push(s[index1]);
		}

		if (tempInfixNumber != "") {
			output[index2] = tempInfixNumber;
			tempInfixNumber = "";
			index2++;
		}

		if (InfixSigns.size() > 1) {
			tempInfixSign = InfixSigns.top();
			InfixSigns.pop();

			// lower priority
			if ((tempInfixSign == '+' || tempInfixSign == '-') && (InfixSigns.top() == '*' || InfixSigns.top() == '/')) {
				output[index2] = InfixSigns.top();
				InfixSigns.pop();
				index2++;

				if (!InfixSigns.empty() && (InfixSigns.top() == '+' || InfixSigns.top() == '-')) {
					output[index2] = InfixSigns.top();
					InfixSigns.pop();
					index2++;
				}
				InfixSigns.push(tempInfixSign);
				tempInfixSign = ' ';
			}

			// equal priority
			if (((tempInfixSign == '+' || tempInfixSign == '-') && (InfixSigns.top() == '+' || InfixSigns.top() == '-')) || ((tempInfixSign == '*' || tempInfixSign == '/') && (InfixSigns.top() == '*' || InfixSigns.top() == '/'))) {
				output[index2] = InfixSigns.top();
				InfixSigns.pop();
				InfixSigns.push(tempInfixSign);
				tempInfixSign = ' ';
				index2++;
			}

			// ) sign  
			if (tempInfixSign == ')') {
				while (InfixSigns.top() != '(') {
					output[index2] = InfixSigns.top();
					InfixSigns.pop();
					index2++;
				}
				InfixSigns.pop();
				tempInfixSign = ' ';
			}

			if (tempInfixSign != ' ') {
				InfixSigns.push(tempInfixSign);
			}
		}

		// last check statement
		if (s[index1] != NULL) {
			index1++;
		}
	}

	// last values inside stack memory
	while (!InfixSigns.empty()) {
		output[index2] = InfixSigns.top();
		InfixSigns.pop();
		index2++;
	}

	index2 = 0;
	while (output[index2] != "") {
		result += output[index2];
		result += " ";
		index2++;
	}
	delete[] output;

	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {

	stack<string> finalResult;
	string firstNumber, secondNumber;
	double sum;
	string element = " ";
	int finalIndex = 0;

	for (int i = 0; i <= size(s); i++) {
		if (!finalResult.empty() && finalResult.top() == "*") {
			finalResult.pop();

			secondNumber = finalResult.top();
			finalResult.pop();
			firstNumber = finalResult.top();
			finalResult.pop();

			sum = stoi(firstNumber) * stoi(secondNumber);
			finalResult.push(to_string(sum));
		}

		else if (!finalResult.empty() && finalResult.top() == "/") {
			finalResult.pop();

			secondNumber = finalResult.top();
			finalResult.pop();
			firstNumber = finalResult.top();
			finalResult.pop();

			sum = stoi(firstNumber) / stoi(secondNumber);
			finalResult.push(to_string(sum));
		}

		else if (!finalResult.empty() && finalResult.top() == "+") {
			finalResult.pop();

			secondNumber = finalResult.top();
			finalResult.pop();
			firstNumber = finalResult.top();
			finalResult.pop();

			sum = stoi(firstNumber) + stoi(secondNumber);
			finalResult.push(to_string(sum));
		}

		else if (!finalResult.empty() && finalResult.top() == "-") {
			finalResult.pop();

			secondNumber = finalResult.top();
			finalResult.pop();
			firstNumber = finalResult.top();
			finalResult.pop();
			
			sum = stoi(firstNumber) - stoi(secondNumber);
			finalResult.push(to_string(sum));
		}

		if (i != size(s)) {
			if (s[finalIndex] == NULL) {
				break;
			}

			while (s[finalIndex] != ' ' && s[finalIndex] != '+' && s[finalIndex] != '-' && s[finalIndex] != '*' && s[finalIndex] != '/') {
				element += s[finalIndex];
				finalIndex++;
			}
			if (s[finalIndex] != ' ' && element == " ") {
				element = s[finalIndex];
			}

			if (element != " ") {
				finalResult.push(element);
			}
			element = " ";
			finalIndex++;
		}
	}

	return stoi(finalResult.top());
} // end-EvaluatePostfixExpression