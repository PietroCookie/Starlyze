#ifndef __ADDRESS_TABLE_H__
#define __ADDRESS_TABLE_H__

#include <stdlib.h>

#define DEFAULT_SIZE_ADDRESS_TABLE 10

typedef struct
{
	off_t position;
	size_t size;
} entry_address_table_t;

typedef struct{
	entry_address_table_t table[DEFAULT_SIZE_ADDRESS_TABLE];
	off_t position;
} address_table_t;

void initialize_address_table(address_table_t* address_table);
void save_address_table_file(int fd, off_t position, address_table_t* address_table);
void read_address_table_file(int fd, off_t position, address_table_t* address_table);

size_t calculate_necessary_size(address_table_t address_table);

#endif