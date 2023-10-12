#ifndef ABB_HPP_
#define ABB_HPP_

#include "abbNode.hpp"
#include <string>

namespace trees {

class ABB {
private:
	ABBNode* root;
public:
	ABB();
	void insertPostfix(const std::string &s);
	void insert_rec(char val, ABBNode* node);
	void insert(char val);
	ABBNode* find_rec(char val, ABBNode* node);
	ABBNode* find(char val);
	void traverse_rec(ABBNode* node, std::string indent);
	void traverse();
	void showASC_rec(ABBNode* node);
	void showASC();
	void updateSize_rec(ABBNode* node);
	void updateSize();
	ABBNode* k_element_rec(int k, ABBNode* node);
	ABBNode* k_element(int k);
	virtual ~ABB();
};

} /* namespace trees */

#endif /* ABB_HPP_ */
