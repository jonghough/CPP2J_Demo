#include "controller.h"


void setupArr(int * jdll, int instance){
	jDo(jdll,instance,"arr =: ([ ? #/~) 5");
}

void rotateRow(int * jdll, int instance, int rowIndex, int rotDir){
	std::string dirS = rotDir < 0 ? "_1" : "1";
	std::string rowS = std::to_string(rowIndex);
	std::string cmdS = "arr =:(" + dirS + " |. " + rowS + " {\"2 arr) " + rowS + "}\"2 arr";
	jDo(jdll, instance, cmdS.c_str());
}

void rotateColumn(int * jdll, int instance, int colIndex, int rotDir){
	std::string dirS = rotDir < 0 ? "_1" : "1";
	std::string colS = std::to_string(colIndex);
	std::string cmdS = "arr =: |: ("+dirS+"|."+colS+"{\"2 |: arr)"+colS+"}\"2 |: arr";
	jDo(jdll, instance, cmdS.c_str());
}

void getArr(int * jdll, int instance, JStruct * jstruct, int** pt){
	jGetM(jdll, instance, "arr", jstruct, pt);
}

bool didWin(int * jdll, int instance){
	JStruct winStruct = {};
	jDo(jdll, instance , "win =: -. 0 e. , =\"1 arr");
	int** pt = (int**) malloc(sizeof(int*)*4);
	int ctr = 0;
	for(ctr=0;ctr<4;ctr++)
	{
		pt[ctr]=(int *)malloc(sizeof(int));
	}
	jGetM(jdll, instance, "win", &winStruct, pt);

	for(ctr=0;ctr<4;ctr++)
	{
		free(pt[ctr]);
	}
	free(pt);
	return winStruct.jData[0] == 0 ? false : true;
}

