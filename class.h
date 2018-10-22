#ifndef _CLASS_PARAMETER_H
#define _CLASS_PARAMETER_H
struct member {
	string name;
	int offset;
	Type t;
	~member() {
		delete t;
	}
};

class ClassTree {
	string name;
	vector<member *> members;
	int currentSize = 4;
	ClassTree() {
		
	}
	ClassTree(string y) {
		name = y;
	}
	~ClassTree() {
		for (int x = 0; x < members; x++) delete members[x];
	}
	void insert(string n, Type * t) {
		member * p = new member();
		p->n = n;
		p->t = t;
		p->offset = currentSize;
		members.push_back(p);
		currentSize += t->size();
		if (t->name == name && quantity != 0); // throw error cannot define a classname inside my class name
	}
};
#endif
