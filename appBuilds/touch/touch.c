#include <stdio.h>
#include <string.h>

#ifndef MAX_FILENAME_LEN
	#define MAX_FILENAME_LEN 256 
#endif

/* Args order:
 *
 * 0. pwd (current location) from main.c (I mean wsh)
 * 1. executed command
 * 2. touch arg number 1
 * 3-127. etc. which is not used
 * 
 */

int main(int argc, char** argv){ 
	if(argv[2] == NULL) {
		printf("An error occured: not enough arguments (filename) to execute touch command\n");
	} else {
		//printf("%s\t%d", argv[2], argc);
		char final_object_path[MAX_FILENAME_LEN];
		char* slash_tester = strchr(argv[2], '/');
		if(slash_tester != NULL){
			printf("An error occured. There are '/' symbols in the name of your file. Write touch --help to check some more info");
		}
		snprintf(final_object_path, sizeof(final_object_path), "%s%s", argv[0], argv[2]);
		//printf("%s", final_object_path);
		//	FILE* file = fopen(final_object_path, "w");
		//	fclose(file);
		//printf("%s\n", final_object_path); //verbose debug
		FILE* file = fopen(final_object_path,"r");
		if(!file){
			FILE* endpoint = fopen(final_object_path, "w");
			fclose(endpoint);
		}
	}
}
