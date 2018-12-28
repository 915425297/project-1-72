#ifndef _SENTENCE_ANALYSER
#define _SENTENCE_ANALYSER
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include "word_analyser.h"
#include "letter_tree.h"
#include "grammer_tree.h"
using namespace std;
class sentenceAnalyser { // manager of the whole text
// all of the things will be gathered in a single file
	public:
		vector<string> txt;
		string head = ""; // the name of the file
		LetterTree * tree;
		static vector<LetterTree *> allTree; // all trees contained in this file
		sentenceAnalyser(string g) {
			tree = new LetterTree();
			allTree.push_back(tree);
			tree->name = g;
			g[g.length() - 1] = 0;
			g[g.length() - 1] = "s";
			head = g;
		}
		~sentenceAnalyser() {
		}
		void scanner();
};
#endif
