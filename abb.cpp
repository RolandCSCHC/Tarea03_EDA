#include "abb.hpp"
#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include "abbNode.hpp"

namespace trees {

ABB::ABB():root(nullptr) {
	// TODO Auto-generated constructor stub
}

void ABB::insertPostfix(const std::string& postfix) 
{
    std::stack<ABBNode*> nodeStack;
	// Variable to track position in postfix string
    size_t i = 0;  

    while (i < postfix.length()) 
	{
        if (isalpha(postfix[i])) 
		{
			// If it's a letter (operand), create a node and place it on the stack
            ABBNode* operandNode = new ABBNode(postfix[i]);
            nodeStack.push(operandNode);
        } else if (isdigit(postfix[i])) 
		{
			// If it's a digit (part of a number), build the whole number
            std::string number;
            while (i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '.')) 
			{
                number += postfix[i];
                i++;
            }
			// Backtrack one step to compensate for the extra increment
            i--;  
			
			// Convert the number string into an integer and create a node
            int num = std::stoi(number);
			// Convert the number to a character and create a node
            ABBNode* numberNode = new ABBNode(static_cast<char>(num));
            nodeStack.push(numberNode);
        } else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') 
		{
            if (nodeStack.size() < 2) 
			{
				// Manages an error if there are not enough operands for the operator
				std::cerr << "Error: Not enough operands for operator '" << postfix[i] << "'." << std::endl;
                return;
            }
			// If it's an operator, pop two operands from the stack
            ABBNode* rightOperand = nodeStack.top();
            nodeStack.pop();
            ABBNode* leftOperand = nodeStack.top();
            nodeStack.pop();

			// Creates a node for the operator and links the operands
            ABBNode* operatorNode = new ABBNode(postfix[i]);
            operatorNode->ptrLeft = leftOperand;
            operatorNode->ptrRight = rightOperand;

			// Puts the operator node on the stack
            nodeStack.push(operatorNode);
        }
        i++;
    }

    if (nodeStack.size() != 1) 
	{
		// Manages an error if there are nodes left on the stack at the end
        std::cerr << "Error: Invalid postfix expression." << std::endl;
        return;
    }

    root = nodeStack.top();
    nodeStack.pop();
}

void ABB::insert_rec(char val, ABBNode* node){
	if (val < node->getData()){
		//LEFT
		if (node->getLeft() == nullptr){
			node->setLeft(new ABBNode(val));
			//std::cout<<val << " inserted on left" << std::endl;
		}
		else{
			insert_rec(val, node->getLeft());
		}
	}
	else{
		//RIGHT
		if (node->getRight() == nullptr){
			node->setRight(new ABBNode(val));
			//std::cout<<val << " inserted on right" << std::endl;
		}
		else{
			insert_rec(val, node->getRight());
		}
	}
}

void ABB::insert(char val){
	if (root == nullptr){
		root = new ABBNode(val);
	}
	else{
		insert_rec(val, root);
	}
}

ABBNode* ABB::find_rec(char val, ABBNode* node){
	ABBNode* ans = nullptr;

	if (node->getData() == val){
		ans = node;
	}
	else{
		if (val < node->getData()){
			ans = find_rec(val, node->getLeft());
		}
		else{
			ans = find_rec(val, node->getRight());
		}
	}

	return ans;
}

ABBNode* ABB::find(char val){
	ABBNode* ans = nullptr;
	ans = find_rec(val, root);
	return ans;
}

void ABB::traverse_rec(ABBNode* node, std::string indent) {
    if (node != nullptr) {
		// If getData() is 43, it will print '+'
		if (node->getData() == 43)
		{
			std::cout << indent << '+' << std::endl;
		}
		// If getData() is 42, it will print '*'
		else if (node->getData() == 42)
		{
			std::cout << indent << '*' << std::endl;
		}
		// If getData() is 45, it will print '-'
		else if (node->getData() == 45)
		{
			std::cout << indent << '-' << std::endl;
		}
		// If getData() is 47, it will print '/'
		else if (node->getData() == 47)
		{
			std::cout << indent << '/' << std::endl;
		}
		// If getData() is 94, it will print '^'
		else if (node->getData() == 94)
		{
			std::cout << indent << '^' << std::endl;
		}
		// If getData() is a number, it will print the number
		else
		{
			std::cout << indent << node->getData() << std::endl;
		}
        traverse_rec(node->getLeft(), indent + "---");
        traverse_rec(node->getRight(), indent + "---");
    }
}

void ABB::traverse() {
    traverse_rec(root, " ");
}


/*extras*/
void ABB::showASC_rec(ABBNode* node){
	if (node != nullptr){
		showASC_rec(node->getLeft());
		std::cout << node->getData() << " " << std::flush;
		showASC_rec(node->getRight());
	}
}
void ABB::showASC(){
	showASC_rec(root);
	std::cout << std::endl;
}

void ABB::updateSize_rec(ABBNode* node){
	if (node != nullptr){
		updateSize_rec(node->getLeft());
		updateSize_rec(node->getRight());
		int lSize = 0;
		int rSize = 0;
		if (node->getLeft() != nullptr){
			lSize = node->getLeft()->getSize();
		}
		if (node->getRight() != nullptr){
			rSize = node->getRight()->getSize();
		}
		node->setSize(lSize + rSize + 1);
	}
}

void ABB::updateSize(){
	updateSize_rec(root);
}


ABBNode* ABB::k_element_rec(int k, ABBNode* node){
	ABBNode* ans = nullptr;
	if (node != nullptr){
		int lSize = 0;
		int posNode = 0;
		if (node->getLeft() != nullptr){
			lSize = node->getLeft()->getSize();
		}
		posNode = lSize + 1;

		if (k == posNode){
			ans = node;
		}
		else if  (k > posNode ){
			ans = k_element_rec( k - posNode, node->getRight());
		}
		else{
			ans = k_element_rec( k, node->getLeft());
		}
	}
	return ans;

}

ABBNode* ABB::k_element(int k){
	return k_element_rec(k, root);
}

ABB::~ABB() {
	delete root;
}

} /* namespace trees */
