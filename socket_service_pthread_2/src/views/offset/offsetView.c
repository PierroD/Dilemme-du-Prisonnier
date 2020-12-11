#include "offsetView.h"

void writeOffset(void *object)
{
    printf("\033[1;35m OFFSET \033[0m%p\n", object);
}