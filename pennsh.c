#include "pennsh.h"
void controlCHandler(int signal) {
	for (int x = 0; x < number; x++) kill(pid[number], SIGINT);
}

int parseInput(char * t) {
	if (t) return 0;
	
}

void flushInput() {
	char i[MAX_BUFFER] = {0};
	read(0, i, MAX_BUFFER);
	while(i[MAX_BUFFER - 1] && i[MAX_BUFFER - 1] == '\n') {
		i[MAX_BUFFER - 1] = 0;
		read(0, i, MAX_BUFFER);
	}
}

int main() {
	
	return 0;
}
