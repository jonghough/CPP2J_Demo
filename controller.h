#ifndef CONTROLLER
#define CONTROLLER

#include "jloader.h"
#include <string>
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
void setupArr(int * jdll, int instance);
void rotateColumn(int * jdll, int instance, int rowIndex, int rotDir);
void rotateRow(int * jdll, int instance, int rowIndex, int rotDir);
void getArr(int * jdll, int instance, JStruct * jstruct, int ** pt);
bool didWin(int * jdll, int instance);
#endif
