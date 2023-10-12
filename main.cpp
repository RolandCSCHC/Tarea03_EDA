#include "abb.hpp"
#include "abbNode.hpp"
#include <bits/stdc++.h> 
#include <iostream>
#include <string>
#include <stack>


// Function to return precedence of operators 
int prec(char c) 
{ 
	if (c == '^') 
		return 3; 
	else if (c == '/' || c == '*') 
		return 2; 
	else if (c == '+' || c == '-') 
		return 1; 
	else
		return -1; 
} 

// The main function to convert infix expression 
// to postfix expression 
void infixToPostfix(std::string s) 
{ 

	std::stack<char> st; 
	std::string result; 

	for (int i = 0; i < s.length(); i++) { 
		char c = s[i]; 

        // If c is a space, skip it
        if (c == ' ') continue;

		// If the scanned character is 
		// an operand, add it to output string. 
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
			|| (c >= '0' && c <= '9')) 
			result += c; 

		// If the scanned character is an 
		// ‘(‘, push it to the stack. 
		else if (c == '(') 
			st.push('('); 

		// If the scanned character is an ‘)’, 
		// pop and add to output string from the stack 
		// until an ‘(‘ is encountered. 
		else if (c == ')') { 
			while (st.top() != '(') { 
				result += st.top(); 
				st.pop(); 
			} 
			st.pop(); 
		} 

		// If an operator is scanned 
		else { 
			while (!st.empty() 
				&& prec(s[i]) <= prec(st.top())) { 
				result += st.top(); 
				st.pop(); 
			} 
			st.push(c); 
		} 
	} 

	// Pop all the remaining elements from the stack 
	while (!st.empty()) { 
		result += st.top(); 
		st.pop(); 
	} 

	std::cout << result << std::endl; 
} 

int main(int nargas, char** vargs){
	trees::ABB abb;
	abb.insert(16);
	abb.insert(4);
	abb.insert(2);
	abb.insert(20);
	abb.insert(15);
	abb.insert(18);
	abb.insert(35);
	abb.insert(50);
	//abb.showASC();
	abb.updateSize();
	abb.traverse();

	trees::ABBNode* node = nullptr;
	for (int k = 1; k<= 8; k++ ){
		node = abb.k_element(k);
		if (node != nullptr){
			std::cout << "k = " <<k << " --> "<< node->getData() << std::endl;
		}
	}

	std::string exp = "a + b * ( c ^ d - e ) ^ ( f + g * h ) - i"; 

	// Function call 
	infixToPostfix(exp);

	return 0;
}
