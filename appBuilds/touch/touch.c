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
 * etc. which is not used
 * 
 */

int main(int argc, char** argv){ 
	if(argv[2] == NULL) {
		printf("An error occured: not enough arguments (filename) to execute touch command\n");
	} else {
		//printf("%s\t%d", argv[2], argc);
		char final_object_path[MAX_FILENAME_LEN];
		snprintf(final_object_path, sizeof(final_object_path), "./%s", argv[2]);
		//printf("%s", final_object_path);
		//	FILE* file = fopen(final_object_path, "w");
		//	fclose(file);
		FILE* file = fopen(final_object_path,"r");
		if(!file){
			FILE* endpoint = fopen(final_object_path, "w");
			fclose(endpoint);
		}
	}
}
