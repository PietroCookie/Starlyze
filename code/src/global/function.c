#include "function.h"
#include <time.h>
#include <stdlib.h>

char* get_timestamp(){
    time_t timestamp = time(NULL);
    struct tm *local_time = localtime(&timestamp);
    char* buffer = (char*)malloc(80*sizeof(char));
    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", local_time);
    return buffer;
}