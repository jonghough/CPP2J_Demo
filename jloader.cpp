
#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include "jloader.h"
#include <iostream>
#include <dlfcn.h>

using namespace std;

int (*jdo)(int, const char *);
int (*jget)(int,const char *, int*,int*,int*,int*);
int (*jfree)(int);


int setupJInstance(int* jdll, int jInstance){
	jdll = (int*)dlopen("./libj.so",1);
	//===================JINIT=====================
	int (*jinit)(void ) = (int (*)(void ))dlsym(jdll, "JInit");
	jInstance = jinit();
	//setup functions
	jdo = (int (*)(int,const char *))dlsym(jdll,"JDo");
	jget =  (int (*)(int, const char *, int*,int*,int*,int*))dlsym(jdll, "JGetM");
	jfree = (int (*)(int))dlsym(jdll,"JFree");


	return jInstance;
}

int jDo(int * jdll, int instance, const char * executeCommand){
	//===================JDO=======================
	jdo(instance, executeCommand);

	return 1;
}

int jGetM(int * jdll, int instance, const char * valueToGet, JStruct* jStruct, int** pt){
	// =====================JGETM==================

	int res = jget(instance, valueToGet, pt[0], pt[1], pt[2], pt[3]);

	if(res != 0){
		cout << "JGetM error, result " << res <<"\n";
	}

	int i = 0;
	int jrank = *pt[1];
	int jshape[jrank];
	int shapectr = 1;
	int* jshapeptr = pt[2];
	for(i = 0; i < jrank; i++){
		jshape[i] = ((int *)*jshapeptr)[i];
		shapectr *= jshape[i];
	}

	int* jvals = pt[3];

	jStruct->jRank = jrank;
	jStruct->jShape = jshape;
	jStruct->jData = ((int *)jvals[0]);


	return res;
}


int jFree(int* jdll, int instance){
	//================JFREE=======================
	int f = jfree(instance);
	cout << "Free instance "<< instance;
	return f;
}
