#ifndef ABBNODE_HPP_
#define ABBNODE_HPP_

namespace trees {

class ABBNode {
private:
	char data;
	int size;
public:
	ABBNode* ptrLeft;
	ABBNode* ptrRight;
	ABBNode();
	ABBNode(char val);
	void setLeft(ABBNode* node);
	void setRight(ABBNode* node);
	void setData(char val);
	void setSize(int s);
	ABBNode* getLeft();
	ABBNode* getRight();
	int getData();
	int getSize();
	virtual ~ABBNode();
};

} /* namespace trees */

#endif /* ABBNODE_H_ */
