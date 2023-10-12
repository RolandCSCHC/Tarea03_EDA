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
std::string infixToPostfix(std::string s) {
    std::stack<char> st;
    std::string result;
    
    // Definir la precedencia de los operadores
    std::map<char, int> precedence;
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;
    precedence['^'] = 3;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // If c is a space, skip it
        //if (c == ' ') continue;

        if (isalnum(c)) {
            // If it's a letter or a digit, add it to the output
            result += c;
			result += ' ';
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
				result += ' ';
                st.pop();
            }
            if (!st.empty() && st.top() == '(') {
                st.pop();
            }
        }
        else if (isOperator(c)) {
            while (!st.empty() && isOperator(st.top()) && precedence[c] <= precedence[st.top()]) {
                result += st.top();
				result += ' ';
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        result += st.top();
		result += ' ';
        st.pop();
    }

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

	std::string exp = "3 + ( 2 + 5 )"; 

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
