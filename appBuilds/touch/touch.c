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
	//int help_tester = strcmp(argv[2], "--help"); // added here because it was way better to write it here at the moment
	if(argv[2] == NULL) {
		printf("An error occured: missing file operand\nWrite 'touch --help' to see more information\n");
	} else {
		if(strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0){
			printf("Usage:\ntouch <file_name>\n\noptions:\n-h, --help\t\t- see this menu\n");
			return 0;
		}
		//printf("%s\t%d", argv[2], argc);
		char final_object_path[MAX_FILENAME_LEN];
		char* slash_tester = strchr(argv[2], '/');
		if(slash_tester != NULL){
			printf("An error occured. There are '/' symbols in the name of your file. Write touch --help to check some more info");
		}
		if(argv[0][strlen(argv[0])-1]=='/'){
		snprintf(final_object_path, sizeof(final_object_path), "%s%s", argv[0], argv[2]);
		} else {
			snprintf(final_object_path, sizeof(final_object_path), "%s/%s", argv[0], argv[2]);
			//printf("%s\n",final_object_path);
		}
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
