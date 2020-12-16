/**
 * \file        offsetView.c
 * \brief       Valeurs en memoires
 * */


#include "offsetView.h"
#include "../../utils/config/parser.h"

/**
 * Affiche les cases memoires
 *
 * @param object poiteur vers les cases memoires
 * 
 * */

void writeOffset(void *object)
{
    if (getShowOffset())
        printf("\033[1;35m OFFSET \033[0m%p\n", object);
}