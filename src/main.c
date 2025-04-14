#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

const char UNAME[] = "user";

void run_command(const char *name){
	char path[256];
	snprintf(path, sizeof(path), "../bin/%s/%s", name, name);
	if (access (path, F_OK) != -1)
}

void shell_input(){
	char input[256];
	printf("[wsh@%s] >> ", UNAME);
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")]=0;
	if(strcmp(input, "exit")==0){
		printf("Goodbye!");
	} else {	
		printf("You have entered: %s\n", input);
		shell_input();
	}
}

int main() {
	shell_input();
	return 0;
}
