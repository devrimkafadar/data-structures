#include <iostream>

class Node{
    private:
		int value;
		Node * next;
		Node * prev;
		Node * right;
		Node * left;
	//public:
		Node(int number) : value(number){
			next = prev = left = right = NULL;
		}
		friend class NodeList;
        friend class NodeTree;
		friend class NodeArray;
		friend class NodeStack;
};