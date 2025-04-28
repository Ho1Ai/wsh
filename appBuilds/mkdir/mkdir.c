#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	if(argv[2]!=NULL) {
		DIR* test_dir = opendir(argv[2]);
		if(test_dir!=NULL){
			printf("File or directory with name %s already exists. Try another directory name", argv[2]);
		} else {
			closedir(test_dir);
			if(argv[0][strlen(argv[0])-1] == '/'){
			char* dirname=strcat(argv[0], argv[2]);
//			printf("%s", dirname);
			mkdir(dirname, 0777);
			}else {
				char dirname [8192];//wanna be sure that it will be enough to keep any usable path
				snprintf(dirname, 8192, "%s/%s", argv[0], argv[2]);
				mkdir(dirname, 0777);
			}
		}
	} else {
		printf("An error occured: not enough arguments (dirname) to execute mkdir command. \n\n >>> You can write \"mkdir --help\" to see more information");
	}
}
