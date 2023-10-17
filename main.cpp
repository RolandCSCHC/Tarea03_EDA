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

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// The function to convert infix expression 
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
            // Add a space after the number to separate it in the postfix expression
            result += ' ';  
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
                // Add a space after the operator to separate it in the postfix expression
                result += ' ';  
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
                // Add a space after the operator to separate it in the postfix expression
                result += ' ';  
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
        // Add a space after the operator to separate it in the postfix expression
        result += ' ';  
        st.pop();
    }

    // Return the resulting postfix expression
    return result;
}

// Map to store variable values
std::map<char, double> variables;

// Global variable named ans to keep the result of the expression
double ans = 0.0;

// Function to evaluate a postfix expression
double calculatePostfixExpression(const std::string& postfix) 
{
	// Initialize a stack to hold operands
    std::stack<double> stack; 
	// Create an input string stream to split tokens
    std::istringstream iss(postfix); 
    std::string token;

    while (iss >> token) 
	{
		if (isdigit(token[0]) || 
                    (token[0] == '-' && 
                    token.length() > 1 && 
                    isdigit(token[1])) || 
                    token.size() > 1) {
            // Token is an operand (a number or a variable)
            if (isalpha(token[0])) {
                // Token is a variable, look up its value in the map
                if (variables.find(token[0]) != variables.end()) {
                    stack.push(variables[token[0]]);
                } else {
                    std::cerr << "Error: Variable " << token << " is not defined." << std::endl;
                    // Handle error condition
                    return 0.0;  
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

// Function to print the menu of the interactive calculator
void menu()
{
    // Print the presentation of the interactive calculator
	std::cout << "\nWelcome to the interactive calculator!" << std::endl;
	std::cout << "======================================" << std::endl;
    std::cout << "If you want to use \"ans\" as a variable, type \"A\" instead" << std::endl;
    std::cout << "~Type ANSWER to calculate the result" << std::endl;
    std::cout << "~Type TREE to display the tree" << std::endl;
    std::cout << "~Type FINISH to finish the program" << std::endl;
}

int main(int nargas, char** vargs)
{
	// Set the precision to 1 decimal place
    std::cout << std::fixed << std::setprecision(1);

    // Create an object of the ABB class
	trees::ABB abb;
    // Create a string to store the postfix expression
    std::string postfix = "";
    // Create a string to store the modified expression
    std::string modifiedExpression = "";
    // Infix expression
    std::string infix = "";
	menu();
	while(true)
	{
        std::cout << "$ ";
        std::string decision_input = "";
        std::getline(std::cin, decision_input);

        // Split the variable_input by '=' to check for variable assignment
        size_t assignmentPos = decision_input.find('=');
        // If the variable_input has an assignment operator, add the variable to the map
        if (assignmentPos != std::string::npos) 
        {
            // Assuming the variable name is a single character
            char varName = decision_input[0]; 
            double varValue = std::stod(decision_input.substr(assignmentPos + 1));

            // Add the variable to the map
            variables[varName] = varValue;
            continue;
        }
        // If decision_input is an expression
        else if (decision_input != "TREE" && decision_input != "ANSWER" && decision_input != "FINISH")
        {
            infix = decision_input;
            // Check if decision_input has variables in it with a loop
            for(int i = 0; i < decision_input.length(); i++)
            {
                // If it has variables, ask for the values of the variables
                if (isalpha(decision_input[i]))
                {
                    std::string variable_input;
                    // If the variable is not in variables map, ask for its value
                    if(decision_input[i] != 'A' && variables.find(decision_input[i]) == variables.end())
                    {
                        std::cout << "Enter the value of the variable " << decision_input[i] << std::endl;
                        std::cout << "Example: " << decision_input[i] << " = 2" << std::endl;
                        std::cout << "$ ";
                        std::getline(std::cin, variable_input);
                    }
                    else
                    {
                        variable_input = "A = " + std::to_string(ans);
                    }
                    // Split the variable_input by '=' to check for variable assignment
                    size_t assignmentPos = variable_input.find('=');
                    // If the variable_input has an assignment operator, add the variable to the map
                    if (assignmentPos != std::string::npos) 
                    {
                        // Assuming the variable name is a single character
                        char varName = variable_input[0]; 
                        double varValue = std::stod(variable_input.substr(assignmentPos + 1));

                        // Add the variable to the map
                        variables[varName] = varValue;
                    }
                    else
                    {
                        std::cerr << "Error: Invalid variable assignment" << std::endl;
                    }
                }
            }
            // Parse the expression to identify variables used
            std::vector<char> usedVariables;
            for (char c : decision_input) 
            {
                if (isalpha(c)) 
                {
                    usedVariables.push_back(c);
                }
            }
            if (!usedVariables.empty()) 
            {
                // Replace each variable with its assigned value
                modifiedExpression = decision_input;
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
                postfix = infixToPostfix(decision_input);
            }
            abb.insertPostfix(postfix);
            ans = calculatePostfixExpression(postfix);
            abb.updateSize();
        }
        // If the decision_input is TREE, print the tree
        else if (decision_input == "TREE")
        {
            std::cout << "\nInfix expression: " << infix << std::endl;
            std::cout << "Infix expression w/ vars: " << modifiedExpression << std::endl;
            std::cout << "Postfix expression: " << postfix << std::endl;
            std::cout << "Tree: \n" << std::endl;
            abb.traverse();
            std::cout << std::endl;
            continue;
        }
        // If the decision_input is ANSWER, calculate the result
        else if (decision_input == "ANSWER")
        {
            if (postfix == "")
            {
                std::cout << "\nResult: " << ans << std::endl;
                std::cerr << "Error: There is no expression to calculate" << std::endl;
                continue;
            }
            ans = calculatePostfixExpression(postfix);
            std::cout << "\nResult: " << ans << "\n" << std::endl;
            continue;
        }
        // If the decision_input is FINISH, finish the program
        else if (decision_input == "FINISH") 
        {
            std::cout << "Finishing the program..." << std::endl;
            break;
        }
	}	
	return 0;
}
