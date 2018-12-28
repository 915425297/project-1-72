#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#ifndef _GRAMMER_TREE
#define _GRAMMER_TREE
#include "letter_tree.h"
using namespace std;
struct Func {
	string name;
	vector<string> names;
	vector<Type *> types;
	Type * returnType = new Type();
	~Func {
		for (int x = 0; x < types; x++) delete types[x];
		delete returnType;
	}
	Func & operator=(Func & other) {
		this->name = other.name;
		this->names.clear();
		this->types.clear();
		for (int x = 0; x < other.names.size(); x++) {
			this->names.push_back(other.names[x]);
			this->types.push_back(new Type());
			*(this->types[x]) = *(other->type[x]);
			*(this->returnType) = *(other.returnType);
		}
		return *this;
	}
	bool operator==(Func & other) {
		if (names.size() != other.names.size()) return false;
		if (types.size() != other.types.size()) return false;
		for (int x = 0; x < names.size(); x++) {
			if (names[x] != other.names[x]) return false;
			if (!((*types[x]) == (*(other.types[x])))) return false;
		}
		return true;
	}
};

struct treeNod {
	string name;
	string type = "";  // calculators: cal, variables: var, 
	treeNod * left = NULL;
	treeNod * right = NULL;
	Func * para = NULL;
	vector<treeNod *> functionPara; // treenode for the function which contained the parameters
	treeNod(string n):name(n) {
	}
};

class GrammerTree {
	public:
		treeNod * root = NULL;
		vector<vector<string>> arr;
		vector<string> arrdef;
		vector<string> para;
		Type * t = NULL;
		string type;
		~GrammerTree();
		GrammerTree(vector<string> & vec);
		Func * buildFunc(vector<treeNod *> & vec, int l, int h);
		treeNod * buildTreeNor(vector<treeNod *> & vec);
		treeNod * buildTreeNor2(vector<treeNod *> & vec);
		treeNod * buildTreeIf(vector<treeNod *> & vec);
		treeNod * buildTreeWhile(vector<treeNod *> & vec);
		treeNod * buildTreeFor(vector<treeNod *> & vec); // for()
		treeNod * buildTreeDef(vector<treeNod *> & vec);
		treeNod * buildDef(vector<treeNod *> & vec, int l, int h);
		Type * buildType(vector<treeNod *> & vec);
		treeNod * buildTreeOther(vector<treeNod *> & vec); 
		void buildTree(vector<treeNod *> & vec);
		treeNod * buildOther(vector<treeNod *> & vec);
		void merge(GrammerTree * t1, GrammerTree * t2);
};
#endif
