#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[128];
	char path[256];
	char passwd[64];
	//int groups; //not used at the moment
} NewUser; // why did I add this stuff if I still don't use it, lmao?

/* Groups:
 * 1. video (group for terminal and other users)
 * 2. audio (group for sound. In the beggining it will be used for debug)
 * 3. storage (not used at the moment, but in the future it will be checked before mounting other partations)
 * 4. wheel (to make division between native user and super user)
*/

uint8_t createUser(NewUser* new_user_instance, const char *name, const char *passwd) {
	
}

int main(){
	NewUser *new_user_instance = malloc(sizeof(NewUser));
	char uname_input[128];
	char passwd_input[64];

	printf("Enter new username: \n");
	fgets(uname_input, sizeof(uname_input), stdin);
	
	printf("Enter the password for new user: \n");
	fgets(passwd_input, sizeof(passwd_input), stdin);
	//printf("%s\n%s\n", uname_input, passwd_input);
	uname_input[strcspn(uname_input, "\n")]=0;
	//printf("%d",strcspn(uname_input, "\n"));
	//printf("from this point it can't be outputed, unforunately");
	passwd_input[strcspn(passwd_input, "\n")]=0;
	
	char new_user_file[256];
	snprintf(new_user_file, sizeof(new_user_file), "./../etc/userdata/%s.totmb", uname_input);

	//printf("%s", uname_input);

	// adding strings into the struct. It is needed because this script will include groups in the future	
	//snprintf(new_user_instance->name, sizeof(new_user_instance->name), "%s", uname_input);
	//snprintf(new_user_instance->path, sizeof(new_user_instance->path), "%s", new_user_file);
	//snprintf(new_user_instance->passwd, sizeof(new_user_instance->passwd), "%s", passwd_input);
	
	
	FILE *file = fopen(new_user_file, "r");
	if (!file) {
		FILE *input = fopen(new_user_file, "w");
		fputs(passwd_input, input);
		fclose(input);
		printf("User has been created succesfully\n");
	}else{
		fclose(file);
	}

	//printf("You have entered: %s", uname_input);
	return 0;
}