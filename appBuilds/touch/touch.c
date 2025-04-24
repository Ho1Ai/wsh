#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	printf("%s\t%d", argv[1], argc);
	char* final_object_path;
	snprintf(final_object_path, 256, "./%s", argv[1]);
	printf("%s", final_object_path);
	//	FILE* file = fopen(final_object_path, "w");
	//	fclose(file);
	FILE* endpoint = fopen(final_object_path, "w");
}
