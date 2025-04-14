#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <dirent.h>
//#include <sys/wait.h>

const char UNAME[] = "user";



void run_command(const char *name){
	char path[256];
	//pid_t pid = fork();
	snprintf(path, sizeof(path), "../bin/%s/%s", name, name);
	if (access (path, F_OK) != -1 && access(path, R_OK) != -1){ // R_OK?
	/*	if (pid == 0) {
			printf("wsh: command found, do nothing\n");	
		} else {
			
		}*/
		printf("wsh: command found, do nothing\n");
	} else {
		printf("wsh: Command not found, unfortunately =(\n");
	}
}

void shell_input(){
	char input[256];
	printf("[wsh@%s] >> ", UNAME);
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")]=0;
	if(strcmp(input, "")!=0){ 
	if(strcmp(input, "exit")==0){
			printf("Goodbye!");
		} else {
			printf("You have entered: %s\n", input);
			run_command(input);
			shell_input(); //recursive call of this function, which means that it is always in input status
		}
	} else {
		shell_input();
	}
}

int main() {
	shell_input();
	return 0;
}
