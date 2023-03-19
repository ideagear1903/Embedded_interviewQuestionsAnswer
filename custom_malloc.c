#include "custom_malloc.h"


static void splitMemBlock(heapMemoryBlockInfo_t *tempNode,size_t bytes);
static void initializeHead(void);
static void mergeFreeMemBlock(void);

static char heap[HEAP_SIZE] = {0,0,0,0,0,0,0,0,0};

/*first node points to starting of heap*/
heapMemoryBlockInfo_t *freeBlockHead = (void *)heap;


static void initializeHead(void)
{
	freeBlockHead->blockSize = HEAP_SIZE - sizeof(heapMemoryBlockInfo_t);
	freeBlockHead->memoryStatusFlag = 1;
	freeBlockHead->nextNode = NULL;
}

static void splitMemBlock(heapMemoryBlockInfo_t *tempNode,size_t bytes)
{
	heapMemoryBlockInfo_t *newNode = (void *)( ((void *)tempNode) + bytes + sizeof(heapMemoryBlockInfo_t)  );
	newNode->blockSize = tempNode->blockSize - bytes - sizeof(heapMemoryBlockInfo_t);
	newNode->memoryStatusFlag = 1;
	
	newNode->nextNode = tempNode->nextNode;

	tempNode->memoryStatusFlag = 0;
	tempNode->blockSize = bytes;
	tempNode->nextNode = newNode;
}

void * memAlloc(size_t bytes)
{
	heapMemoryBlockInfo_t *currNode = freeBlockHead;
	void *resultNode = NULL;
	/*populate head with values for first time*/
	if(currNode->blockSize == 0)
	{
		printf("init memory list\r\n");
		initializeHead();
	}

	/*search for a block that is free with requested size*/
	while(((currNode->blockSize < bytes) || (currNode->memoryStatusFlag == 0)) 
		&& (currNode->nextNode != NULL))
	{
		currNode = currNode->nextNode;
	}

	if(currNode->blockSize == bytes)
	{
		printf("exact size available\r\n");
		currNode->memoryStatusFlag = 0;
		currNode->blockSize = bytes;
		resultNode = (void *)(++currNode);
	}
	else if(currNode->blockSize > bytes)
	{
		printf("spliting memory chunk\r\n");
		splitMemBlock(currNode,bytes);
		resultNode = (void *)(++currNode);
	}
	else
	{	
		printf("no memory available\r\n");
		resultNode = NULL;
	}

	return resultNode;
}

static void mergeFreeMemBlock(void)
{
	heapMemoryBlockInfo_t *currNode = freeBlockHead;
	
	while(currNode->nextNode != NULL)
	{
		if( (currNode->memoryStatusFlag) && ((currNode->nextNode)->memoryStatusFlag) )
		{
			currNode->blockSize += (currNode->nextNode)->blockSize + sizeof(heapMemoryBlockInfo_t);
			currNode->nextNode = (currNode->nextNode)->nextNode;
		}
		currNode = currNode->nextNode;
	}
}

void freeMem(void *freePtr)
{
	if( ( freePtr >= (void *)heap ) && ( freePtr < ((void *)(heap) + HEAP_SIZE )) )
	{
		heapMemoryBlockInfo_t *tempNode = (void *)freePtr;
		--tempNode;
		tempNode->memoryStatusFlag = 1;
		mergeFreeMemBlock();
		freePtr = NULL;
	}
}
