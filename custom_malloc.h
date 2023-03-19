#ifndef _CUSTOM_MALLOC_H
#define _CUSTOM_MALLOC_H

#include <stdio.h>
#include <stdbool.h>

/*this malloc implementaion uses a static array instead of actual heap
 * size of heap defined by HEAP_SIZE macro*/

#define HEAP_SIZE 50

/*
 * the basic of malloc in heap memory is a linked list
 * the list contains memory size requested , memory status 
 * allocated or not,pointer to a next node in memory
 * */
typedef struct heapMemoryBlockInfo
{
	size_t blockSize;
	bool memoryStatusFlag;
	struct heapMemoryBlockInfo *nextNode;
}heapMemoryBlockInfo_t;


void *memAlloc(size_t bytes);
void freeMem(void *freePtr);

#endif
