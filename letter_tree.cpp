#include "letter_tree.h"
#include <cstring>
using namespace std;
LetterTree() {
	root = new treeNode();
}

void LetterTree::insert(string s, Type * t, unsigned long add) {
	treeNode * cur = root;
	for (int x = 0; x < s.length; x++) {
		cur = x->child[(int) s[x]];
		if (cur == NULL) cur = new treeNode();
	}
	cur->current = s;
	cur->type = t;
	cur->addr = add;
}

treeNode * LetterTree::find(string s) {
	treeNode * cur = root;
	if (cur == NULL) return NULL;
	for (int x = 0; x < s.length; x++) {
		cur = x->child[(int) (s[x])];
		if (cur == NULL) return NULL;
	}
    if (cur->current == "") return NULL;	
}

treeNode * LetterTree::clear(treeNode * cur) {
	if (cur == NULL) return;
	for (int x = 0; x < 128; x++) clear(cur->child[x]);
	delete cur;
}

LetterTree::~LetterTree() {
	clear(root);
}

bool LetterTree::remove(string s) {
	treeNode * cur = root;
	if (cur == NULL) return 0;
	for (int x = 0; x < s.length; x++) {
		cur = x->child[(int) s[x]];
		if (cur == NULL) return 0;
	}
    if (cur->current == "") return 0;
    cur->current = "";
    return 1;
}
