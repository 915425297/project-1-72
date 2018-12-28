#include <vector>
#include <string>
#include "grammer_tree.h"
#ifndef _TYPE_H
#define _TYPE_H
class Type {
	public:
	string name;
	Func * para = NULL;
	int pointers = 0;
	int quantity = 1;
	int length = 0; // for selfdefine only
	int size = 0;
	ClassTree * cpara = NULL; // if it is class, only pointer will returned
	vector<Type *> theRelatedTypes;
	Type() {
		
	}
	Type(string n): name(n) {
		
	}
	Type operator=(Type & other) {
		this->pointers = other.pointers;
		this->quantity = other.quantity;
		this->length = other.length;
		this->name = other.name;
		this->para = other.para;
		this->size = other.size;
		this->cpara = other.cpara;
		*(this->para) = *(other.para);
	}
	
	Type(Func * para1): para(para1) {
		name = "function";
	}
	
	Type(string name1, Func * para1):name(name1), para(para1) {
		
	}
	void getSize() {
		if (cpara != NULL || para != NULL || pointers != 0) size = 4;
		else if (name == "float" || name == "int" || name == "unsigned") size = 4;
		else if (name == "short") size = 2;
		else if (name.substr(0, 10) == "selfDefine") {
			size = stoi(name.substr(11, name.length() - 10));
		}
		size *= 4;
	}
	~Type() {
		for (int x = 0; x < theRelateTypes; x++) delete theRelatedTypes[x];
		delete para;
		delete cpara;
	}
	bool operator==(Type & other) {
		return (this->name == other.name) 
		&& (this->quantity == other.quantity)
		&& (this->pointers == other.pointers)
		&& (this->size == other.size)
		&& (!(this->para || other.para) || (*this->para) == (*other.para))
		&& (!(this->cpara || other.cpara) || (*this->cpara) == (*other.cpara));
	}
};
#endif
