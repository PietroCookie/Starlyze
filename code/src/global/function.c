/**
 * @file function.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */

// INCLUDES
#include "function.h"
#include <time.h>
#include <stdlib.h>

/**
 * @brief Obtain the current date and time
 *
 * @return char*
 */
char *get_timestamp()
{
    time_t timestamp = time(NULL);
    struct tm *local_time = localtime(&timestamp);
    char *buffer = (char *)malloc(80 * sizeof(char));
    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", local_time);
    return buffer;
}