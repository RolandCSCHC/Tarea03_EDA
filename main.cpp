#include "abb.hpp"
#include "abbNode.hpp"
#include <bits/stdc++.h> 
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <map>
#include <regex>
#include <iomanip>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// The main function to convert infix expression 
// to postfix expression 
std::string infixToPostfix(std::string s) 
{
    // Initialize an empty stack to store operators
    std::stack<char> st;
    // Initialize an empty string to store the resulting postfix expression
    std::string result;
    
    // Define the precedence of operators
    std::map<char, int> precedence;
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;
    precedence['^'] = 3;

    // Iterate through each character in the input infix expression
    for (int i = 0; i < s.length(); i++) 
	{
        char c = s[i];

        // If the character is an alphanumeric character (operand), add it to the result string
        if (isalnum(c)) 
		{
            // Handle multi-digit numbers by reading characters until a non-digit is encountered
            while (i < s.length() && (isalnum(s[i]) || s[i] == '.')) 
			{
                result += s[i++];
            }
            result += ' ';  // Add a space after the number to separate it in the postfix expression
            // Decrement i to account for the extra increment in the loop
            i--;
        }
        // If the character is an opening parenthesis '(', push it onto the stack
        else if (c == '(') 
		{
            st.push(c);
        }
        // If the character is a closing parenthesis ')', pop operators from the stack and add them to the result
        else if (c == ')') 
		{
            while (!st.empty() && st.top() != '(') 
			{
                result += st.top();
                result += ' ';  // Add a space after the operator to separate it in the postfix expression
                st.pop();
            }
            // Pop the opening parenthesis from the stack
            if (!st.empty() && st.top() == '(') 
			{
                st.pop();
            }
        }
        // If the character is an operator (+, -, *, /, ^), handle operator precedence
        else if (isOperator(c)) 
		{
            while (!st.empty() && isOperator(st.top()) && precedence[c] <= precedence[st.top()]) 
			{
                result += st.top();
                result += ' ';  // Add a space after the operator to separate it in the postfix expression
                st.pop();
            }
            // Push the current operator onto the stack
            st.push(c);
        }
    }

    // After processing the expression, pop any remaining operators from the stack and add them to the result
    while (!st.empty()) 
	{
        result += st.top();
        result += ' ';  // Add a space after the operator to separate it in the postfix expression
        st.pop();
    }

    // Return the resulting postfix expression
    return result;
}

// Map to store variable values
std::map<char, double> variables;

double calculatePostfixExpression(const std::string& postfix) 
{
	// Initialize a stack to hold operands
    std::stack<double> stack; 
	// Create an input string stream to split tokens
    std::istringstream iss(postfix); 
    std::string token;

    while (iss >> token) 
	{
		if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1])) || token.size() > 1) {
            // Token is an operand (a number or a variable)
            if (isalpha(token[0])) {
                // Token is a variable, look up its value in the map
                if (variables.find(token[0]) != variables.end()) {
                    stack.push(variables[token[0]]);
                } else {
                    std::cerr << "Error: Variable " << token << " is not defined." << std::endl;
                    return 0.0;  // Handle error condition
                }
            } else {
                double operand = stod(token);
                stack.push(operand);
            }
		}
		// Token is an operator
		else 
		{
            
            if (stack.size() < 2) 
			{
                // Handle error condition
				std::cerr << "Error: Not enough operands for operator " << token << std::endl;
				return 0.0;  
            }
			// Pop the second operand from the stack
            double operand2 = stack.top(); 
            stack.pop();
			// Pop the first operand from the stack
            double operand1 = stack.top(); 
            stack.pop();
			// Push the result of addition
            if (token == "+") 
			{
                stack.push(operand1 + operand2); 
            } 
			// Push the result of subtraction
			else if (token == "-") 
			{
                stack.push(operand1 - operand2); 
            } 
			// Push the result of multiplication
			else if (token == "*") 
			{
                stack.push(operand1 * operand2); 
            } 
			// Push the result of division
			else if (token == "/") 
			{
                if (operand2 == 0.0) 
				{
					// Handle error condition
                    std::cerr << "Error: Division by zero" << std::endl;
					return 0.0;  
                }
				// Push the result of division
                stack.push(operand1 / operand2); 
            } 
			// Push the result of exponentiation
			else if (token == "^") 
			{
                stack.push(pow(operand1, operand2)); 
            } 
			// Handle unknown operators
			else 
			{
                std::cerr << "Error: Unknown operator " << token << std::endl;
                return 0.0;  
            }
        }
    }
	// The final result is at the top of the stack
    if (stack.size() == 1) 
	{
        return stack.top(); 
    } 
	else 
	{
		// Handle error condition
        std::cerr << "Error: Incomplete expression" << std::endl;
        return 0.0;  
    }
}

// Global variable named ans to keep the result of the expression
double ans = 0.0;

int main(int nargas, char** vargs)
{
	// Set the precision to 1 decimal place
    std::cout << std::fixed << std::setprecision(1);

	trees::ABB abb;
	// Print the presentation of the interactive calculator
	std::cout << "Welcome to the interactive calculator!" << std::endl;
	std::cout << "======================================" << std::endl;
	while(true)
	{
		std::string input;
        std::cout << "Enter all the variables you want to use: ";
        std::getline(std::cin, input);

        if (input == "FINISH") 
		{
            break;
        }

		// If the input is answer, print the result
		if (input == "ANSWER") 
		{
			std::cout << "Result: " << ans << std::endl;
			continue;
		}

		// Split the input by '=' to check for variable assignment
        size_t assignmentPos = input.find('=');

        if (assignmentPos != std::string::npos) 
		{
			// Assuming the variable name is a single character
            char varName = input[0]; 
            double varValue = std::stod(input.substr(assignmentPos + 1));

            // Add the variable to the map
            variables[varName] = varValue;
		}

	}

	std::string exp = "1 * ( 2 + x ) - 10 / z + ( y * 2 - 2 )";
	std::string postfix;
	std::string modifiedExpression;

	// Parse the expression to identify variables used
	std::vector<char> usedVariables;
	for (char c : exp) 
	{
		if (isalpha(c)) 
		{
			usedVariables.push_back(c);
		}
	}

	if (!usedVariables.empty()) 
	{
		// Replace each variable with its assigned value
		modifiedExpression = exp;
		for (char var : usedVariables) 
		{
			int varValue = variables[var];
			// Convert the variable char back to a string
			std::string varName(1, var);
			std::string varValueStr = std::to_string(varValue);
			modifiedExpression = std::regex_replace(modifiedExpression, std::regex(varName), varValueStr);
		}
			postfix = infixToPostfix(modifiedExpression);
	}
	else
	{
		postfix = infixToPostfix(exp);
	}

	std::cout << "Infix expression: " << exp << std::endl;
	std::cout << "Infix expression w/ vars: " << modifiedExpression << std::endl;
	std::cout << "Postfix expression: " << postfix << std::endl;

	// Insert postfix expression into the tree
	abb.insertPostfix(postfix);
	abb.updateSize();
	abb.traverse();
	ans = calculatePostfixExpression(postfix);
	std::cout << "Result: " << ans << std::endl;

	return 0;
}
