#ifndef _LETTER_TREE
#define _LETTER_TREE
#include <cstring>
#include <iostream>
#include "type.h"
#include "grammer_tree.h"
using namespace std;

struct treeNode {
	treeNode * child[128];
	string current = "";
	Type * type = NULL;
	Func * func = NULL;
    unsigned long addr;
	treeNode() {
		for (int x = 0; x < 128; x++) child[x] = NULL;
	}
	
	~treeNode() {
		delete[] child;
		delete type;
		delete func;
	}
};

class LetterTree {
	public:
	treeNode * root;
	string name = "";
	LetterTree();
	~LetterTree();
	void insert(string s, Type * t, unsigned long addr);
	treeNode * find(string s);
	treeNode * remove(string s);
	void clear(treeNode * cur);
};
#endif
