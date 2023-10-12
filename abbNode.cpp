#include "abbNode.hpp"

namespace trees {

ABBNode::ABBNode() : 
		ptrLeft(nullptr), data('\0'), ptrRight(nullptr), size(0) {}

ABBNode::ABBNode(char val) : 
		ptrLeft(nullptr), data(val), ptrRight(nullptr), size(1) {}

void ABBNode::setLeft(ABBNode* node){
	ptrLeft = node;
}

void ABBNode::setRight(ABBNode* node){
	ptrRight = node;
}

void ABBNode::setData(char val){
	data = val;
}

void ABBNode::setSize(int s){
	size = s;
}

ABBNode* ABBNode::getLeft(){
	return ptrLeft;
}

ABBNode* ABBNode::getRight(){
	return ptrRight;
}

int ABBNode::getData(){
	return data;
}

int ABBNode::getSize(){
	return size;
}

ABBNode::~ABBNode() {
	if (ptrLeft != nullptr){
		delete ptrLeft;
	}
	if (ptrRight != nullptr){
		delete ptrRight;
	}
}

} /* namespace trees */
