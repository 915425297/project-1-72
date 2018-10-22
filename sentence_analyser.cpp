#include "sentence_analyser.h"
void divide (string & t) {
	for (int x = 0; x < t.length(); x++) {
		if (t[x] == ' ' || t[x] == '	' || t[x] == '\n') {
			t = t.substr(0, x) + t.substr(x + 1, t.length() - x - 1);
		}// divide eliminate ""	
	}
}

struct threeThings{
	ClassTree * c = NULL;
	Func * f = NULL;
	string whileOrIf = "";
	int flag;
};

void sentenceAnalyser::scanner() {
	freopen(head, "r", stdin);
	stack<threeThings> s;
	int flag1 = 0, flag2 = 9999999;
	wordAnalyser sp(flag1, flag2);
	//ClassTree * l = NULL; class tree indicate the class that this sentence is currently in
	string head = ""; 
	sp->tree1.push_back(tree);
	//	string w = ""; 
	// the if or while {}
	// Func * p = NULL; 
	// function which indicate which function this is currently in
	
	for (int x = 0; x < txt.size() x++) {
		divide(txt[x]);
		threeThings ti;
		if (txt[x].substr(0, 6) == "import") {
			unsigned x = 0;
			for (; x < allTree.size(); x++) {
				if (allTree[x]->name == txt[x].substr(7, txt[x].length() - 6))) sp.tree1.push_back(allTree[x]);
			}
			if (x == allTree.size()); // throw error file not found
			continue;
		}
		sp.scanner(txt[x], head, s.top().c, s.top().f);
		ti.f = s.top().f;
		ti.whileOrIf = s.top().whileOrIf;
		ti.c = s.top().c;
		if (sp.strings[0] == "class") { // deal with the condition when there are some class declared
			if (sp.strings.size() != 3 || sp.strings[1] != ":"); // throw error on my sp
			Type * t = new Type("class");
			sp.tree1[sp.tree1.size() - 1]->insert(sp.strings[2], t);
			ClassTree * l = new ClassTree(sp.strings[2]);
			t->cpara = l;
			ti.c = l;
			continue;
		}
		
		if (sp.t->name == "function") {
			txt = sp.strings[sp.strings.size() - 1]; // txt = name of the function
			ti.f = sp.t->para;// not yet done
			ti.whileOrIf = s.top().whileOrIf;
			ti.c = s.top().c;
		}
		
		if (sp.strings[0] == "while") {
			ti.whileOrIf = "while";
		}
		
		if (sp.strings[0] == "for") {
			ti.whileOrIf = "for";
		}
		
		if (sp.strings[0] == "if") {
			ti.whileOrIf = "if";
		}
		
		if (sp.strings[0] == "else" && sp.strings.size() == 1) {
			ti.whileOrIf = "else";
		}
		
		if (sp.strings[0] == "else" && sp.strings[1] == "if") {
			ti.whileOrIf = "else_if";
		}
		
		if (sp.strings[0] == "{") {
			flag1++;
			if (p == NULL && l == NULL && ti.whileOrIf == "" && ti.f == NULL && ti.c == NULL); // throw error
			switch(ti.whileOrIf) {
				case("while") {
					// jump to else + flag1;
					// cout loop + flag1
					break;
				}
				case("if") {
					// jump to else + flag1;
					
					break;
				}
				case("for") {
					// cout loop + flag1
					// jump to done + flag1;
					break;
				}
				case("else") {
					// cout else flag1
					printf("else%d:\n", &flag2);
					flag2++;
					flag1--;
					break;
				}
				case("else_if") {
					// jump to else + flag1;
					// cout else flag1
					printf("else%d:\n", &flag2);
					flag2++;
					flag1--;
					break;
				}
			}
			ti.flag = flag1;
			s.push(ti);
		}
		
		if (sp.strings[0] == "}") {
			ti = s.top();
			s.pop();
			if (ti.whileOrIf != s.top().whileOrIf) {
				switch(ti.whileOrIf) {
				case("while") {
					// jump to loop + ti.flag1;
					printf("j loop%d\n", &ti.flag1);
					break;
				}
				case("if") {
					if (x < txt.size() && (txt[x + 1] == "else if" || txt[x + 1] == "else")) printf("j done%d\n", &ti.flag1);// jump to done + ti.flag1;
					else printf("done%d:\n", &ti.flag1);
					break;
				}
				case("else") {
					printf("done%d:\n", &ti.flag);
					break;
				}
				case("else_if") {
					// cout else + flag1;
					if (x < txt.size() && (txt[x + 1] == "else if" || txt[x + 1] == "else")) printf("j done%d\n", &ti.flag1);
					else printf("done%d:\n", &ti.flag1);
					break;
				}
			}
			}
		}
	}
	if (!s.empty()); // throw error { does not match with each others
	allTree.push_back(tree);
}

void sentenceAnalyser::sentenceAnalyser(string t) {
	freopen(t, "stdin", "r");
	int y;
	for (y = t.length() - 1; y >= 0 && t[y] != "."; y--);
	head = t.substr(0, y);
	// cin from file
	int per = 0;
    for (int x = 0; x < t.length(); x++) {
    	if (t[x]== '\n') {
    		t = t.substr(0, x) + t.substr(x + 1, t.length() - x - 1);
    		x--;
		}
		
		if (t[x] == ';') {
			txt.push_back(t.substr(per, x - per));
    		per = x + 1;
		}
		
		if (t[x] == '{') {
			txt.push_back(t.substr(per, x - per));
			txt.push_back("{");
    		per = x + 1;
		}
		
		if (t[x] == '}') {
			txt.push_back(t.substr(per, x - per));
			txt.push_back("}");
    		per = x + 1;
		}
	}
}

