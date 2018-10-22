#include "grammer_tree.h"
#include "letter_tree.h"
#include "type.h"
#include <stack>
using namespace std;
struct to {
	char c;
	int po;
	to(char t, int y): c(t), po(y) {
	}
	to() {
	} 
};

void GrammerTree::clear(treeNod * root) {
	if (root == NULL) return;
	clear(root->left);
	clear(root->right);
	delete root;
}

int find1(vector<treeNod *> & vec, int k, int u, int l) { // find the most recent corresponding operator
	int x = u;
	for (; x >= l; x--) {
		if (vec[x] == NULL) continue;
		bool i = 0;
		for (int y = arr[k].size() - 1; y >= 0; y--) {
			i = i | (vec[x]->name == arr[k][y]); // if there 
		}
		if (i) return x;
	}
	return 0;
}

// find the first related operation after k
int find2(vector<treeNod *> & vec, int k, int u, int l) { // find the most recent operator containing the =
	int x = l;
	for (; x <= u; x++) {
		if (vec[x] == NULL) continue;
		if (vec[x]->name == "=") return x;
	}
}
//construct the tree if it is normal expression

treeNod * GrammerTree::buildTreeNor(vector<treeNod *> & vec, int l, int h) {
	if (l < h) return NULL; 
	if (l == h) return vec[0];
	vector<treeNod *> vec1;
	treeNod * result = NULL;
	for (int x = 0; x < vec.size(); x++) if (vec[x] != NULL) vec1.push_back(vec[x]);
	for (int x = 0; x < arr.size(); x++) {
		if (x == 0) {
			int per = 0, posi = find2(vec1, y, h, per);
			if (posi <= h) { // if it is "="
				result = vec1[posi];
				result->left = buildTree(vec1, l, posi - 1);
			    result->right = buildTree(vec1, posi + 1, h);
			    return result;
			}
		}
		int per = vec.size();
		if(find1(vec1, y, per, l) >= l) {
			int posi = find1(vec1, y, per, l);
			result = vec1[posi];
			result->left = buildTreeNor(vec1, l, posi - 1);
			if (result->name != "func" && result->type != "cal") result->right = buildTreeNor(vec1, posi + 1, h);
		}
	}
	if (result != NULL) result->type = "var"; // throw error on multiple things crowded
	return result;
}

int findLast(vector<treeNod *> & vec, int y) {
	y--;
	while (y >= 0 && vec[y] == NULL) y--;
	return y;
} 

int findNext(vector<treeNod *> & vec, int y) {
	y++;
	while (y < vec.size() && vec[y] == NULL) y++;
	return y;
}
 // the will return the node of parameters
 // this function will build the tree node of the function of parameters
treeNod * buildFunction(vector<treeNod *> & vec) { 
	treeNod * result = new treeNod();
	result->type = "parameter";
	if (vec.empty()) return result;
	for (int x = 0; x < vec.size();) {
		if (vec[x]->type != "var"); // throw error
		if (x < vec.size() - 1 && vec[x]->name != ",")// throw error
		if (vec[x].type != "var"); // throw error function does not allow non variable or numbers.
		result->para.push_back(vec[x].name);
		x += 2;
	}
	return result;
}
// this will wipe out the () and also build function if needed
// the function is ended up with operator ( 
void GrammerTree::buildTreeNor2(vector<treeNod *> & vec) {
	stack<to> s;
	for (int x = 0; x < vec.size(); x++) {
		if (vec[x] == NULL) continue;
		vector<treeNod *> ve;
		if (vec[x]->name == "(") {
			s.push(to('(', x));
			int o = s.size();
			int po = findLast(vec, x);
			if (vec[po]->type == "var") { // indicate that this is a function
				delete vec[x];
				vec[x] = NULL;
				x++; 
				for (; vec[x]->name != ")" || s.size() != o; x++) {
					if (x == vec.size() - 1); // throw error since there is no "(" in the vector
					if (s.size() < o); // throw error
					if (vec[x]->name != "(") {
						s.push(to('(', x));
					} else if (vec[x]->name != ")") {
						s.pop();
					}
					ve.push_back(vec[x]);
					vec[x] = NULL;
				}
				delete vec[x];
				vec[x] = NULL;
				if (xy >= 0 && vec[xy].type = "var") {
					x++;
					vec[s.top().po] = new treeNod("func", "cal");
					vec[s.top().po]->right = buildFunction(ve); // build function for those in the 
					vec[po] = NULL; // check that if this is a function call
				}
			}
		}
		
	    else if (vec[x]->name == ")") {
	    	if (s.empty() || s.top().c != '(');// throw () does not match
	    	
	    	for (int y = s.top().po; y < x; y++) {
	    		if (vec[y] == NULL) continue;
				if (vec[y]->name.compare("(") != 0 && vec[y]->name.compare(")") != 0) ve.push_back(vec[y]);
	    		else delete vec[y];
	    		vec[y] = NULL;
			}
			
			if (ve.size() == 1 && ve[0]->type.compare("type") == 0) {
				vec[s.top().po] = new treeNod(")", "cal");
				vec[s.top().po]->left = ve[0];
				int j = findNext(vec, x);
				if (j >= vec.size() || vec[j]->type.compare("val") != 0); //throw error
				vec[s.top().po]->right = vec[j];
				vec[j] = NULL;
			} // cast
			else vec[s.top().po] = buildTreeNor(ve, 0, ve.size()); 
			x = s.top().po + 1;// check type
			s.pop();
		}
		   // search for all of the (), not deal with def
		if (vec[x]->name == "[") s.push(to('[', x));
		if (vec[x]->name == "]") {
	    	if (s.empty() || s.top().c != '[');// throw () does not match
	    	vector<treeNod *> ve;
	    	for (int y = s.top().po + 1; y < x; y++) {
	    		ve.push_back(vec[y]);
	    		vec[y] = NULL;
			}
			x = s.top().po + 1;
			vec[s.top().po] = new treeNod("[");
			vec[x] = buildTreeNor1(ve);
			s.pop();
		}
	}
	if (!s.empty());// throw () does not match
	return buildTreeNor(vec, 0, vec.size());
}
// all of the other operations including bracket and casting should be dealt here
void GrammerTree::buildTree(vector<treeNod *> & vec) { // total tree controller which manage the operation
// including assigning function to deal with the tree
	if (vec[0]->type != "var" || vec[1]->name == ":") {// when the tree is definition, if, while or import
		root = buildTreeOther(vec); 
		return;
	}
	root = buildTreeNor2(vec); // the controller for tree 
}


treeNod * GrammerTree::buildTreeFor(vector<treeNod *> & vec) {
	if (vec[1].compare("(") || vec[3].compare(")")); //throw error
	return vec[2];
}

treeNod * GrammerTree::buildTreeIf(vector<treeNod *> & vec) {
	if (vec[1].compare("(") == 0 || vec[vec.size() - 1].compare(")") == 0);
	vector<treeNod *> vec1;
	for (int x = 2; x < vec.size() - 1; x++) {
		vec1.push_back(vec[x]);
	}
	return buildTreeNor2(vec1);
}

treeNod * GrammerTree::buildTreeWhile(vector<treeNod *> & vec) {
	if (vec[1].compare("(") == 0 || vec[vec.size() - 1].compare(")") == 0);
	vector<treeNod *> vec1;
	for (int x = 2; x < vec.size() - 1; x++) {
		vec1.push_back(vec[x]);
	}
	return buildTreeNor2(vec1);
}

Func * GrammerTree::buildFunc(vector<treeNod *> & vec, int l, int h) { // build those with parameters (definition only)
	Func * result = new Func();
	if (l <= h) return result;
	bool y = 0;
	int per = 0;
	stack<to> s;
	for (int x = l; x <= h; x++) {
		if (vec[x]->name == "(") {
			s.push(to('(', x));
			if (s.size() == 0 && y) per = x + 1;
		} else if (vec[x]->name == ")") {
			if (s.empty() || s.top().c != '(');// throw error
			s.pop();
		} else if (vec[x]->name == "<") {
			s.push(to('<', x));
		} else if (vec[x]->name == ">") {
			if (s.empty() || s.top().c != '>'); //  throw error
		} else if (vec[x]->name == ",") {
			if (s.size() == 0) {
				result->returnType = buildType(vec, l, x); // the thing before the first comma is return type
				if (result->returnType->name == "function" && result->returnType->pointers == 0);
				per = x + 1; // illegal to return a function, but ok to pass pointers
				y = 1;
			} else if (s.size() == 1 && y) {
				if (vec[x - 1]->type != "var"); // pass not a variable
				result->types.push_back(vec[x - 1]->name);
				Type * tem = buildType(vec, per, x - 1);
				per = x + 1;
				if (tem->name == "function" && tem->pointers == 0); // illegal to pass a function as parameter, but ok to pass pointers
				result->types.push_back(tem);
			}
		}
	}
	if (per < h - 2) { // assume that the last thing is ")"
		int x = h - 2;
		if (vec[x - 1]->type != "var"); // pass not a variable
		result->types.push_back(vec[x - 1]->name);
		Type * tem = buildType(vec, per, x - 2);
		per = x + 1;
		if (tem == NULL); // illegal to pass a null thing as parameter
		if (tem->name == "function" && tem->pointers == 0); // illegal to pass a function as parameter
		result->types.push_back(tem);
	}
 	return result;
}

Type * GrammerTree::buildType(vector<treeNod *> & vec, int l, int h) {
	if (l <= h) return NULL;
	int pointers = 0, quantity;
	for (;vec[l]->name == "*" && l < h; l++) pointers++;
	Type * result = new Type(vec[l]->name);
	if (vec[h]->name == "]" && vec[h - 2]->name == "[") {
		if (result->pointers == 0 && result->name == "function"); // throw error no function allowed in the related type
		quantity = toNumber(vec[h - 1]->name);
		h -= 3;
		result->quantity = quantity;
	}
	if (h == l); // throw error
	if (vec[l]->type != "type"); // throw error, not a type 
	result->pointers = pointers;
	if (h - l == 1) {
		return result; 
	}
	l++;
	stack<char> s;
	stack<int> s1;
	vector<treeNod *> vec1
	if (vec->type == "type"); // throw error since this is not a type
	int per = l;
	for (int x = l; x <= h; x++) {
		if (vec[x]->type.compare("cal") == 0) {
			if (vec[x]->name == "<") s.push('<');
			else if (vec[x]->name == ">") {
				if (s.empty()); // throw error
				s.pop();
			}
			else if (vec[x]->name == "(") {
				s1.push(x + 1);
			}
			else if (vec[x]->name == ")") {
				if (s1.empty());  // throw error
				if (s1.size() == 1) {
					if (x != h); // throw error since nothing allowed after a function
					result->para = buildFunc(vec, s1.top(), x - 1);
					s1.pop();
				}
			}
			else if (vec[x]->name == ",") {
				if (s.size() == 0); //throw error
				if (s.size() == 1) {
					if (per <= x - 1);// throw error
					Type * tem = buildType(vec, per, x);
					if (tem->pointers == 0 && tem->name == "function"); // throw error no function allowed in the related type
					result->theRelatedTypes.push_back(tem);
					per = x + 1;
				}
			}
		}
	}
    result->theRelatedTypes.push_back(buildType(vec, per, h - 2));
    return result;
}

treeNod * GrammerTree::buildTreeDef(vector<treeNod *> & vec)	{
	if (vec[0]->type != "var");
	if (vec[1]->name != ":"); // throw error illegal definition
	t = buildType(vec, 2, vec.size() - 1);
	type = "def";
	if (t == NULL); // does not support null things 
	return new treeNod(vec[0]->name);
}


treeNod * GrammerTree::buildTreeOther(vector<treeNod *> & vec) {
	if (vec[0]->name == "{") {
		if (vec.size() == 1); // throw error
		return vec[0];
	}
	
	if (vec[0]->name.compare("class") == 0) {
		if (vec.size() != 2);
		type = "class"; // if the tree is to build a class
		return vec[1];
	}
	
	if (vec[0]->name.compare("if") == 0) {
	type = "if"; // the if tree
	return buildTreeIf(vec);	
    }
    
	if (vec[0]->name.compare("for") == 0) {
	type = "for";
	return buildTreeFor(vec);
	}
	
	if (vec[0]->name.compare("while") == 0) {
	type = "while"; //  the while tree
	return buildTreeWhile(vec);
	}
	
	if (vec[0]->name.compare("delete") == 0) {
		type = "delete"; // the import tree, which have imported something from other files
		return vec[1];
	}
	type = "def";
	return buildTreeDef(vec); // if all of other elses the definition tree which structured var:type
}

GrammerTree::GrammerTree(vector<string> vec, vector<LetterTree *> & tree) {
	string o[][] = {{"=", ",", "", "", ""}, {"||", "", "", "", ""}, {"&&", "", "", "", ""}, {"|", "", "", "", ""}, 
	{"&", "", "", "", ""}, {"==", "!=", "", "", ""}, {"<", "<=", ">", ">=", "instanceof"}, 
	{"<<", ">>", ">>>", "", ""}, {"+", "-", "", "", ""}, {"*", "/", " %", "", ""}, {"!", "~", "", "", ""}
	{".", "[", "(", "->", "func"}};
	freopen("theTypes.txt", "r", stdin);
	vector<treeNod *> i;
	for (int x = 0; x <= 12; x++) {
		vector<string> p;
		for (int y = 0; y < 5; y++) {
			if (o[x][y].compare("") == 0) continue;
			p.push_back(o[x][y]);
		}
		arr.push_back(p);
	}
	for (int x = 0; x < vec.size(); x++) { // judge whether it is a type or a var
		i.push_back(new treeNod(vec[x]));
		treeNode * node = NULL;
		for (int y = 0; y < tree.size(); y++) {
			node = tree.find(vec[x]);
			if (node != NULL) break;
		}
		if (node != NULL) i[x]->type = node->type;
		else i[x]->type = "var";             //make every string to be the tree
	}
	root = buildTree(i);
}


GrammerTree::~GrammerTree() {
	clear(root);
}


