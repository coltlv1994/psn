/*
	proc.c, written by Zhengyang Lyu <lyuz@kth.se>
	Combined with modified auto3.py, originally written by Xufei Ning,
	used for processing YCSB test result.

	This file is dedicated for the purpose of a team project,
	under the supervison of teaching assistant(s) and teachers.
	Unless with written permission signed by all team members,
	any code of this file is not allowed for commercial activities.
	For academic purposes, please keep this comment part.

	Oct. 22, 2016
*/

#include "stdio.h"	//fopen(), fgetc(), fclose(), fprintf();
#include "stdlib.h"	//malloc(), free();
#include "ctype.h"	//isspace();
#include "string.h" //strcat();

//functions for memory management. 
int stralloc(char** sp);
int strdestroy(char** sp);

int main(int argc, char** argv) {
	// Variables declaration
	FILE* input;
	FILE* output;
	int charGet;
	int intCount_1, intCount_2;
	char** strArray;
	char* filename;

	// Variables initialization
	intCount_1 = 0;
	intCount_2 = 0;
	strArray = (char**)malloc(3*sizeof(char*));
	stralloc(strArray);
	char header[] = "Throughput,Latency,75th\n"; // String constant
	char ed[] = "percentile.csv";
	filename = (char*)malloc(sizeof(char)*30);

	// File operations
	strcat(filename, argv[1]);
	strcat(filename, ed);
	input = fopen("prep_c","r+");
	output = fopen(filename,"w+");
	if(!input||!output) {
		printf("File reading error.\n");
		return -1;
	}
	
	// CSV file header preparation
	
	fprintf(output, "%s", header);
	
	// Writing CSV file
	while((charGet = fgetc(input)) != EOF) {
		switch(charGet) {
			case ')' : {
				charGet = fgetc(input);
				charGet = fgetc(input);
				while(!(isspace(charGet = fgetc(input)) || feof(input)))
					strArray[intCount_2][intCount_1++] = charGet;
				// Actually feof(...) could be omitted without clear impact
				strArray[intCount_2++][intCount_1] = '\0';
				intCount_1 = 0;
				if(intCount_2 == 3) {
				fprintf(output, "%s,%s,%s\n", strArray[0], strArray[1],strArray[2]);
				// Various of ways to write file, this is considered as easiest one.
				intCount_2 = 0;
				strdestroy(strArray);
				stralloc(strArray);
				}
			}
			default: continue;
		}
	}
	fclose(output);
	fclose(input);

	// Cleaning up.
	strdestroy(strArray);
	free(strArray);
	free(filename);
	return 0;
}


int stralloc(char** sp) {
	sp[0] = (char*)malloc(30*sizeof(char));
	sp[1] = (char*)malloc(30*sizeof(char));
	sp[2] = (char*)malloc(30*sizeof(char));
	return 0;
}

int strdestroy(char** sp) {
	free(sp[0]);
	free(sp[1]);
	free(sp[2]);
	return 0;
}
