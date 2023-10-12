#include "abb.hpp"
#include "abbNode.hpp"
#include <bits/stdc++.h> 
#include <iostream>
#include <string>
#include <stack>

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



int main(int nargas, char** vargs)
{
	trees::ABB abb;

/* 	trees::ABBNode* node = nullptr;
	for (int k = 1; k<= 8; k++ ){
		node = abb.k_element(k);
		if (node != nullptr){
			std::cout << "k = " <<k << " --> "<< node->getData() << std::endl;
		}
	} */

	std::string exp = "1 + 10"; 

	// Function call 
	std::string postfix = infixToPostfix(exp);

	std::cout << "Infix expression: " << exp << std::endl;
	std::cout << "Postfix expression: " << postfix << std::endl;

	// Insert postfix expression into the tree
	abb.insertPostfix(postfix);
	abb.updateSize();
	abb.traverse();

	return 0;
}
