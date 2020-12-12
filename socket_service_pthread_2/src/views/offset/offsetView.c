#include "offsetView.h"
#include "../../utils/config/parser.h"

void writeOffset(void *object)
{
    if (getShowOffset())
        printf("\033[1;35m OFFSET \033[0m%p\n", object);
}