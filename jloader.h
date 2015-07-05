
#ifndef J_LOADER
#define J_LOADER
/*
 * Struc tto hold the rank, shape and data information
 * from a jGetM j.dll API call. Only for ints.
 *
 */
struct JStruct{
    int jRank;
    int * jShape;
    int * jData;
};
// Sets up the j instance to be used.
int setupJInstance(int* jdll, int jInstance);
// Executes a J command using the current J instance.
int jDo(int * jdll, int instance, const char * executeCommand);
// Gets the value of a J variable along with its rank and shape data.
int jGetM(int * jdll, int instance, const char * valueToGet, JStruct * jStruct, int ** pt);
// Frees the J instance.
int jFree(int * jdll, int instance_pointer);

#endif
