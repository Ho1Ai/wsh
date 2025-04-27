#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdint.h>

// consts

#define MAX_INP_SIZE 320
#define MAX_ARG_COUNT 128
#define MAX_UNAME_LINE 128
#define MAX_PASSWD_LINE 64
#define MAX_PATH_SIZE 4096

//const char UNAME[] = "user";

// 'environmental' variables

char* current_path = "./";


// structs




// user session struct

typedef struct {
	char uname[MAX_UNAME_LINE]; //128 maybe?
	bool logged;
} UserSession;







// functions

// user session functions

uint8_t try_login (const char *uname_file, const char *passwd, UserSession* user_work_instance){
	char finalfile[256];
	snprintf(finalfile, sizeof(finalfile), "./../etc/userdata/%s.totmb", uname_file);
	FILE *file = fopen(finalfile, "r");
	if (!file) {
		printf("Couldn't find user with this name\n");
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

	uint8_t tester = try_login(uname_inp, passwd_inp, new_session);
	if (tester == 1){
		snprintf(new_session->uname, sizeof(new_session->uname), "%s", uname_inp);
		new_session->logged = true;
		return 1;
	} else {
		return 0;
	}
}





// commands list

uint8_t run_command(char **arg_parser /*, const char* args_list*/){
	char path[256];
	//pid_t pid = fork();
	snprintf(path, sizeof(path), "../bin/%s/%s", arg_parser[1], arg_parser[1]);
	//printf("%s\n\n",path);
	//printf("%s %s", path, arg_parser[0]);
	if (access (path, F_OK) != -1 && access(path, R_OK) != -1){ // R_OK?
		pid_t pid = fork();
		if (pid == 0) {
			execv(path, arg_parser);
			perror("execution failed");
			exit(1); // don't touch this stuff at the moment
		} else {
			int status;
			waitpid(pid, &status, 0);
			return 1; // cork
		}
		//printf("wsh: command found, do nothing\n");
	} else {
		printf("wsh: Command not found\n");
		return 1; //cork
		//printf("wsh: Command not found, unfortunately =(\n");
	}
}




void cd(char** args_list){
	if(args_list[2] != NULL) {
		//printf("%s\t%s\n", args_list[0], args_list[2]);
		char final_path[MAX_PATH_SIZE];
		if (strcmp(args_list[2], "..")!=0){
			char new_arg[MAX_PATH_SIZE];
			snprintf(new_arg, MAX_PATH_SIZE, "%s", args_list[2]);
			char *slash_in_new_name = strchr(new_arg, '/');
			//printf("%p", slash_in_new_name);

			if(slash_in_new_name) {
			*slash_in_new_name = '\0';
			}

			//printf("%d", strlen(new_arg));
			
			snprintf(final_path, sizeof(final_path), "%s%s/", args_list[0], new_arg);
		} else {
			snprintf(final_path, sizeof(final_path), "%s", args_list[0]);
			if(final_path[strlen(final_path)-1] == '/' && strcmp(final_path,"./") !=0) {
				final_path[strlen(final_path)-1] = '\0';
				char* last_slash_ptr = strrchr(final_path, '/');
				*last_slash_ptr = '\0';
			}

			if(strlen(final_path) == 1) {
				snprintf(final_path, sizeof(final_path), "./");
			}
		}
	
		//printf("%s", final_path);
		DIR* test_dir = opendir(args_list[2]);
		if(!test_dir) {
			printf("An error occured: no such file or directory. \n");
		} else {
			closedir(test_dir);
			current_path = final_path;
		}
	} else {
		current_path = "./";
	}
	return;
}








// shell

void shell_input(UserSession* new_session){
	bool changing_dir = false;
	char input[MAX_INP_SIZE];
	char* t_args[MAX_ARG_COUNT];

	int arg_count = 0;
	printf("[wsh@%s] >> ", new_session->uname);
	if(fgets(input, MAX_INP_SIZE, stdin)==NULL) {
		new_session->logged = false;
		printf("^D");
		printf("\nGoodbye!");
		return;
	};
	input[strcspn(input, "\n")]='\0';
	
	char* getter = strtok(input, " ");

	t_args[arg_count++] = current_path;//by default we use our current pwd

	while(getter != NULL && arg_count < MAX_ARG_COUNT) {
		t_args[arg_count++] = getter;
		getter = strtok(NULL, " ");
	} // yeah, only after 3 days of trying to fix it I asked ChatGPT to help me, lol. I didn't know about strtok
	t_args[arg_count++] = NULL;
	//printf("%s", getter[0]);
	//printf("%s", t_args[0]);
	
	if(strcmp(input, "")!=0){
		if(strcmp(input, "cd")==0){
			changing_dir=true;
			cd(t_args);
			shell_input(new_session);
		} // just a simple cork, which is needed because I have current_path variable in main.c. I don't use chdir or smth like that because this shell will be rewritten 'from scratch'

		if(strcmp(input, "exit")==0){ // yeah, I am very lazy to use it in different file (e.g. exit.c)
			memset(new_session->uname, 0, sizeof(new_session->uname) );
			new_session->logged = false;
			printf("Goodbye!");
		} else {
			if (!changing_dir){
				uint8_t a = run_command(t_args);
				if (a == 1){
					shell_input(new_session); 
				}
			}//recursive call of this function, which means that it is always in input status
		}
	} else {
		shell_input(new_session);
	}
}







//defaults

int main() {
	UserSession* new_session = malloc(sizeof(UserSession));
	while (new_session->logged == false){
		login(new_session);
	} 
	if (new_session->logged == true) {
		shell_input(new_session);
	}
	free(new_session);
	return 0;
}
