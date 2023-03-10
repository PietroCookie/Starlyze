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
int address_table_full(address_table_t address_table);

void write_address_table_in_file_descriptor(int file_descriptor, address_table_t address_table);
address_table_t read_address_table_in_file_descriptor(int file_descriptor);

void save_modification_address_table(int file_descriptor, address_table_t address_table, int id_table);

int add_entry_in_address_table(address_table_t* address_table, entry_address_table_t entry);
void remove_entry_in_address_table(address_table_t* address_table, int id_table);

size_t necessary_size_address_table();

#endif