/*
author: jivfur
date: 09/04/2017
description: BFS
*/
#include<iostream>
#include<ostream>
#include<istream>

using namespace std;

class Node {
private:
	Node *right;
	Node *left;
	int value;
public:
	Node(int v) {
		right = NULL;
		left = NULL;
		value = v;
	}

	Node* getRigthChild() {
		return right;
	}

	Node* getLeftChild() {
		return left;
	}

	int getValue() {
		return value;
	}

	void setValue(int v) {
		value = v;
	}

	void setRightChild(int v) {
		right = new Node(v);
	}
	void setLeftChild(int v) {
		left = new Node(v);
	}

};

class Tree {
private:
	Node *root;
public:
	Tree(int value) {
		root = new Node(value);
	}

	void addValue(Node *node, int value) {
		if (value>node->getValue()) {
			if (node->getRigthChild() != NULL) {
				addValue(node->getRigthChild(), value);
			}
			else {
				node->setRightChild(value);
			}
		}
		else {
			if (node->getLeftChild() != NULL) {
				addValue(node->getLeftChild(), value);
			}
			else {
				node->setLeftChild(value);
			}
		}
	} 

	Node* getRoot() {
		return root;
	}

	void goTroughTree() {
		cout << root->getValue() << endl;
		if (root->getLeftChild() != NULL) {
			goTroughTree(root->getLeftChild(), 1);
		}
		if (root->getRigthChild() != NULL) {
			goTroughTree(root->getRigthChild(), 1);
		}
	}

	void goTroughTree(Node *start, int depth) {
		string space = string(depth, (char)124) + '-';
		cout << space.c_str() << start->getValue() << endl;
		if (start->getLeftChild() != NULL) {
			goTroughTree(start->getLeftChild(), depth + 1);
		}
		if (start->getRigthChild() != NULL) {
			goTroughTree(start->getRigthChild(), depth + 1);
		}

	}

	void bfs(Node *start, int value) {
		if (start->getValue() == value) {
			cout << "Value Found" << endl;
		}
		if (start->getRigthChild() != NULL) {
			bfs(start->getRigthChild(), value);
		}
		if (start->getLeftChild() != NULL) {
			bfs(start->getLeftChild(), value);
		}
	}

	void bfs(int value) {
		if (root->getValue() == value) {
			cout << "Value Found" << endl;
		}
		if (root->getRigthChild() != NULL) {
			bfs(root->getRigthChild(), value);
		}
		if (root->getLeftChild() != NULL) {
			bfs(root->getLeftChild(), value);
		}
	}
};


int main() {
	int num[] = { 50,25,75,12,38,62,88,6,18,32,44,56,68,82,94,3,21,53,97 };
	Tree *myTree = new Tree(num[0]);
	for (int i = 1; i < 19; i++) {
		myTree->addValue(myTree->getRoot(), num[i]);
	}
	myTree->goTroughTree();
	myTree->bfs(25);

	system("pause");
	return 1;
}