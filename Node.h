#ifndef NODE_H
#define NODE_H

#include "Enum.h"

class Node {
public:
	Rating_t label;
	Attribute_t attr;
	double splitValue;
	Node* left;
	Node* right;

	Node() {
		label = nil_r;
		attr = nil_a;
		left = NULL;
		right = NULL;
	}
};

bool isLeafNode(Node* n) {
	return (n->left == NULL) && (n->right == NULL);
}

#endif