#ifndef _WORD_ANALYSER
#define _WORD_ANALYSER
#include <cstring>
#include <iostream>
#include <vector>
#include "grammer_tree.h"
#include "class.h"
#include "letter_tree.h"
using namespace std;
struct jy {
	Type p;
	string reg1 = "";
	string reg2 = "";
};
class wordAnalyser { // manager of a single sentence
	public:
		vector<LetterTree *> tree1;
		vector<string> strings;
		wordAnalyser(int & flag11, int & flag21):fkag1(flag11), flag2(flag21);
		int & flag1;
		int & flag2;
		Type * t;
		bool checkWhetherConnection(char t);
		void scanner(string g, string head, ClassTree * ctree, Func * f);
		bool judgeLegal(string s);
		bool checkWhetherDef(string s);
		void treeWriter(GrammerTree & tree, string head, ClassTree * ctree, Func * f);
		jy wordAnalyser::operatorAdd(treeNod * root, string txt, int & move);
		jy wordAnalyser::operatorSub(treeNod * root, string txt, int & move);
		~wordAnalyser() {
			for (int x = 1; x < tree1.size(); x++) delete tree1[x];
		}
};
#endif
