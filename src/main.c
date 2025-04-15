#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_UNAME_LINE 128
#define MAX_PASSWD_LINE 64

//const char UNAME[] = "user";

typedef struct {
	char uname[MAX_UNAME_LINE]; //128 maybe?
	bool logged;
} UserSession;

uint8_t try_login (const char *uname_file, const char *passwd, UserSession* user_work_instance){
	char finalfile[256];
	snprintf(finalfile, sizeof(finalfile), "./../etc/userdata/%s.totmb", uname_file);
	FILE *file = fopen(finalfile, "r");
	if (!file) {
		perror("Couldn't find user with this name");
		return 0;	
	};

	
	
	char infile_passwd[MAX_PASSWD_LINE];
	fgets(infile_passwd, sizeof(infile_passwd), file);
	infile_passwd[strcspn(infile_passwd, "\n")] = 0;
	fclose(file);
	//printf("%s%s",infile_passwd, passwd);
	char li_passwd[64]; // li means local instance. I can't change arg
	snprintf(li_passwd, sizeof(li_passwd), "%s", passwd);
	li_passwd[strcspn(li_passwd, "\n")]=0;
	if(strcmp(infile_passwd, li_passwd) == 0) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t login(UserSession *new_session){
	char uname_inp[MAX_UNAME_LINE];
	char passwd_inp[MAX_PASSWD_LINE];
	
	

	if (new_session->logged == false) {
		printf("login: ");
		fgets(uname_inp, sizeof(uname_inp), stdin);
		uname_inp[strcspn(uname_inp, "\n")] = 0;
		printf("password: ");
		fgets(passwd_inp, sizeof(passwd_inp), stdin);
	}

	if (try_login(uname_inp, passwd_inp, new_session) == 1){
		return 1;
	} else {
		return 0;
	}
}

void run_command(const char *name){
	char path[256];
	pid_t pid = fork();
	snprintf(path, sizeof(path), "../bin/%s/%s", name, name);
	if (access (path, F_OK) != -1 && access(path, R_OK) != -1){ // R_OK?
		if (pid == 0) {
			execl(path, name, NULL);
			perror("execution failed");
			exit(1);
		} else {
			int status;
			waitpid(pid, &status, 0);
		}
		//printf("wsh: command found, do nothing\n");
	} else {
		printf("wsh: Command not found, unfortunately =(\n");
	}
}

void shell_input(UserSession* new_session){
	char input[256];
	printf("[wsh@%s] >> ", new_session->uname);
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")]=0;
	if(strcmp(input, "")!=0){ 
	if(strcmp(input, "exit")==0){
			memset(new_session->uname, 0, sizeof(new_session->uname) );
			new_session->logged = false;
			printf("Goodbye!");
		} else {
			printf("You have entered: %s\n", input);
			run_command(input);
			shell_input(new_session); //recursive call of this function, which means that it is always in input status
		}
	} else {
		shell_input(new_session);
	}
}

int main() {
	UserSession* new_session = malloc(sizeof(UserSession));
	while (new_session->logged == false){
		login(new_session);
	} 
	if (new_session->logged == true) {
		shell_input(new_session);
	}
	return 0;
}
