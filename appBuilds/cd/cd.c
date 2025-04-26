#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char** argv){
	if(argv[2]!=NULL){
		//printf("%s\n", argv[0]);
		DIR* open_directory = opendir(argv[2]);
		if (!open_directory) {
			//printf("Can't open %s: no such file or directory\n");	
		} else {
			//printf("%s", argv[0]);
			char* attr = strcat(argv[0], argv[2]);
			argv[2] = attr;
		}
	} else {
		printf("An error occured: not enough arguments (dirname) to execute cd command\n. If you meant \"~\" dir, it is not allowed at the moment, because there is no home dir");
	}
}
