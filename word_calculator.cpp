#include "word-analyser.h"
// all of the self-defined terms the stack must allocate space for them
jy wordAnalyser::operatorAdd(jy p1, jy p2, treeNod * root, string txt, int & move) {
			freopen(txt, "w", stdout);
			jy n;
			if (p1->p.name == "int") {
				printf("add $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "t1";
			}
			else if (p1->p.name == "float") {
				printf("add.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "long") {
				if ("")
			}
			else if (p1->p.name == "double") {
				printf("add.d $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1->p.length / 32;
				move += p1->p.size;
				printf("move $v0, $sp\n");
				printf("sub $sp, $sp, %d\n", &p1->p.size);
				printf("move $t5, $zero\n");
				printf("li $t6, $zero\n"); // the carry out register
				for (int x = 0; x < y; x++) { // add one reg by one reg each is 32-bit
					int u = 4 * x;
					printf("lw $t3, %d($%s)\n", &u, &p1->reg1);
					printf("lw $t4, %d($%s)\n", &u, &p1->reg2);
					printf("add $t5, $t3, $t4\n");
					printf("add $t5, $t5, $t6\n");
					printf("sw $t5, %d($sp)\n", &u);
					printf("or $t6, $t3, $t4\n");
					printf("xor $t6, $t5, $t6\n");
					printf("srlu $t6, $t6, 31\n");
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_+\n", &p1->type->name1);
			}
}

jy wordAnalyser::operatorMul(jy p1, jy p2, treeNod * root, string txt, int & move) {
			freopen(txt, "w", stdout);
			jy n;
			if (p1->p.name == "int" || p1->p.name == "unsigned") {
				printf("mul $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "t1";
			}
			else if (p1->p.name == "float") {
				printf("mul.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "long") {
				if ("")
			}
			else if (p1->p.name == "double") {
				printf("mul.d $f2, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f2";
			}
			else if (p1->p.name == "selfDefine") { // big endian the most significant bit is on the top address
			// can only be signed
				int y = p1->p.length / 16;
				move += p1->p.size;
				printf("move $v0, $sp\n");
				printf("sub $sp, $sp, %d\n", &p1->p.size);
				printf("move $t5, $zero\n");
				printf("li $t6, $zero\n"); // the carry out register		
				for (int x = 0; x < y; x++) { // add one reg by one reg each is 32-bit
					int u = 2 * x;
					printf("lhu $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("lhu $t4, (%d)$%s\n", &u, &p1->reg2);
					printf("mul $t5, $t3, $t4\n");
					printf("add $t5, $t5, $t6\n");
					printf("and $t7, $t5, 65535\n");
					if (x == y - 1) {
						printf("sgtu $t8, $t7, 65536\n");
						printf("mul $t8, $t8, 32768\n");
						printf("or $t7, $t8, $t7n");
					} 
					printf("sh $t7, (%d)$v0\n", &u);
					printf("sub $t6, $t5, $t7\n");
				}
			}
			else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_+\n", &p1->type->name);
			}
}

jy wordAnalyser::operatorDiv(treeNod * root, string txt, int & move) {// high precision division
}

jy wordAnalyser::operatorRem(treeNod * root, string txt, int & move) {// high precision division, not yet known
}

jy wordAnalyser::operatorOr(jy p1, jy p2, treeNod * root, string txt, int & move) {
			freopen(txt, "w", stdout);
			jy n;
			if (p1->p.name == "int") {
				printf("or $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "t1";
			}
			else if (p1->p.name == "float") {
				// throw error there is no calculation for float
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "long") {
				if ("")
			}
			else if (p1->p.name == "double") {
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1->p.length / 32;
				move += p1->p.size;
				printf("move $v0, $sp\n");
				printf("sub $sp, $sp, %d\n", &p1->p.size);
				printf("move $t5, $zero\n");
				for (int x = 0; x < y; x++) { // add one reg by one reg each is 32-bit
					int u = 4 * x;
					printf("lw $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("lw $t4, (%d)$%s\n", &u, &p1->reg2);
					printf("or $t5, $t3, $t4\n");
					printf("sw $t5, %d($sp)\n", &u);
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_|\n", &p1->type->name);
			}
}

jy wordAnalyser::operatorAnd(jy p1, jy p2, treeNod * root, string txt, int & move) {
			freopen(txt, "w", stdout);
			jy n;
			if (p1->p.name == "int") {
				printf("and $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "t1";
			}
			else if (p1->p.name == "float") {
				// throw error there is no calculation for float
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "long") {
				if ("")
			}
			else if (p1->p.name == "double") {
				// throw error there is no calculation for float
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1->p.length / 32;
				move += p1->p.size;
				printf("move $v0, $sp\n");
				printf("sub $sp, $sp, %d\n", &p1->p.size);
				printf("move $t5, $zero\n");
				for (int x = 0; x < y; x++) { // add one reg by one reg each is 32-bit
			
					int u = 4 * x;
					printf("lw $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("lw $t4, (%d)$%s\n", &u, &p1->reg2);
					printf("and $t5, $t3, $t4\n");
					printf("sw $t5, %d($sp)\n", &u);
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_&\n", &p1->type->name);
			}
}

jy wordAnalyser::operatorXor(jy p1, jy p2, treeNod * root, string txt, int & move) {
			freopen(txt, "w", stdout);
			jy n;
			if (p1->p.name == "int") {
				printf("xor $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "t1";
			}
			else if (p1->p.name == "float") {
				// throw error there is no calculation for float
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "long") {
				// throw error since x32 machine does not support this kind of data structure
			}
			else if (p1->p.name == "double") {
				// throw error there is no calculation for float
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1->p.length / 32;
				move += p1->p.size;
				printf("move $v0, $sp\n");
				printf("sub $sp, $sp, %d\n", &p1->p.size);
				printf("move $t5, $zero\n");
				for (int x = 0; x < y; x++) { // add one reg by one reg each is 32-bit
					int u = 4 * x;
					printf("lw $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("lw $t4, (%d)$%s\n", &u, &p1->reg2);
					printf("xor $t5, $t3, $t4\n");
					printf("sw $t5, (%d)$sp\n", &u);
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_^\n", &p1->type->name);
			}
}

jy wordAnalyser::operatorNot(jy p1, jy p2, treeNod * root, string txt, int & move) {
			freopen(txt, "w", stdout);
			jy n;
			if (p1->p.name == "int") {
				printf("not $t1, $%s\n", &p1->reg1);
				n.p = p1.p;
				n.reg1 = "t1";
			}
			else if (p1->p.name == "float") {
				// throw error there is no calculation for float
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "long") {
				// throw error since x32 machine does not support this kind of data structure
			}
			else if (p1->p.name == "double") {
				// throw error there is no calculation for duoble
				printf("sub.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.p = p1.p;
				n.reg1 = "f1";
			}
			else if (p1->p.name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1->p.length / 32;
				move += p1->p.size;
				printf("move $v0, $sp\n");
				printf("sub $sp, $sp, %d\n", &p1->p.size);
				for (int x = 0; x < y; x++) { // add one reg by one reg each is 32-bit
					int u = 4 * x;
					printf("lw $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("not $t5, $t3\n");
					printf("sw $t5, (%d)$sp\n", &u);
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_~\n", &p1->type->name);
			}
}

jy wordAnalyser::operatorGreater(jy p1, jy p2, treeNod * root, string txt, int & move, int & flag) {
			freopen(txt, "w", stdout);
			jy n;
			if (p1->p.name == "int") {
				printf("sgt $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "t1";
			}
			else if (p1->p.name == "float") {
				// throw error there is no calculation for float
				printf("sgt.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "f1";
			}
			else if (p1->p.name == "unsigned") {
				printf("sgtu $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "t1";
			}
			else if (p1->p.name == "long") {
				if ("")
			}
			else if (p1->p.name == "double") {
				// throw error there is no calculation for float
				printf("sgt.d $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "f1";
			}
			else if (p1->p->name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1->p.length / 32;
				move += p1->p.size;
				printf("mov $t6, $zero\n");
				printf("mov $t7, $zero\n");
				for (int x = y - 1; x >= 0; x++) { // add one reg by one reg each is 32-bit
					int u = 4 * x;
					printf("lw $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("lw $t4, (%d)$%s\n", &u, &p1->reg2);
					if (x == y - 1)  {
						printf("slt $t5, $t3, $t4\n");
						printf("sgt $t6, $t3, $t4\n");
					} else {
						printf("sltu $t5, $t3, $t4\n");
						printf("sgtu $t6, $t3, $t4\n");
					}
					printf("bne $t5, $zero, compare1_%d\n", &flag); // return failure
					printf("bne $t6, $zero, compare2_%d\n", &flag); // return success
					printf("slt $t5, $t3, $t4\n");
				}
				n.reg1 = "v0";
				printf("compare1_%d:\n", &flag);
				printf("li $v0, 0\n");
				printf("compare2_%d:\n", &flag);
				printf("li $v0, 1\n");
				flag += 1;
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_>\n", &p1->type->name);
			}
			return n;
}

jy wordAnalyser::operatorLess(jy p1, jy p2, treeNod * root, string txt, int & move, int & flag) {
			freopen(txt, "w", stdout);
			jy n;
			
			if (p1->p->name == "int") {
				printf("slt $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "t1";
			}
			else if (p1->p->name == "unsigned") {
				printf("sltu $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "t1";
			}
			else if (p1->p->name == "float") {
				// throw error there is no calculation for float
				printf("slt.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "f1";
			}
			else if (p1->p->name == "long") {
				if ("")
			}
			else if (p1->p->name == "double") {
				// throw error there is no calculation for float
				printf("slt.d $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "f1";
			}
			else if (p1->p->name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1->p->length / 32;
				move += p1->p->size;
				printf("mov $t6, $zero\n");
				printf("mov $t7, $zero\n");
				for (int x = y - 1; x >= 0; x++) { // add one reg by one reg each is 32-bit
					int u = 4 * x;
					printf("lw $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("lw $t4, (%d)$%s\n", &u, &p1->reg2);
					if (x == y - 1)  {
						printf("slt $t5, $t3, $t4\n");
						printf("sgt $t6, $t3, $t4\n");
					} else {
						printf("sltu $t5, $t3, $t4\n");
						printf("sgtu $t6, $t3, $t4\n");
					}
					printf("bne $t5, $zero, compare1_%d\n", &flag); // return failure
					printf("bne $t6, $zero, compare2_%d\n", &flag); // return success
					printf("slt $t5, $t3, $t4\n");
				}
				n.reg1 = "v0";
				printf("compare2_%d:\n", &flag);
				printf("li $v0, 0\n");
				printf("compare1_%d:\n", &flag);
				printf("li $v0, 1\n");
				flag += 1;
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_<\n", &p1->type->name);
			}
			return n;
}

jy wordAnalyser::operatorGreaterEqual(jy p1, jy p2, treeNod * root, string txt, int & move, int & flag) {
			freopen(txt, "w", stdout);
			jy n;
			
			if (p1->p->name == "int") {
				printf("sgt $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "t1";
			}
			else if (p1->p->name == "unsigned") {
				printf("sgtu $t1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "t1";
			}
			else if (p1->p->name == "float") {
				// throw error there is no calculation for float
				printf("sgt.s $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "f1";
			}
			else if (p1->p->name == "long") {
				if ("")
			}
			else if (p1->p->name == "double") {
				// throw error there is no calculation for float
				printf("sgt.d $f1, $%s, $%s\n", &p1->reg1, &p2->reg1);
				n.reg1 = "f1";
			}
			else if (p1->p->name == "selfDefine") { // big endian the most significant bit is on the top address
				int y = p1.p.length / 32;
				move += p1.p.size;
				printf("mov $t6, $zero\n");
				printf("mov $t7, $zero\n");
				for (int x = y - 1; x >= 0; x++) { // add one reg by one reg each is 32-bit
					int u = 4 * x;
					printf("lw $t3, (%d)$%s\n", &u, &p1->reg1);
					printf("lw $t4, (%d)$%s\n", &u, &p1->reg2);
					if (x == y - 1)  {
						printf("slt $t5, $t3, $t4\n");
						printf("sgt $t6, $t3, $t4\n");
					} else {
						printf("sltu $t5, $t3, $t4\n");
						printf("sgtu $t6, $t3, $t4\n");
					}
					printf("bne $t5, $zero, compare1_%d\n", &flag); // return failure
					printf("bne $t6, $zero, compare2_%d\n", &flag); // return success
					printf("slt $t5, $t3, $t4\n");
				}
				n.reg1 = "v0";
				printf("compare2_%d:\n", &flag);
				printf("li $v0, 1\n");
				printf("compare1_%d:\n", &flag);
				printf("li $v0, 0\n");
				flag += 1;
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_>=\n", &p1->type->name);
			}
			return n;
}

jy wordAnalyser::operatorDereference(jy * p1, treeNod * root, string txt) {
			freopen(txt, "w", stdout);
			jy n;
			n.p = p1->p;
			if (n.p.pointers <= 0); // throw error
			n.p.pointers--;if ( || p1->p->name == "float" ) 
			if (p1->p->name == "int"|| p1->p->name == "unsigned") {
				printf("lw $t1, 0($%s)\n", &p1->reg1);
				n.reg1 = "t1";
			} else if (p1->p->name == "selfDefine") { // big endian the most significant bit is on the top address
				printf("lw $t1, 0($%s)\n", &p1->reg1);
				n.reg1 = "t1";
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_*\n", &p1->type.name);
			}
			return n;
}

jy wordAnalyser::operatorRightShiftUnsigned(jy * p1, treeNod * root, string txt, int & flag) {
			freopen(txt, "w", stdout);
			jy n;
			n.p = p1->p;
			if (n.p.pointers <= 0); // throw error
			n.p.pointers--;if (p1->p->name == "float" || )
			if (p1->p->name == "int" || p1->p->name == "unsigned") {
				printf("sll $t1, $%s, $%s\n", &p1->reg1, & p1->reg2);
				n.reg1 = "t1";
			} else if (p1->p->name == "selfDefine") { // big endian the most significant bit is on the top address
				printf("lw $t4, 0($%s)\n", &p1->reg2); // the left shift will be limited to 32-bit
				printf("div $t6, $t4, 32\n");
				printf("rem $t7, $t4, 32\n");
				printf("mul $t6, $t6, 4\n");
				printf("add $t7, $%s, $t6\n", &p1->reg1);
				printf("sll $t5, 1, $t7\n");
				printf("sub $t5, $t5, 1\n");
				int y = p1->p->length / 4;
				move += p1.p.size;
				printf("lw $t3, 0($t7)\n");
				for (int x = 1; x < y; x++) {
					int u = 4 * x;
					int p = 4 * (y - x - 1);
					printf("ble $t6, %d, LeftShift1%d\n", &p, &flag);
					printf("srlu $t3, $t3, $t7\n");
					printf("lw $t4, %d($t7)\n", &u);
					printf("blt $t6, %d, LeftShift2%d\n", &p, &flag);
					printf("and $t8, $t4, $t5\n");
					printf("sll $t8, $t8, $t7\n");
					printf("add $t3, $t3, $t8\n");
					printf("LeftShift2%d:\n", &flag);
					printf("sw $t3, %d($sp)\n", &u);
					printf("mov $t3, $t4\n");
					printf("LeftShift1%d:\n", &flag);
					printf("sw $zero, %d($sp)\n", &u);
					flag++;
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_>>>\n", &p1->type.name);
			}
			return n;
}

jy wordAnalyser::operatorLeftShift(jy * p1, treeNod * root, string txt, int & flag) {
			freopen(txt, "w", stdout);
			jy n;
			n.p = p1->p;
			if (n.p.pointers <= 0); // throw error
			if (p1->p->name == "int" || p1->p->name == "unsigned") {
				printf("sll $t1, $%s, $%s\n", &p1->reg1, & p1->reg2);
				n.reg1 = "t1";
			} else if (p1->p->name == "selfDefine") { // big endian the most significant bit is on the top address
				printf("lw $t4, 0($%s)\n", &p1->reg2); // the left shift will be limited to 32-bit
				int y = p1->p->length / 4;
				printf("sub $sp, $sp, %d\n", &y);
				printf("lw $t9, %d($%s)", &y, &p1->reg1);
				printf("slt $t9, $t9, $zero\n");
				printf("sub $t9, $zero, $t9\n");
				printf("div $t6, $t4, 32\n");
				printf("rem $t7, $t4, 32\n");
				printf("mul $t6, $t6, 4\n");
				printf("add $t7, $%s, $t6\n", &p1->reg1);
				printf("sll $t5, 1, $t7\n");
				printf("sub $t5, $t5, 1\n");
				move += p1.p.size;
				printf("lw $t3, 0($t7)\n");
				for (int x = 1; x < y / 8; x++) {
					int u = 4 * x;
					int p = 4 * (y - x - 1);
					printf("ble $t6, %d, LeftShift4%d\n", &p, &flag);
					printf("srlu $t3, $t3, $t7\n");
					printf("lw $t4, %d($t7)\n", &u);
					printf("blt $t6, %d, LeftShift3%d\n", &p, &flag);
					printf("and $t8, $t4, $t5\n");
					printf("sll $t8, $t8, $t7\n");
					printf("add $t3, $t3, $t8\n");
					printf("j LeftShift5%d:\n", &flag);
					printf("LeftShift3%d:\n", &flag);
					printf("sll $t8, 1, $t7\n");
					printf("sub $t8, $t8, 1\n");
					printf("xor $t8, $t8, $t7\n");
					printf("or $t3, $t8, $t3\n");
					printf("LeftShift5%d:\n", &flag);
					printf("sw $t3, %d($sp)\n", &u);
					printf("mov $t3, $t4\n");
					printf("LeftShift4%d:\n", &flag);
					printf("sw $t9, %d($sp)\n", &u);
					flag++;
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_>>\n", &p1->type.name);
			}
			return n;
}

jy operatorEqual(jy * p1, treeNod * root, string txt) {
			freopen(txt, "w", stdout);
			jy n;
			n.p = Type("bool");
			if (n.p.pointers <= 0); // throw error
			n.p.pointers--;
			n.reg1 = "t1";
			if (p1->p->name == "int" || p1->p->name == "char" 
			|| p1->p->name == "bool" || p1->p->name == "short") {
				printf("seq $t1, $%s, $%s\n", &p1->reg1, & p1->reg2);
			} else if (p1->p->name == "selfDefine") {
				printf("lw $t4, 0($%s)\n", &p1->reg2);
				int y = p1->p->length / 32;
				printf("li $t1, 1\n");
				for (int x = 0; x < y; x++) {
					printf("lw $t4, %d($%s)\n", &u, &p1->reg1);
					printf("lw $t5, %d($%s)\n", &u, &p1->reg2);
					printf("seq $t2, $t4, $t5\n");
					printf("and $t1, $t2, $t1\n");
				}
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_==\n", &p1->type.name);				
			}
			return n;
}

jy operatorNotEqual(jy * p1, treeNod * root, string txt) {
			freopen(txt, "w", stdout);
			jy n;
			n.p = Type("bool");
			if (n.p.pointers <= 0); // throw error
			n.p.pointers--;
			n.reg1 = "t1";
			if (p1->p->name == "int" || p1->p->name == "char" 
			|| p1->p->name == "bool" || p1->p->name == "short") {
				printf("sne $t1, $%s, $%s\n", &p1->reg1, & p1->reg2);
			} else if (p1->p->name == "selfDefine") {
				printf("lw $t4, 0($%s)\n", &p1->reg2);
				int y = p1->p->length / 32;
				printf("li $t1, 1\n");
				for (int x = 0; x < y; x++) {
					printf("lw $t4, %d($%s)\n", &u, &p1->reg1);
					printf("lw $t5, %d($%s)\n", &u, &p1->reg2);
					printf("seq $t2, $t4, $t5\n");
					printf("and $t1, $t2, $t1\n");
				}
				printf("not $t1, $t1\n");
			} else {
				printf("move $a0, $%s\n", &p2->reg1);
				printf("move $a1, $%s\n", &p2->reg2);
				printf("jal %s_!=\n", &p1->type.name);				
			}
			return n;
}

