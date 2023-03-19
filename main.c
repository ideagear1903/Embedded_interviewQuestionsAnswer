#include "custom_malloc.h"


int main()
{
	char *ptr_1 = memAlloc(10);
	for(int index=0;index<8;index++)
	{
		ptr_1[index] = 'a' + index;
	}
	ptr_1[9] = '\0';
	printf("%s\r\n",ptr_1);

        char *ptr_2 = memAlloc(10);
	for(int index=0;index<8;index++)
        {
                ptr_2[index] = 'a' + index;
        }
        ptr_2[9] = '\0';
        printf("%s\r\n",ptr_2);

	freeMem(ptr_1);
	freeMem(ptr_2);


}
