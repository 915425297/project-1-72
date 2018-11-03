#include <cstring>
#include <iostream>
#include "cstdio"
#include "letter_tree.h"
#include "word_analyser.h"
using namespace std;

wordAnalyser::wordAnalyser() {
	freopen("letters.txt", "r", stdin);
	char[1024] g;
	for (int x = 0; x <= 15; x++) {
		scanf("%s\n", &g);
		tree.insert(g, "type", 0);
	}
}

void wordAnalyser::divide(string g) {
	int per = 0;
	for (int x = 0; x < g.length(); x++) {
		if (checkWhetherConnection(g[x])) {
			if (per != x) {
				strings.push_back(g.substr(per, x));
			}
			per = x;
			if (g[x] == ' ' || g[x] == '	' || g[x] == '\n') {
				per++; 
				continue;
			}
			if (g[x] == '\"') {
				while(x < g.length() && g[x] != '\"') x++; // check whether ""
				strings.push_back(g.substr(per, x + 1));
				per = x + 1;
				continue;
			}
			string s = "";
			while(checkWhetherConnection(g[x]) 
			&& !(g[x] == ' ' || g[x] == '	' || g[x] == '\n') && x < g.length()) {
				s = s + g[x];
				if (tree1.find(s) == NULL 
				|| tree1.find(s).type.compare("cal") != 0) break; // to check that  whether this is an operation
				x++;
			}
			if (per == x) {
				per = x + 1;
				continue;
			}
			s = g.substr(per, x);
			if (tree1.find(s) == NULL); // throw error;
			per = x + 1;
		} else {
			per++;
		}
	}
}

void wordAnalyser::scanner(string g, string head, ClassTree * ctree, Func * f) {
	divide(g);
	GrammerTree tree2(g, tree1);
	treeWriter(tree2, head, ctree, f);
	strings.clear();
}

bool wordAnalyser::checkWhetherDef(vector<string> & strs) {
	treeNode * t = tree1.find(strs[0]);
	return t->type == "type";
}

wordAnalyser::checkWhetherConnection(char t) {
	int p = t;
	return (p >= 48 && p <= 57) || (p == 95) 
	|| (p >= 65 && p <= 90) || (p >= 97 && p <= 122);
}

jy wordAnalyser::treeSearchMIPS(treeNod * root, string txt, int & move) { // cout code for part 2
	freopen(txt, "w", stdout);
	jy p2;
	jy p1;
	if (root->left) p1 = treeSearch(root->left, txt);
	if (root->right) p2 = treeSearch(root->right, txt);
	if (root->type == "cal" && root->name == "function") {
		
	}
	if (root->type == "var") {
		if (root->right != NULL || root->left != NULL); // throw error, the variables must be on the leaves 
		int x; 
		treeNod * t;
		for (x = tree1.size() - 1; x >= 0; x--) {
			t = tree1[x]->find(root->name);
			if (t != NULL) break;
		}
		if (!t->type) // throw error this is not a variable
		jy n;
		n.p = t->type;
		if (t->type->space > 8) {
			printf("li $t1, %d\n", &t->addr); // if it is array or so, the addr will be the starting address
			
		}
		if (t->type->pointer != 0) {
			printf("lw $t1, zero(%d)\n", &t->addr);
			n.reg1 = "t1"
			return n;
		}
		
		if (t->type->name == "int") {
			printf("lw $t1, zero(%d)\n", &t->addr);
			n.reg1 = "t1";
		}
		else if (t-type->name == "bool") {
			printf("lb $t1, zero(%d)\n", &t->addr);
			n.reg1 = "t1";
		}
		else if (t-type->name == "short") {
			printf("ls $t1, zero(%d)\n", &t->addr);
			n.reg1 = "t1";
		}
		else if (t->type->name == "long") {
			// throw error since does not support long in mips
			printf("lw $t1, zero(%d)\n", &t->addr);
			printf("lw $t2, zero(%d)\n", &t->addr + 4);
			n.reg1 = "t1";
			n.reg1 = "t2";
		}
		else if (t->type->name == "float") {
			printf("lw $f1, zero(%d)\n", &t->addr);
			n.reg1 = "f1";
		}
		else if (t->type->name == "double") {
			printf("lw $f1, zero(%d)\n", &t->addr);
			n.reg1 = "f1";
		}
		else if (t->type->name == "selfDefine") { // only return the start address
			printf("li $t1, %d\n", &t->addr);
			n.reg1 = "t1";
		}
		else {
			printf("li $t1, %d\n", &t->addr);
			n.reg1 = "t1";
		}
		
	}
	else if (root->type == "cal") { //  the core part of this project 
		if () // type casting
		else if (t->type->name == "function") {
			printf("move $v0, $%s\n", &p2->reg1);
			printf("move $v1, $%s\n", &p2->reg2);
			// also insert these two things into the trees
			printf("jalr $%s\n", &p1->reg1);
			n->reg1 = "v0";
			n->reg2 = "v1";
		}
		else if (t->type->name == "+") {
			return operatorAdd(root, txt, move);
		}
		else if (*(p2.p) == *(p1.p)) {
			
		} else {
			// throw error: illegal to 
		}
	}
	return n;
}

void wordAnalyser::treeWriter(GrammerTree & tree, string txt, ClassTree * ctree, Func * f) {
	freopen()
	this->t = NULL;
	switch(tree.type) {
		case("def"): {
			if (tree.root == NULL); //  throw error
			this->t = tree.t;
			if (ctree != NULL) {
				ctree.insert(tree.root, tree.t);
				if (this->t->para != NULL) {
				this->t->para->name = ctree->name + "_" + tree.root->name;
				}
				return;
			}
			if (tree.root->left != NULL || tree.root->right != NULL); // throw error
			tree1.insert(tree.root->name, tree.t, 0);
			if (this->t->para != NULL) {
				this->t->para->name = tree.root->name;
			}	// not completed the assembly part of the def
			break;
		}
		case("{") {
			LetterTree * node = new LetterTree();
			tree1.push_back(node);
			if (f != NULL) {
				for (int x = 0; x < f->names.size(); x++) {
					node.insert(f->names[x], f->types[x]);
				}
			}
			break;
		}
		case("}") {
			// free memory and return
			tree1.pop_back(node);
			break;
		}
		case("class") {
			return;
			break;
		}
		case("if") {
			Type * p = treeSearch(tree.root);
			if (p->name != "bool"); // throw error what returned is not a boolean 
			break;
		}
		case("while") {
			printf("loop%d:\n", &flag1);
			jy p = treeSearch(tree.root);
			if (p->name != "bool"); // throw error what returned is not a boolean 
			printf("beq %s\n, zero, done%d", &p.reg, &flag1);
			break;
		}
		case("nor") { // if this is the normal tree
			jy u = treeSearch(tree.root, txt);
			if (u->t != NULL); // throw error
			break;
		}
	}
}
